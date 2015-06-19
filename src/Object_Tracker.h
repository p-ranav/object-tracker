/*
 * Object Tracker Class Declaration
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.26
 */

using namespace cv;

class Object_Tracker{

public:
	// Constructor
	Object_Tracker();

	// Image Filter 
	void filter(Mat &filter_matrix);

	// Main Object Tracker Function
	Mat track(Mat webcam_feed, Mat filterd_output);

private:
	int max_objects;
	int min_area;
	int max_area;
};
