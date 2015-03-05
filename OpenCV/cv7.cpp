#include "my_cv.h"

void cv7(void) {
	Mat src = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", CV_LOAD_IMAGE_COLOR);
	Mat tmp, dst1, dst2;

	tmp = src;
	resize(tmp, dst1, Size(tmp.cols / 2, tmp.rows / 2), 0, 0, INTER_AREA);
	resize(tmp, dst2, Size(tmp.cols * 2, tmp.rows * 2), 0, 0, INTER_LINEAR);


	/*	// 测试不同的插值方式：放大二选一
    resize(dst1, dst1, Size(dst1.cols / 2, dst1.rows / 2), (0, 0), (0, 0), INTER_AREA);
	resize(dst1, dst1, Size(dst1.cols / 2, dst1.rows / 2), (0, 0), (0, 0), INTER_AREA);
	resize(dst1, dst1, Size(dst1.cols / 2, dst1.rows / 2), (0, 0), (0, 0), INTER_AREA);
	resize(dst1, dst1, Size(dst1.cols / 2, dst1.rows / 2), (0, 0), (0, 0), INTER_AREA);
	resize(dst1, dst1, Size(dst1.cols / 2, dst1.rows / 2), (0, 0), (0, 0), INTER_AREA);
	// 模糊
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	// 马赛克 = =
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	resize(dst1, dst1, Size(dst1.cols * 2, dst1.rows * 2), (0, 0), (0, 0), INTER_LINEAR);
	*/

	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	namedWindow("/2", CV_WINDOW_AUTOSIZE);
	namedWindow("*2", CV_WINDOW_AUTOSIZE);

	imshow("Original", src);
	imshow("/2", dst1);
	imshow("*2", dst2);

	waitKey(0);
}