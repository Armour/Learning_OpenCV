#include "my_cv.h"

static Mat src;
static Mat dstOpen;
static Mat dstClose;
static Mat dstGradient;
static Mat dstTophat;
static Mat dstBlackhat; 
static Mat dstErode;
static Mat dstDilate;

void cv6(void) {
    //src = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", CV_LOAD_IMAGE_COLOR);
    src = imread("/Users/armour/Desktop/can/9.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Erode", WINDOW_AUTOSIZE);
	namedWindow("Dilate", WINDOW_AUTOSIZE);
	namedWindow("Open", WINDOW_AUTOSIZE);
	namedWindow("Close", WINDOW_AUTOSIZE);
	namedWindow("Gradient", WINDOW_AUTOSIZE);
	namedWindow("Tophat", WINDOW_AUTOSIZE);
	namedWindow("Blackhat", WINDOW_AUTOSIZE);
	namedWindow("Floodfill", WINDOW_AUTOSIZE);

    Mat ele = getStructuringElement(MORPH_RECT, Size(2 * 5 + 1, 2 * 5 + 1), Point(5, 5));
    morphologyEx(src, dstGradient, MORPH_GRADIENT, ele);
    morphologyEx(src, dstErode, MORPH_ERODE, ele);
    morphologyEx(src, dstTophat, MORPH_TOPHAT, ele);
    morphologyEx(src, dstDilate, MORPH_DILATE, ele);
    morphologyEx(src, dstOpen, MORPH_OPEN, ele);
    morphologyEx(src, dstClose, MORPH_CLOSE, ele);
	morphologyEx(src, dstBlackhat, MORPH_BLACKHAT, ele);

    Rect comp;
	floodFill(src, Point(50,300), Scalar(255, 255, 255), &comp , Scalar(10, 10, 10), Scalar(10, 10, 10));

	imshow("Floodfill", src);
	imshow("Erode", dstErode);
	imshow("Dilate", dstDilate);
	imshow("Open", dstOpen);
	imshow("Close", dstClose);
	imshow("Gradient", dstGradient);
	imshow("Tophat", dstTophat);
	imshow("Blackhat", dstBlackhat);

	waitKey(0);
}