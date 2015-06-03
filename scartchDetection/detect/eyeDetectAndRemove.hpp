#ifndef EYEDETECT_H
#define EYEDETECT_H

#include "../../tools/eye_detection.h"

class EyeDetectAndRemove{
public:
	void deal(Mat &img,Mat &img_detection){
		detectEyeAndRemove(img, img_detection);
	}
};


#endif