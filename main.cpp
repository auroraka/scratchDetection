#include "imageDeal\imageTool.hpp"
#include "scartchDetection\scratchDetection.hpp"
#include "mydebug\debug.hpp"
#include <iostream>
using namespace std;

char name[100];
Debug Mdebug;
int n, m;

void init(Mat &img){
	n = img.rows;
	m = img.cols;
}
void imgLoad(int i, Mat &img){
	sprintf(name, "pic/%d.jpg", i);
	img = imread(name);
}
void showResult(int i,Mat &img,Mat &img_repair){
	cout << "deal " << i << " ok." << endl;
	sprintf(name, "pic/%d_repair.jpg", i);
	imwrite(name, img_repair);
	
	Debug::show("origin",img);
	Debug::show("repair", img_repair);
	waitKey(0);
}
void detect(){
	ScratchDetection *scratchDetection=new ScratchDetection;
	Mat img, img_repair;
	for (int i = 3; i <= 3; i++){
		imgLoad(i,img);
		if (!img.data) continue;
		init(img);
		scratchDetection->deal(img, img_repair);
		showResult(i,img,img_repair);
	}
}
int main(){
	detect();
	return 0;
}