#ifndef MEANDETECT_H
#define MEANDETECT_H

#include "repairTool.hpp"

class MeanRepair{
private:
	void reconstructAverage(int i, int j, Mat &img, Mat &img_mark, int size){
		if (!img_mark.at<unsigned char>(i, j)) return;
		int flag = 1, mySize = size;
		while (flag&&mySize < 0.02*min(img.cols, img.rows)){
			img.at<Vec3b>(i, j) = RepairSpace::getAverage_color(img, img_mark, i, j, size, flag);
			mySize++;
		}
		img_mark.at<unsigned char>(i, j) = 0;
	}
	void reconstruction_color(Mat &img, Mat &img_detection, int size){
		Mat img_mark;
		img_detection.copyTo(img_mark);
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				if (img_mark.at<unsigned char>(i, j) != 0){
					reconstructAverage(i, j, img, img_mark, size);
				}
			}
		}
	}
public:
	void deal(Mat &img,Mat &img_detect,int winSize){
		reconstruction_color(img, img_detect, winSize);
	}
};


#endif