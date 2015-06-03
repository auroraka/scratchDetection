#ifndef DETECT_H
#define DETECT_H

#include <opencv2/opencv.hpp>
#include "basicDetect.hpp"
#include "removeBig.hpp"
#include "irDetect.hpp"
#include "expandDetect.hpp"
#include "eyeDetectAndRemove.hpp"
#include "../../imageDeal/imageTool.hpp"

class Detect{
	Mat img; //img=img_gray
	BasicDetect *basicDetect;
	RemoveBig *removeBig;
	IRDetect *irDetect;
	ExpandDetect *expandDetect;
	EyeDetectAndRemove *eyeDetectAndRemove;
	
	void init(Mat &img_origin, Mat &img_detect){
		img_detect = Mat::zeros(n, m, CV_8U);
		img_detect.at<unsigned char>(3, 3) = 5;
		cvtColor(img_origin, img, CV_RGB2GRAY);
	}
	void chooseSwitch(Mat &img_origin, Mat &img_detect, int winSize, int median_threshold = 20, double contrast_threshold = 0.5){
		basicDetect = new BasicDetect;
		basicDetect->deal(img,img_detect,winSize,median_threshold,contrast_threshold);


		//removeBig = new RemoveBig;
		//removeBig->deal(img, img_detect,winSize);
		
		//irDetect=new IRDetect;
		//irDetect->deal(img_origin,img, img_detect,winSize);
		
		//expandDetect = new ExpandDetect;
		//expandDetect->deal(img_origin, img_detect,winSize);

		eyeDetectAndRemove = new EyeDetectAndRemove;
		eyeDetectAndRemove->deal(img, img_detect);
	}
public:
	void deal(Mat &img_origin, Mat &img_detect, int winSize, int median_threshold=20, double contrast_threshold=0.5){
		init(img_origin, img_detect);
		chooseSwitch(img_origin, img_detect, winSize, median_threshold, contrast_threshold);
		Debug::show("detect", img_detect);
	}
};


#endif