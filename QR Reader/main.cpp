#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <zbar.h>

using namespace std;
using namespace cv;
using namespace zbar;  

/* This program detects any QRc codes and prints messages to the Ternimal */
int main() {
	//Capture stream from webcam.
  	VideoCapture capture(0);

  	//An image scanner
  	zbar::ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);   

   	//Check if we can get the webcam stream.
  	if(!capture.isOpened()) {
    	cout << "Could not open camera" << endl;
    	return -1;
  	}

  	while (true) {
  		//This variable will hold the image from the camera.
	    Mat camera_frame;

	    //Read an image from the camera.
	    bool success_cap = capture.read(camera_frame);

        Mat camera_frame_grey;
        cvtColor(camera_frame,camera_frame_grey,CV_BGR2GRAY);

        uchar *raw = (uchar *)camera_frame_grey.data;

	    if(success_cap) {
			int width = camera_frame.cols;   
			int height = camera_frame.rows;   
			string message = "";

			//Wrap image data   
			Image image(width, height, "Y800", raw, width * height);   
			//Scan the image for barcodes   
			scanner.scan(image);
			//Extract results  
			SymbolSet symbols = scanner.get_results();
			for(SymbolIterator iter = symbols.symbol_begin(); iter != symbols.symbol_end(); ++iter) {
				message += iter->get_data();
 			}
 			cout << "decoded message: " << message << " " << endl;
	    }  
	}
	return 0;
}
