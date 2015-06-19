/*
 * Object Tracker Class Definition
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.26
 */

#include "Image_Processor.h"

RNG rng(12345);

// Constructor
Object_Tracker::Object_Tracker(){
	max_objects = 50;
	min_area = 20*20;
	max_area = 640*480;
}

// Helper Function INT to STRING
string intToString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

// Filter the input image matrix using erode and dilate functions
void Object_Tracker::filter(Mat &filtered_output){
	// Erode Element - 3px*3px rectangle
	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
	// Dilate with larger element
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

	// ERODE
	erode(filtered_output, filtered_output, erodeElement);
	erode(filtered_output, filtered_output, erodeElement);

	// DILATE
	dilate(filtered_output, filtered_output, dilateElement);
	dilate(filtered_output, filtered_output, dilateElement);
}

// Track Object
Mat Object_Tracker::track(Mat webcam_feed, Mat filtered_output){

	// Center of Object
	int x = 0, y  = 0;

	// Copy to temporary matrix
	Mat temp;
	filtered_output.copyTo(temp);

	// Vectors needed by findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// Find Contour
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	// Use moments to find object
	double refArea = 0;
	bool objectFound = false;

	if (hierarchy.size() > 0){
		int numObjects = hierarchy.size();

		if(numObjects < max_objects){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;
				if(area > min_area && area< max_area && area > refArea){
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
					refArea = area;
				}
				else 
					objectFound = false;
			}
		}
	}

	/*
	 * TIME TO DRAW THE OBJECT CONTOUR
	 */
	findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Approximate contour to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f> center(contours.size());
	vector<float> radius(contours.size());

	for(int i = 0; i < contours.size(); i++){
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat (contours_poly[i]));
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
	}

	// Draw polygonal contour + bounding rects + circles
	Mat tracker_output = Mat::zeros(filtered_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++){
		Scalar color = Scalar(rng.uniform(0, 255), 
				      rng.uniform(0, 255), 
                                      rng.uniform(0,255));
		drawContours(tracker_output, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(tracker_output, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(tracker_output, center[i], (int)radius[i], color, 2, 8, 0);
	}
	return tracker_output;
}
