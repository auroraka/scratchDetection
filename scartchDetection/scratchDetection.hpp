#ifndef SCRATCHDETECTION_H
#define SCRATCHDETECTION_H

#include "detect\detect.hpp"
#include "repair\repair.hpp"
#include "beautify\beautify.hpp"

class ScratchDetection{
	Detect *detect;
	Repair *repair;
	Beautify *beautify;
public:
	ScratchDetection(){
		detect = new Detect;
		repair = new Repair;
		beautify = new Beautify;
	}
	void deal(Mat &img,Mat &img_repair,int winSize=4){
		Mat img_detect;
		detect->deal(img, img_detect, winSize);
		img.copyTo(img_repair);
		repair->deal(img_repair,img_detect, winSize);
		beautify->deal(img);
	}
};

#endif