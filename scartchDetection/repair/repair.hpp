#ifndef REPAIR_H
#define REPAIR_H

#include "meanRepair.hpp"
#include "copyRepair.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;

class Repair{
	MeanRepair *meanRepair;
	CopyRepair *copyRepair;
	void init(Mat &img,Mat &img_detect,int winSize){
		meanRepair = new MeanRepair;
		copyRepair = new CopyRepair;
	}
	void chooseRepair(Mat &img, Mat &img_detect, int winSize){
		meanRepair->deal(img, img_detect, winSize);
	}
public:
	void deal(Mat &img,Mat &img_detect,int winSize){
		init(img, img_detect, winSize);
		chooseRepair(img, img_detect,winSize);
		
	}
};


#endif