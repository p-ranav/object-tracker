/*
 * OpenCV-based Real-time Object Tracking:
 * --------------------------------------
 * (1) Periodically fetch webcam feed
 * (2) Convert RGB image frames to HSV image frames
 * (3) Filter, erode and dilate the input stream
 * (4) For all filtered objects, find contours
 * (5) Approximate contours to polygons and draw bounding boxes
 * (6) Using the object center and bounding box, track the object
 *
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.26
 */

#include <iostream>
#include "Image_Processor.h"

using namespace std;

int main(int argc, char** argv)
{
	// Create an Image Processor Object
	Image_Processor image_processor;

	// Initialize Image Processor
	image_processor.init();

	// Run Image Processor Real-Time Loop
	image_processor.run();

	return 0;
}
	
