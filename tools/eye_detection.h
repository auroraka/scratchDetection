#ifndef EYE_DETECTION_H
#define EYE_DETECTION_H

#include <opencv2/opencv.hpp>
using namespace cv;

void detectEyeAndRemove(cv::Mat frame, cv::Mat img_detection);

#endif