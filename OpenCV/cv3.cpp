#include "my_cv.h"

void cv3(void) {
	Mat src1;
	Mat src2;
	Mat dst;
	double alpha = 0.5;
	double beta;
	src1 = imread("/Users/armour/Desktop/OpenCV/Image/Test.jpg", CV_LOAD_IMAGE_COLOR);
	src2 = imread("/Users/armour/Desktop/OpenCV/Image/Test2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat imageROI = src1(Rect(100, 100, src2.cols, src2.rows));
	beta = 1 - alpha;
	addWeighted(imageROI, alpha, src2, beta, 0.0, dst);
    //dst = imageROI * 0.5 + src2 *0.5;
	namedWindow("Addweighted", CV_WINDOW_NORMAL);
	imshow("Addweighted", dst);
	waitKey(0);
}