#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

using namespace std;

Mat myLaplace(Mat img, int type) {
	//拉普拉斯四种模板
	vector<vector<int> > laplacetemplate(3, vector<int>(3));
	if (type == 1) {
		laplacetemplate = { {0,1,0},
							{1,-4,1},
							{0,1,0} };
	}
	else if (type == 2) {
		laplacetemplate = { {1,1,1},
							{1,-8,1},
							{1,1,1} };
	}
	else if (type == 3) {
		laplacetemplate = { {0,-1,0},
							{-1,-4,-1},
							{0,-1,0} };
	}
	else if (type == 4) {
		laplacetemplate = { {-1,1,-1},
							{1,-8,1},
							{-1,1,-1} };
	}
	else {
		cerr << "type is not avaiable" << endl;
	}

	Mat res(img.rows, img.cols, img.type());

	if (img.channels() == 1) {
		GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);
		for (int x = 1; x < img.rows - 1; x++) {
			for (int y = 1; y < img.cols - 1; y++) {
				int val = 0;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (type == 1 || type == 2) {
							val += img.at<uchar>(x - 1 + i, y - 1 + i) * laplacetemplate[i][j];
						}
						else if (type == 3 || type == 4) {
							val += img.at<uchar>(x - 1 + i, y - 1 + i) * laplacetemplate[i][j];
						}
						
					}
				}
				res.at<uchar>(x, y) = uchar(val);
			}
		}
	}

	return res;
}

int main() {
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.png", 0);
	
	int type = 3;

	Mat res = myLaplace(img, type);							

	imshow("原图", img);
	imshow("type = 1,平滑结果图", res);

	waitKey(0);
}