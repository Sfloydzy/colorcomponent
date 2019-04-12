#include "pch.h"

//IMAGE COLOUR DIFFERNTIATION
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

int main () {
	Mat image = imread("green.jpg", 1);
	namedWindow("image", CV_WINDOW_FREERATIO); //outputs image of saved image
	imshow("image", image);
	waitKey(0);

	//BGR BLUE GREEN RED
	//RED
	Mat OutputImage;
	inRange(image, Scalar(10, 10, 100), Scalar(100, 100, 255), OutputImage);

	//GREEN
	Mat OutputImage2;
	inRange(image, Scalar(10, 100, 10), Scalar(100, 255, 100), OutputImage2);
	
	int x1, x2;
	x1 = countNonZero(OutputImage);
	x2 = countNonZero(OutputImage2);

	if (x1 > x2) {
		cout << "RED" << endl;
	}
	else cout << "GREEN" << endl;


	namedWindow("Output", CV_WINDOW_FREERATIO);
	imshow("Output", OutputImage2); //outputs highlight colour region
	waitKey(0);
}


//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//Mat redFilter(const Mat& src)
//{
//	assert(src.type() == CV_8UC3);
//
//	Mat redOnly;
//	inRange(src, Scalar(0, 0, 0), Scalar(0, 0, 255), redOnly);
//
//	return redOnly;
//}
//
//int main(int argc, char** argv)
//{
//	Mat input = imread("lena.jpg");
//
//	imshow("input", input);
//	waitKey();
//
//	Mat redOnly = redFilter(input);
//
//	imshow("redOnly", redOnly);
//	waitKey();
//
//	// detect squares after filtering...
//
//	return 0;
////}


////VIDEO STREAM SLIDER
//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/highgui/highgui_c.h>
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv)
//{
//	VideoCapture cap(0); //capture the video from web cam
//
//	if (!cap.isOpened())  // if not success, exit program
//	{
//		cout << "Cannot open the web cam" << endl;
//		return -1;
//	}
//
//	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
//
//	int iLowH = 0;
//	int iHighH = 179;
//
//	int iLowS = 0;
//	int iHighS = 255;
//
//	int iLowV = 0;
//	int iHighV = 255;
//
//	//Create trackbars in "Control" window
//	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
//	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
//
//	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
//	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
//
//	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
//	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
//
//	while (true)
//	{
//		Mat imgOriginal;
//
//		bool bSuccess = cap.read(imgOriginal); // read a new frame from video
//
//		if (!bSuccess) //if not success, break loop
//		{
//			cout << "Cannot read a frame from video stream" << endl;
//			break;
//		}
//
//		Mat imgHSV;
//
//		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
//
//		Mat imgThresholded;
//
//		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
//
//	   //morphological opening (remove small objects from the foreground)
//		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//morphological closing (fill small holes in the foreground)
//		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		imshow("Thresholded Image", imgThresholded); //show the thresholded image
//		imshow("Original", imgOriginal); //show the original image
//
//		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
//		{
//			cout << "esc key is pressed by user" << endl;
//			break;
//		}
//	}
//
//	return 0;
//
//}


//COLOUR DROPPER
//#include <iostream>
//#include <string>
//#include <opencv2/opencv.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//#define COLOR_ROWS 80
//#define COLOR_COLS 250
//
//void on_mouse_click(int event, int x, int y, int flags, void* ptr) {
//	if (event == cv::EVENT_LBUTTONDOWN) {
//		cv::Mat* snapshot = (cv::Mat*)ptr;
//		cv::Vec3b pixel = snapshot->at<cv::Vec3b>(cv::Point(x, y));
//		int b, g, r;
//		b = pixel[0];
//		g = pixel[1];
//		r = pixel[2];
//		std::string rgbText = "[" + std::to_string(r) + ", " + std::to_string(g)
//			+ ", " + std::to_string(b) + "]";
//
//		// From stackoverflow.com/questions/1855884/determine-font-color-based-on-background-color
//		float luminance = 1 - (0.299*r + 0.587*g + 0.114*b) / 255;
//		cv::Scalar textColor;
//		if (luminance < 0.5) {
//			textColor = cv::Scalar(0, 0, 0);
//		}
//		else {
//			textColor = cv::Scalar(255, 255, 255);
//		}
//
//		cv::Mat colorArray;
//		colorArray = cv::Mat(COLOR_ROWS, COLOR_COLS, CV_8UC3, cv::Scalar(b, g, r));
//		cv::putText(colorArray, rgbText, cv::Point2d(20, COLOR_ROWS - 20),
//			cv::FONT_HERSHEY_SIMPLEX, 0.8, textColor);
//		cv::imshow("Color", colorArray);
//	}
//}
//
//
//int main(int argc, char** argv) {
//	cv::VideoCapture capture(0);
//
//	if (!capture.isOpened()) {
//		std::cout << "Error opening VideoCapture." << std::endl;
//		return -1;
//	}
//
//	cv::Mat frame, snapshot, colorArray;
//	capture.read(frame);
//
//	snapshot = cv::Mat(frame.size(), CV_8UC3, cv::Scalar(0, 0, 0));
//	cv::imshow("Snapshot", snapshot);
//
//	colorArray = cv::Mat(COLOR_ROWS, COLOR_COLS, CV_8UC3, cv::Scalar(0, 0, 0));
//	cv::imshow("Color", colorArray);
//	cv::setMouseCallback("Snapshot", on_mouse_click, &snapshot);
//
//	int keyVal;
//	while (1) {
//		if (!capture.read(frame)) {
//			break;
//		}
//		cv::imshow("Video", frame);
//
//		keyVal = cv::waitKey(1) & 0xFF;
//		if (keyVal == 113) {
//			break;
//		}
//		else if (keyVal == 116) {
//			snapshot = frame.clone();
//			cv::imshow("Snapshot", snapshot);
//		}
//	}
//	return 0;
//}