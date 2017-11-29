#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
//String sign_cascade_name = "cascade_speed.xml";
//String sign_cascade_name = "cascade_archive.xml";

String stop_cascade_name_Haar = "stopsign_classifier.xml";
//String stop_cascade_name_Lbp = "stopsign_classifier.xml";
String pedestrian_Haar = "haarcascade_fullbody.xml";
//String pedestrian_Haar = "haarcascade_pedestrian.xml";
//String pedestrian_Haar = "haarcascade_mcs_upperbody.xml";
//String pedestrian_Haar = "haarcascade_frontalface_alt.xml";
//String pedestrian_Haar = "haar_classifier.xml";


//String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
//CascadeClassifier sign_cascade;
CascadeClassifier stop_cascade;
CascadeClassifier pedestrian_cascade;

//HOGDescriptor stop_cascade2;

//CascadeClassifier eyes_cascade;
string window_name = "Capture - ADAS";
RNG rng(12345);

/** @function main */
int main(int argc, const char** argv)
{

	int frameCount = 0;
	//CvCapture* capture;
	//String videoFile = "Blacksburg2.mp4";
	//String videoFile = "yield3.mp4";
	//String videoFile = "VTstopSign_2.mp4";
	String videoFile = "pedestrians1.mp4";
	//String videoFile = "VTstopSign_2.mp4";
	//VideoCapture capture(1); //zedd cam
	VideoCapture capture; //videofile
	//VideoCapture capture(0);  // webcam
	Mat frame;
	

	//-- 1. Load the cascades
	//if (!sign_cascade.load(sign_cascade_name)) { printf("--(!)Error loading\n"); return -1; };
	//if (!stop_cascade.load(stop_cascade_name_Haar)) { printf("--(!)Error loading\n"); return -1; };
	if(!pedestrian_cascade.load(pedestrian_Haar)) { printf("--(!)Error loading\n"); return -1; };
	

	//-- 2. Read the video stream
	capture.open(videoFile); //comment for web cam input
	
		while (capture.read(frame))
		{
			//frame = cvQueryFrame(capture);

			//-- 3. Apply the classifier to the frame

			if (frameCount % 2 == 0) {
			//cout << "Range" << frame.cols;

				if (!frame.empty())
				{
					detectAndDisplay(frame);
				}
				else
				{
					printf(" --(!) No captured frame -- Break!"); break;
				}
			}
			int c = waitKey(10);
			if ((char)c == 'c') { break; }
			imshow(window_name, frame);
			frameCount++;
		}
	
	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame)
{
	//std::vector<Rect> yield_signs;
	//std::vector<Rect> stop_signs;
	std::vector<Rect> pedestrian_signs;
	Mat frame_gray;
	//int thresh = 100;
	//Mat frame_hsv;
	/*Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat drawing;*/
	
	
	//Mat mask1, mask2;
	
	//cv::Rect roi(frame.cols*0.40, 0, frame.cols - frame.cols*0.40, frame.rows);
	//Mat cFrame = frame(roi);
	//cvtColor(cFrame, frame_hsv, COLOR_BGR2HSV);
	/*inRange(frame_hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
	inRange(frame_hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);*/

	//Mat mask = mask1 | mask2;

	//int red_area = cv::countNonZero(mask);

	if (1)
	{
		//int x1 = 320, x2 = 1280, y1 = 180, y2 = 720, x3, y3;

		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		//equalizeHist(frame_gray, frame_gray);
		//cvtColor(cFrame, frame_gray, CV_BGR2GRAY);

		equalizeHist(frame_gray, frame_gray);

		
		//-- Detect signs
		
		//sign_cascade.detectMultiScale(frame_gray, yield_signs, 1.2, 10, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10), Size(90, 90));
		//stop_cascade.detectMultiScale(frame_gray, stop_signs, 1.2, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10), Size(90, 90));
		pedestrian_cascade.detectMultiScale(frame_gray, pedestrian_signs, 1.1, 4, 0 | CV_HAAR_SCALE_IMAGE, Size(20, 20), Size(150, 150));

		/*for (size_t i = 0; i < stop_signs.size(); i++)
		{
			yield_signs[i].x += frame.cols*0.40;
			stop_signs[i].x += frame.cols*0.40;
		}*/
		//String str = "yield_sign_";
		
		//for (size_t i = 0; i < yield_signs.size(); i++)
		//{
		//	//Point center(yield_signs[i].x + yield_signs[i].width*0.5, yield_signs[i].y + yield_signs[i].height*0.5);
		//	Point center(yield_signs[i].x , yield_signs[i].y );
		//	rectangle(frame, yield_signs[i], Scalar(255, 255, 255), /*int thickness =*/ 1, /*int lineType = */8, /*int shift =*/ 0);
		//	Point text(yield_signs[0].x, yield_signs[0].y);
		//	str += to_string(i+1);
		//	putText(frame, str, text, FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255), 1, 8, false);

		//}

		//String str2 = "stop_sign_";
	 //   
		//for (size_t i = 0; i < stop_signs.size();i++) {
		//	//Point center(stop_signs[i].x + stop_signs[i].width*0.5, stop_signs[i].y + stop_signs[i].height*0.5);
		//	Point center(stop_signs[i].x , stop_signs[i].y );
		//	Point text(stop_signs[0].x, stop_signs[0].y);
		//	rectangle(frame, stop_signs[i], Scalar(255, 255, 255));
		//	//const String *text = "stop_sign";
		//	str2 += to_string(i+1);
		//	putText(frame, str2, text, FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255), 1, 8, false);
		//}

		String str3 = "pedestrian";

		for (size_t i = 0; i < pedestrian_signs.size(); i++) {

			Point center(pedestrian_signs[i].x, pedestrian_signs[i].y);
			Point text(pedestrian_signs[0].x, pedestrian_signs[0].y);
			rectangle(frame, pedestrian_signs[i], Scalar(255, 255, 255));

			//str3 += to_string(i + 1);
			putText(frame, str3, text, FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255), 1, 8, false);
		}

		//-- Show what you got
	}
	imshow(window_name, frame);
}