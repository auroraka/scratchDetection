#ifndef EXPANDDETECT_H
#define EXPANDDETECT_H

#include "../../tools/function.hpp"

class ExpandDetect{
private:
	int dis(int x, int y, int i, int j, Mat &img){
		int sum = 0;
		for (int k = 0; k < 3; k++) sum += abs(img.at<Vec3b>(x, y)[k] - img.at<Vec3b>(i, j)[k]);
		return sum;
	}
	int check(int x, int y, int u, int v, Mat &img, int size){
		int count = 0;
		if (dis(x, y, u, v, img) <= 20){
			for (int i = max(0, x - size); i < min(img.rows, x + size + 1); i++)
				for (int j = max(0, y - size); j < min(img.cols, y + size + 1); j++){
					if (dis(i, j, x, y, img)>80) count++;
				}
			return double(count) / (2 * size + 1)*(2 * size + 1)>0.3;
		}
		return 0;
	}
	int countNeighbor(Mat &img, Mat &img_detection, int i, int j){
		int count = 0;
		for (int k = 0; k < 4; k++){
			int u = i + ArraySpace::xo[k];
			int v = j + ArraySpace::yo[k];
			if (ArraySpace::inMap(u, v, img.rows, img.cols) && img_detection.at<unsigned char>(u, v) != 0) count++;
		}
		return count;
	}
	int getDetectMed(Vec3b detectMed, Mat &img, Mat &img_detect, int i, int j, int size){
		int count = 0;
		detectMed = Vec3b(0, 0, 0);
		for (int u = i - size; u <= i + size; u++)
			for (int v = j - size; v <= j + size; v++) if (ArraySpace::inMap(u, v, img.rows, img.cols)){
				if (img_detect.at<unsigned char>(u, v) != 0){
					detectMed = detectMed + img.at<Vec3b>(u, v);
					count++;
				}
			}
		if (!count) return 0;
		detectMed = detectMed / count;
		return 1;
	}
	int getUndetectMed(Vec3b undetectMed, Mat &img, Mat &img_detect, int i, int j, int size){
		int count = 0;
		undetectMed = Vec3b(0, 0, 0);
		for (int u = i - size; u <= i + size; u++)
			for (int v = j - size; v <= j + size; v++) if (ArraySpace::inMap(u, v, img.rows, img.cols)){
				if (img_detect.at<unsigned char>(u, v) == 0){
					undetectMed += img.at<Vec3b>(u, v);
					count++;
				}
			}
		if (!count) return 0;
		undetectMed /= count;
		return 1;
	}
	int farFromUndetect(Mat &img, Mat &img_detection, int i, int j, int size){
		return 1;
		Vec3b detectMed, undetectMed;
		if (!getDetectMed(detectMed, img, img_detection, i, j, size)) return 0;
		if (!getUndetectMed(undetectMed, img, img_detection, i, j, size)) return 0;
		for (int k = 0; k < 3; k++){
			if ((img.at<Vec3b>(i, j)[k] - detectMed[k]) / (undetectMed[k] - detectMed[k]) > 0.3) return 0;
		}
		return 1;
	}
	int nearToDetect(Mat &img, Mat &img_detection, int i, int j, int size){
		Vec3b detectMed;
		if (!getDetectMed(detectMed, img, img_detection, i, j, size)) return 0;
		for (int k = 0; k < 3; k++){
			if (abs(img.at<Vec3b>(i, j)[k] - detectMed[k])>50) return 0;
		}
		return 1;
	}
public:
	void deal(Mat &img, Mat &img_detection, int size){
		for (int i = 0; i < img.rows; i++)
			for (int j = 0; j < img.cols; j++) if (img_detection.at<unsigned char>(i, j) == 0){
				int detectNeibor = countNeighbor(img, img_detection, i, j);
				if (detectNeibor == 4){
					img_detection.at<unsigned char>(i, j) = 255;
				}
				else if (detectNeibor >= 1){
					if (nearToDetect(img, img_detection, i, j, size) && farFromUndetect(img, img_detection, i, j, size)){
						img_detection.at<unsigned char>(i, j) = 255;
					}
				}
			}
		Debug::show("expand", img_detection);
	}
	void deal2(Mat &img, Mat &img_detection, int size){
		Point3D *Q = new Point3D[(img.rows + 5)*(img.cols + 5)];
		int **visited = ArraySpace::newArray(img.rows + 5, img.cols + 5);
		int p1 = 1, p2 = 0;
		for (int i = 0; i < img.rows; i++)
			for (int j = 0; j < img.cols; j++) if (img_detection.at<unsigned char>(i, j) != 0){
				Q[++p2] = Point3D(i, j, 0);
				visited[i][j] = 1;
			}
		for (; p1 <= p2; p1++){
			int u = Q[p1].x, v = Q[p1].y;
			for (int k = 0; k < 4; k++){
				int x = u + ArraySpace::xo[k];
				int y = v + ArraySpace::yo[k];
				if (ArraySpace::inMap(x, y, img.rows, img.cols) && check(x, y, u, v, img, size) && !visited[x][y] && Q[p1].z<2){
					visited[x][y] = 1;
					Q[++p2] = Point3D(x, y, Q[p1].z + 1);
					img_detection.at<unsigned char>(x, y) = 255;
					cout << x << " " << y << endl;
				}
			}
		}
		Debug::show("expand", img_detection);
	}
};


#endif