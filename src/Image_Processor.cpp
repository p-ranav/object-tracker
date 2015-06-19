/*
 * Image Processor Class Definition
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.26
 */

#include "Image_Processor.h"

// Filter Global Variables
int hue_min = 0;
int hue_max = 255;
int saturation_min = 0;
int saturation_max = 255;
int value_min = 0;
int value_max = 255;

// Global callback function for sliders
void slider_update(int, void*){}

void Image_Processor::create_filter_knobs_slider(){
	namedWindow("Filter Knobs", 0);    
	createTrackbar( "Hue_MIN", "Filter Knobs", &hue_min, hue_max, slider_update);
	createTrackbar( "Hue_MAX", "Filter Knobs", &hue_max, hue_max, slider_update);
	createTrackbar( "Sat_MIN", "Filter Knobs", &saturation_min, saturation_max, slider_update);
	createTrackbar( "Sat_MAX", "Filter Knobs", &saturation_max, saturation_max, slider_update);
	createTrackbar( "Value_MIN", "Filter Knobs", &value_min, value_max, slider_update);
	createTrackbar( "Value_MAX", "Filter Knobs", &value_max, value_max, slider_update);
}

// Setup Webcam Feed
void Image_Processor::setup_webcam_feed(int cam_id){
	// Start up webcam
	webcam.open(cam_id);

	//set Height and Width of Feed
	webcam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	webcam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
}

// Show Output Windows
void Image_Processor::show_windows(){
	imshow("Webcam", webcam_feed);
	imshow("HSV", HSV);
	imshow("Filter", filtered_output);
	imshow("Object Tracker", tracker_output);
}

// Check for User Input
void Image_Processor::handle_user_input(){
	// Briefly wait for key press
	key_press = cvWaitKey(20);

	// If user presses ESC, quit loop
	if (key_press == 27)
		quit = true;
}

// Main Initialize Function
void Image_Processor::init(){
	setup_webcam_feed(0);
	create_filter_knobs_slider();
}

// Main Real-Time Loop
void Image_Processor::run(){
	quit = false;
	while(quit == false){

		// Obtain Webcam Feed
		webcam.read(webcam_feed);

		// Convert from RGB TO HSV space
		cvtColor(webcam_feed, HSV, COLOR_BGR2HSV);

		// Filter HSV Image based on slider values
		inRange(HSV,
                        Scalar(hue_min, saturation_min, value_min), 
                        Scalar(hue_max, saturation_max, value_max),
                        filtered_output);

		// Erode and Dilate
		object_tracker.filter(filtered_output);

		// Track Object
		tracker_output = object_tracker.track(webcam_feed, filtered_output);

		// Show all output windows
		show_windows();

		// Handle user input
		handle_user_input();
	}
}
