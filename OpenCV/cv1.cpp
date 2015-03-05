#include "my_cv.h"

void cv1(void) {
	Mat image;
	image = imread("/Users/armour/Desktop/OpenCV/Image/Test.jpg", CV_LOAD_IMAGE_COLOR);
	if (!image.data) {
		
	}
	namedWindow("Original Image", CV_WINDOW_NORMAL);
	imshow("Original Image", image);

	Mat result;
	flip(image, result, -2);

	namedWindow("Output Image", CV_WINDOW_NORMAL);
	imshow("Output Image", result);

	waitKey(0);
}