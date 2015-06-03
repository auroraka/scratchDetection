#ifndef IRDETECT_H
#define IRDETECT_H

class IRDetect{
private:
	void decMean(Mat img){
		int x = 0;
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				x += img.at<unsigned char>(i, j);
			}
		}
		x = int(double(x) / img.rows*img.cols);
		img = img - x;
		x = 0;
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				x = std::max(x, int(img.at<unsigned char>(i, j)));
			}
		}
	}
public:
	void deal(Mat img_origin, Mat img, Mat img_detection, int winSize){
		Mat img_IR(img.rows, img.cols, CV_8U), img_IR_detection;
		if (!img_detection.data) img_detection = Mat(img.rows, img.cols, CV_8U);
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				img_IR.at<unsigned char>(i, j) = img_origin.at<Vec3b>(i, j)[1];
			}
		}

		double a = 1.2, b = 0;
		img_IR_detection = a*img - img_IR + b;

		img = img*0.15;
		img_IR_detection = img_IR_detection - img;

		decMean(img_IR_detection);
		//imshow("dec", img_IR_detection);
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				if (img_IR_detection.at<unsigned char>(i, j)>10) img_detection.at<unsigned char>(i, j) = 255;
			}
		}
		for (int i = 0; i < img.rows; i++){
			for (int j = 0; j < img.cols; j++){
				if (!(i>winSize && j > winSize && img.rows - i > winSize && img.cols - j > winSize)){
					img_detection.at<unsigned char>(i, j) = 0;
				}
			}
		}
		Debug::show("IR_detection", img_detection);
	}
};


#endif