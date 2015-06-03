#ifndef GUIDED_H
#define GUIDED_H

#include "../../tools/guidedfilter.hpp"
#include "../../mydebug/debug.hpp"

class Guided{
public:
	void deal(Mat &img){
		Mat img_guide;
		guidedFilterColor(img, img, img_guide, 2, 10 * 10);
		img = img_guide;
		Debug::show("beautify", img);
	}
};


#endif