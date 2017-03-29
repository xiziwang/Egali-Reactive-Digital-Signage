/*****************************************************************************
*                                                                            * 
*  Copyright (C) Karl Engebretson & Xizi Wang                                *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/

/* Notice: A part of the code is referred to the file NiSimpleRead.cpp */

#include <XnOpenNI.h>
#include <XnLog.h>
#include <XnCppWrapper.h>
#include <iostream>
#include <string>
#include <fstream>
#include "depthdetectorthread.h"

using namespace xn;
using namespace std;

// Macros - CHECK Status
#define CHECK_RC(rc, what)											\
    if (rc != XN_STATUS_OK)											\
    {																\
        printf("%s failed: %s\n", what, xnGetStatusString(rc));		\
    }

/*******************************************************************/
/* This thread detects the depth of the central point of the frame */
/*******************************************************************/

DepthDetectorThread::~DepthDetectorThread() {
    wait();
}

/* This  detects . */
void DepthDetectorThread::run() {

    XnStatus nRetVal = XN_STATUS_OK;

	Context context;
	ScriptNode scriptNode;
	EnumerationErrors errors;

    //Check the existence of Config.xml file
    //NOTE: this path might be changed
    const char *fn = "/Users/Lucy-Wang/Developer/Kinect/Egali-Reactive-Digital-Signage/Egali_Reactive_Digital_Signage/Config.xml";
	ifstream fin(fn);
	if(!fin) {
		printf("Could not find '%s'. Aborting.\n" , fn);
        cout << "Error: " << XN_STATUS_ERROR << endl;
	}
	printf("Reading config from: '%s'\n", fn);
	
	//Init from Config.xml
	nRetVal = context.InitFromXmlFile(fn, scriptNode, &errors);

	//Check the status (node)
	if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
        cout << "Error: " << nRetVal << endl;
	}
	else if (nRetVal != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));
        cout << "Error: " << nRetVal << endl;
    }

	DepthGenerator depth;
	DepthMetaData depthMD;

	//Find existing ndoe
	nRetVal = context.FindExistingNode(XN_NODE_TYPE_DEPTH, depth);
	CHECK_RC(nRetVal, "Find depth generator");

	while (true)
	{
		//Update and check status
		nRetVal = context.WaitOneUpdateAll(depth);
		if (nRetVal != XN_STATUS_OK)
		{
			printf("UpdateData failed: %s\n", xnGetStatusString(nRetVal));
			continue;
		}

		//Generate Meta Data
		depth.GetMetaData(depthMD);
		XnDepthPixel distance = depthMD(depthMD.XRes() / 2, depthMD.YRes() / 2);

        string depth = depthGenerator(distance);
        // if distance changed, send the signal
        if (depth.compare(m_depth)!=0) {
            m_depth = depth;
            emit depthChanged();
        }
    }
	//Release vars
	depth.Release();
	scriptNode.Release();
	context.Release();
}

/* generate depth range string */
string DepthDetectorThread::depthGenerator(XnDepthPixel distance) {
    string res = "";
    int d = (int) distance;

    // generate main container depth
    if (0 < d && d < 1000) res += "0";
    else if (1001 < d && d < 2000) res += "1";
    else if (2001 < d && d < 3000) res += "2";
    else res += "i";
    res += " ";

    // generate secondary container depth
    if(0 < d && d < 1500) res += "0";
    else if (1501 < d && d < 3000) res += "1";
    else res += "i";
    res += " ";

    // generate guidance container depth
    if(0 < d && d < 1500) res += "0";
    else res += "i";

    return res;
}


/* This function return the stored m_depth since the m_depth is a private variable*/
string DepthDetectorThread::getDepth() {
    return m_depth;
}
