#ifndef DEBUG_H
#define DEBUG_H

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class Debug;
extern Debug Mdebug;//Attention: Mdebug need initialize in main

class Debug{
public:
	static char dir[100];
	enum state{ ON, OFF };
	static int SWITCH;
	static int showImage;
	static int writeImage;
	static int TEXT;
	static void show(string name, Mat a){
		if (SWITCH == OFF) return;
		if (a.data == NULL){
			cout << "Debug error: " << name << " is NULL" << endl;
			//system("pause");
			return;
		}
		if (writeImage == ON){
			sprintf(dir, "pic/%s.jpg", name.c_str());
			imwrite(dir, a);
		}
		if (showImage == ON){
			imshow(name, a);
		}
	}

	static void showAndExit(string name, Mat a){
		if (SWITCH == OFF) return;
		if (a.data == NULL) return;
		if (writeImage == ON){
			sprintf(dir, "pic/%s.jpg", name.c_str());
			imwrite(dir, a);
		}
		if (showImage == ON){
			imshow(name, a);
		}
		waitKey(0);
		exit(0);
	}
	static void quit(){
		if (SWITCH == OFF) return;
		cout << "quit...";
		waitKey(0);
		//system("pause");
		exit(0);
	}
	Debug& operator << (int a){
		if (SWITCH == OFF) return *this;
		if (TEXT==ON){
			cout << a << endl;
		}
		return *this;
	}
};

int Debug::SWITCH = ON;
int Debug::showImage=ON;
int Debug::writeImage = ON;
int Debug::TEXT = ON;

char Debug::dir[100] = "";


#endif