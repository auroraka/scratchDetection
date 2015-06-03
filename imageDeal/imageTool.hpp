#ifndef MYMAT_H
#define MYMAT_H

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


//Attention: n,m need initialize in main
extern int n;
extern int m;


class Mat8u:public Mat{
public:
	Mat8u() :Mat(){};
	Mat8u(Mat img):Mat(img){}
	unsigned char &myat(int i,int j){
		return Mat::at<unsigned char>(i, j);
	}
};
class Mat3c :public Mat{
public:
	Mat3c():Mat(){};
	Mat3c(Mat img) :Mat(img){}
	Vec3b &myat(int i, int j){
		return Mat::at<Vec3b>(i, j);
	}
};

namespace ImageSpace{
	void split(Mat &img, Mat img_channel[]){
		for (int k = 0; k < 3; k++){
			img_channel[k] = Mat(img.rows, img.cols, CV_8U);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++){
					img_channel[k].at<unsigned char>(i, j) = img.at<Vec3b>(i, j)[k];
				}
		}
	}

	void join(Mat img_channel[], Mat &img){
		img = Mat(img_channel[0].rows, img_channel[0].cols, CV_8UC3);
		for (int k = 0; k < 3; k++){
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++){
					img.at<Vec3b>(i, j)[k] = img_channel[k].at<unsigned char>(i, j);
				}
		}
	}
}

#endif