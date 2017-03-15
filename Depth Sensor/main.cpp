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

// Macros - CHECK Status
#define CHECK_RC(rc, what)											\
	if (rc != XN_STATUS_OK)											\
	{																\
		printf("%s failed: %s\n", what, xnGetStatusString(rc));		\
		return rc;													\
	}

using namespace xn;
using namespace std;


/* This program detects the depth of the central point of the frame. */
int main() {

	XnStatus nRetVal = XN_STATUS_OK;

	Context context;
	ScriptNode scriptNode;
	EnumerationErrors errors;

	//Check the existence of Config.xml file
	const char *fn = "Config.xml";
	ifstream fin(fn);
	if(!fin) {
		printf("Could not find '%s'. Aborting.\n" , fn);
		return XN_STATUS_ERROR;
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
		return (nRetVal);
	}
	else if (nRetVal != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));
		return (nRetVal);
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
		cout << "FrameID: " << depthMD.FrameID() << " z_axis: " << distance << endl;
	}

	//Release vars
	depth.Release();
	scriptNode.Release();
	context.Release();

	return 0;
}
