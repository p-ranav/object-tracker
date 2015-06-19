/*
 * Image Processor Class Declaration
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.26
 */

#include <stdio.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "Object_Tracker.h"

using namespace cv;

class Image_Processor{

public:
	// Setup Webcam feed variable
        void setup_webcam_feed(int cam_id=0);

	// Setup filter knobs slider
	void create_filter_knobs_slider();

	// Show output windows
	void show_windows();

	// Handle user input
	void handle_user_input();

	// Main Initialize Function
	void init();

	// Main Real-Time Loop
	void run();

private:
	// Webcam feed
	VideoCapture webcam;

	// Object Tracker Object
	Object_Tracker object_tracker;

	// Webcam Image Frame Matrix
	Mat webcam_feed;

	// HSV Image Matrix
	Mat HSV;

	// Filtered Image Matrix
	Mat filtered_output;	

	// Object Tracker Matrix
	Mat tracker_output;

	// User Input from Keyboard
	char key_press;
	bool quit;
};
