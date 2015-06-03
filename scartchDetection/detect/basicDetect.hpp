#ifndef BASICDETECT_H
#define BASICDETECT_H

#include "../../mydebug/debug.hpp"
#include "../../tools/guidedfilter.hpp"

class BasicDetect{
private:
	void median_detect_color(Mat& img, Mat &img_median_detect, int winSize, int  median_diff_threshold){
		Mat img_median;
		img_median_detect = Mat(img.rows, img.cols, CV_8U);
		medianBlur(img, img_median, 2 * winSize + 1);
		Debug::show("median_img", img_median);
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				if (abs(img.at<unsigned char>(i, j) - img_median.at<unsigned char>(i, j)) >= median_diff_threshold){
					img_median_detect.at<unsigned char>(i, j) = 255;// abs(img.at<unsigned char>(i, j) - img_median.at<unsigned char>(i, j));
				}
				else{
					img_median_detect.at<unsigned char>(i, j) = 0;
				}
			}
		}
		Debug::show("median", img_median_detect);
	}
	void calcStd(Mat &img, Mat &img_std, int winSize){
		Mat img_double, img_mean;
		img.convertTo(img_double, CV_64F);
		Size win_size(2 * winSize + 1, 2 * winSize + 1);
		boxFilter(img_double, img_mean, CV_64F, win_size);
		absdiff(img_double, img_mean, img_std);
		img_std = img_std.mul(img_std);
		boxFilter(img_std, img_std, CV_64F, win_size);
	}
	void calcContrast(Mat &stdg, Mat &stddl, Mat &img_output){
		Mat temp, temp2; double eps = 0.001;
		temp = stdg - stddl; temp = temp.mul(temp);
		temp2 = stdg.mul(stdg) + stddl.mul(stddl) + eps;
		divide(temp, temp2, img_output);
	}
	double calcContrastThreshold(Mat &img_contrast){
		vector<double> my;
		my.clear();
		for (int i = 0; i < img_contrast.rows; i++)
			for (int j = 0; j < img_contrast.cols; j++){
				my.push_back(img_contrast.at<double>(i, j));
			}
		return my[int(img_contrast.rows*img_contrast.cols*0.6)];
	}
	void makeContrastDetect(Mat &img_contrast, Mat &img_contrast_detect, double contrast_threshold_old){
		//PRINTF(img_contrast, 50);
		double contrast_threshold = calcContrastThreshold(img_contrast);
		img_contrast_detect = Mat(img_contrast.rows, img_contrast.cols, CV_8U);
		for (int i = 0; i < img_contrast.rows; i++){
			for (int j = 0; j < img_contrast.cols; j++){
				if (img_contrast.at<double>(i, j) > contrast_threshold){
					img_contrast_detect.at<unsigned char>(i, j) = (unsigned char)(100 * abs(img_contrast.at<double>(i, j) - contrast_threshold));
				}
				else{
					img_contrast_detect.at<unsigned char>(i, j) = 0;
				}
			}
		}
	}
	void contrast_detect_color(Mat &img, Mat &img_contrast_detect, int winSize, double  contrast_threshold){
		Mat img_median, stdg, stddl, img_contrast;
		medianBlur(img, img_median, 2 * winSize + 1);

		calcStd(img, stdg, winSize);
		calcStd(img_median, stddl, winSize);
		calcContrast(stdg, stddl, img_contrast);
		makeContrastDetect(img_contrast, img_contrast_detect, contrast_threshold);
		Debug::show("contrast", img_contrast_detect);
	}
	void combine_color(Mat &img_median_detect, Mat &img_contrast_detect, Mat &img_detection, int threshold){
		double temp, medianMax, contrastMax;
		double *a = &temp, *b = &medianMax, *c = &contrastMax;
		minMaxIdx(img_median_detect, a, b);
		minMaxIdx(img_contrast_detect, a, c);
		img_detection = Mat(img_median_detect.rows, img_median_detect.cols, CV_8U);
		for (int i = 0; i < img_median_detect.rows; i++){
			for (int j = 0; j < img_median_detect.cols; j++){
				int x = img_median_detect.at<unsigned char>(i, j), y = img_contrast_detect.at<unsigned char>(i, j);
				//cout << x << " " << y << endl;
				unsigned char z = unsigned char(((double)x / medianMax)*((double)y / contrastMax) * 255);
				//cout<< x<<" "<< medianMax<<" " <<y<<" "<< contrastMax<<" "<<int(z)<<endl;
				img_detection.at<unsigned char>(i, j) = z>20 ? z : 0;
				/*if (x && y){
				img_detection.at<unsigned char>(i, j) = img_median_detect.at<unsigned char>(i, j);
				}
				else{
				img_detection.at<unsigned char>(i, j) = 0;
				}*/
			}
		}
		//imshow("aaa", img_detection);
		//waitKey(0);
		//PRINTFILE(img_contrast_detect, "output.txt");
		//exit(0);
	}
	void guidedDetect(Mat &img, Mat &img_detection, int winSize, int guideThreshold){
		Mat img_guide(img.rows, img.cols, CV_8U);
		img_detection = Mat(img.rows, img.cols, CV_8U);
		guidedFilter(img, img, img_guide, 6, 40 * 40);
		for (int i = 0; i < img.rows; i++)
			for (int j = 0; j < img.cols; j++){
				int x = img.at<unsigned char>(i, j), y = img_guide.at<unsigned char>(i, j);
				if (abs(x - y) > guideThreshold) img_detection.at<unsigned char>(i, j) = abs(x - y);
				else img_detection.at<unsigned char>(i, j) = 0;
			}
		//DEBUG("detect", img_detection);
		Debug::show("guide", img_detection);
		Debug::show("guide_img", img_guide);
		/*for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++){
		int x = img.at<unsigned char>(i, j), y = img_guide.at<unsigned char>(i, j);
		if (abs(x - y) > 0){
		img_detection.at<unsigned char>(i, j) = abs(x - y);
		}
		else img_detection.at<unsigned char>(i, j) = 0;
		}*/
		//DEBUGAndReturn("detect2", img_detection);
	}
public:
	void deal(Mat &img, Mat &img_detection, int winSize, int median_diff_threshold, double contrast_threshold){
		//Debug<<
		Mat img_median_detect, img_guide_detect, img_contrast_detect;
		//guidedDetect(img, img_guide_detect, winSize, median_diff_threshold);
		
		median_detect_color(img, img_median_detect, winSize, median_diff_threshold);
		contrast_detect_color(img, img_contrast_detect, winSize, contrast_threshold);
		combine_color(img_median_detect, img_contrast_detect, img_detection, 30);
		Debug::show("detect_color", img_detection);

	}
};


#endif