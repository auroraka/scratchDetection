#ifndef COPYREPAIR_H
#define COPYREPAIR_H

#include <opencv2\opencv.hpp>

class CopyRepair{
private:
	void init(Mat &img, Mat &img_detection, int size, int size_big){
		/*n = img.rows; m = img.cols;
		detect = newArray<int>(n + 5, m + 5);
		detect_sum = newArray<int>(n + 5, m + 5);
		detect_sum_box = newArray<int>(n + 5, m + 5);
		visited = newArray<int>(n + 5, m + 5);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++){
				detect[i][j] = img_detection.at<unsigned char>(i, j) > 0 ? 1 : 0;
			}
		detect_sum[0][0] = detect[0][0];
		detect_sum[0][1] = detect[0][1];
		detect_sum[1][0] = detect[1][0];
		for (int i = 1; i < n; i++)
			for (int j = 1; j < m; j++){
				detect_sum[i][j] = detect_sum[i - 1][j] + detect_sum[i][j - 1] - detect_sum[i - 1][j - 1] + detect[i][j];
			}
		for (int i = size + 1; i <= n - size; i++)
			for (int j = size + 1; j <= m - size; j++){
				detect_sum_box[i][j] = detect_sum[i + size][j + size] - detect_sum[i + size][j - size - 1] - detect_sum[i - size - 1][j + size] + detect_sum[i - size - 1][j - size - 1];
			}*/
	}
public:
	void deal(Mat &img,Mat &img_detect,int winSize,int winSizeBig=500){
		//int n, m;
		//int **detect, **detect_sum, **detect_sum_box, **visited;
		//init(img,img_detect,winSize,winSizeBig);
	}
};

#endif