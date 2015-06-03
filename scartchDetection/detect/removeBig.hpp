#ifndef REMOVEBIG_H
#define REMOVEBIG_H

#include "../../tools/function.hpp"

class RemoveBig{
public:
	void deal(Mat &img, Mat &img_detection, int winSize){
		winSize = max(winSize, 5);
		int n = img.rows, m = img.cols;
		int **sum = ArraySpace::newArray(n + 5, m + 5), **use = ArraySpace::newArray(n + 5, m + 5);
		for (int i = 1; i <= img.rows; i++){
			for (int j = 1; j <= img.cols; j++){
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (img_detection.at<unsigned char>(i - 1, j - 1) == 0 ? 0 : 1);
			}
		}
		for (int i = 1; i <= img.rows; i++){
			for (int j = 1; j <= img.cols; j++) if (!use[i][j]){
				int x1 = i - winSize, x2 = i + winSize;
				int y1 = j - winSize, y2 = j + winSize;
				if (ArraySpace::inMap1(x1, y1, n, m) && ArraySpace::inMap1(x2, y2, n, m)){
					int x = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
					if (double(x) / ((2 * winSize + 1)*(2 * winSize + 1)) > 0.8){
						for (int u = x1; u <= x2; u++){
							for (int v = y1; v <= y2; v++){
								img_detection.at<unsigned char>(u, v) = 0;
								use[u][v] = 1;
							}
						}
					}
				}
			}
		}
		//ArraySpace::deleteArray(sum, n+5, m+5);
		//ArraySpace::deleteArray(use, n+5, m+5);
		Debug::show("remove_bigger", img_detection);
	}

};


#endif