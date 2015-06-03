#ifndef BEATUIFY_H
#define BEAUTIFY_H

#include "Guided.hpp"

class Beautify{
	Guided *guided;
	void init(Mat &img){
	
		guided = new Guided;
	}
	void chooseSwitch(Mat &img){
		guided->deal(img);
		
	}
public:
	void deal(Mat &img){
		init(img);
		chooseSwitch(img);
	}
};


#endif BEAUTIFY_H