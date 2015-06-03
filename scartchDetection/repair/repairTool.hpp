#ifndef REPAIRTOOL_H
#define REPAIRTOOL_H

namespace RepairSpace{
	unsigned char getMedian(Mat &img, Mat &img_detection, int i1, int j1, int size){
		vector<unsigned char> my;
		my.clear();
		for (int i = max(i1 - size, 0); i < min(i1 + size + 1, img.rows); i++){
			for (int j = max(j1 - size, 0); j < min(j1 + size + 1, img.cols); j++){
				if (img_detection.at<unsigned char>(i, j) == 0){
					my.push_back(img.at<unsigned char>(i, j));
				}
			}
		}
		sort(my.begin(), my.end());
		return my.size() ? my[my.size() / 2] : 0;
	}

	int getWeightAverage(Mat &img, Mat &img_detection, int i1, int j1, int size){
		int sum = 0, tot = 0, x;
		for (int i = max(i1 - size, 0); i < min(i1 + size + 1, img.rows); i++){
			for (int j = max(j1 - size, 0); j < min(j1 + size + 1, img.cols); j++){
				if (img_detection.at<unsigned char>(i, j) == 0){
					x = (2 * size - abs(i - i1) + abs(j - j1));
					tot += x;
					sum += x*img.at<unsigned char>(i, j);
				}
			}
		}
		return tot ? (sum / tot) : -1;
	}
	int getAverage(Mat &img, Mat &img_detection, int i1, int j1, int size, int &flag){
		int sum = 0, tot = 0, x;
		for (int i = max(i1 - size, 0); i < min(i1 + size + 1, img.rows); i++){
			for (int j = max(j1 - size, 0); j < min(j1 + size + 1, img.cols); j++){
				if (img_detection.at<unsigned char>(i, j) == 0){
					x = 1;
					tot += x;
					sum += x*img.at<unsigned char>(i, j);
				}
			}
		}
		if (!tot) flag = 1; else flag = 0;
		return tot ? (sum / tot) : 0;
	}
	Vec3b getAverage_color(Mat &img, Mat &img_detection, int i1, int j1, int size, int &flag){
		//size = 7;
		int sumx = 0, sumy = 0, sumz = 0, tot = 0, x;
		for (int i = max(i1 - size, 0); i < min(i1 + size + 1, img.rows); i++){
			for (int j = max(j1 - size, 0); j < min(j1 + size + 1, img.cols); j++){
				if (img_detection.at<unsigned char>(i, j) == 0){
					x = (2 * size - abs(i - i1) + abs(j - j1));
					tot += x;
					sumx += x*img.at<Vec3b>(i, j)[0];
					sumy += x*img.at<Vec3b>(i, j)[1];
					sumz += x*img.at<Vec3b>(i, j)[2];
				}
			}
		}
		if (!tot){

			flag = 1;
			cout << i1 << " " << j1 << endl;
		}
		else flag = 0;
		return tot ? Vec3b(sumx / tot, sumy / tot, sumz / tot) : Vec3b(0, 0, 0);
	}

}


#endif