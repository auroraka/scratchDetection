#include "eye_detection.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String face_cascade_name = "tools/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "tools/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);


//检测出眼睛部分并去掉
void detectEyeAndRemove( Mat img ,Mat img_detection)
{
	Mat frame_gray; img.copyTo(frame_gray);
	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)){ printf("--(!)Error loading 1\n"); system("pause"); return; };
	if (!eyes_cascade.load(eyes_cascade_name)){ printf("--(!)Error loading 2\n"); system("pause"); return; };


	std::vector<Rect> faces;
	
	equalizeHist( frame_gray, frame_gray );
	//-- Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	Mat test = Mat::zeros(img.rows, img.cols, CV_8U);//

	for( size_t i = 0; i < faces.size(); i++ )
	{
		//Draw eyes
		Mat faceROI = frame_gray( faces[i] );
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
		
		for( size_t j = 0; j < eyes.size(); j++ )
		{
			Point center( int(faces[i].x + eyes[j].x + eyes[j].width*0.5), int(faces[i].y + eyes[j].y + eyes[j].height*0.5) ); 
			int radius = cvRound( (eyes[j].width + eyes[i].height)*0.25 );
			for (int u = 0; u < frame_gray.rows; u++){
				for (int v = 0; v < frame_gray.cols; v++){
					if ((u - center.y)*(u - center.y) + (v - center.x)*(v - center.x) <= radius*radius){
						img_detection.at<unsigned char>(u, v) = 0;
					}
				}
			}
			circle( frame_gray, center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
		}
	
		//Draw face
		
		if (eyes.size() < 2){
			int radius = cvRound((faces[i].width + faces[i].height)*0.0625);
			Point center(int(faces[i].x + faces[i].width*0.25), int(faces[i].y + faces[i].height*0.4));
			for (int u = 0; u < frame_gray.rows; u++){
				for (int v = 0; v < frame_gray.cols; v++){
					if ((u - center.y)*(u - center.y) + (v - center.x)*(v - center.x) <= radius*radius){
						img_detection.at<unsigned char>(u, v) = 0;
						test.at<unsigned char>(u, v) = 255;
					}
				}
			}


			center = Point(int(faces[i].x + faces[i].width*0.75), int(faces[i].y + faces[i].height*0.4));
			for (int u = 0; u < frame_gray.rows; u++){
				for (int v = 0; v < frame_gray.cols; v++){
					if ((u - center.y)*(u - center.y) + (v - center.x)*(v - center.x) <= radius*radius){
						img_detection.at<unsigned char>(u, v) = 0;
						test.at<unsigned char>(u, v) = 255;
					}
				}
			}
		}

		Point center(int(faces[i].x + faces[i].width*0.5), int(faces[i].y + faces[i].height*0.5));
		ellipse(frame_gray, center, Size(int(faces[i].width*0.5), int(faces[i].height*0.5)), 0, 0, 360, Scalar(255, 0, 255), 2, 8, 0);
	} 
	//DEBUG("test", test);
	//DEBUG("eye_detection", frame_gray);
	//DEBUG("eye_detection_remove", img_detection);
}