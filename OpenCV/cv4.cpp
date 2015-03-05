#include "my_cv.h"

static Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4;
static int g_nBlurValue = 10;
static int g_nGaussianBlurValue = 6;
static int g_nMedianBlurValue = 10;
static int g_nBilateralFilterValue = 10;

// call－back function
static void on_Blur(int, void *);
static void on_GaussianBlur(int, void *);
static void on_MedianBlur(int, void *);
static void on_BilateralFilter(int, void*);

void cv4(void) {
    /*Mat src;
     Mat dstBlur3;
     Mat dstBlur5;
     Mat dstBlur7;
     Mat dstGaussianBlur3;
     Mat dstGaussianBlur5;
     Mat dstGaussianBlur7;
     Mat dstMedianBlur3;
     Mat dstMedianBlur5;
     Mat dstMedianBlur7;
     Mat dstBilateralFilter3;
     Mat dstBilateralFilter5;
     Mat dstBilateralFilter7;

     src = imread("Test5.jpg", CV_LOAD_IMAGE_COLOR);
     //salt(src);

     namedWindow("Original", CV_WINDOW_AUTOSIZE);
     namedWindow("Blur3", CV_WINDOW_AUTOSIZE);
     namedWindow("Blur5", CV_WINDOW_AUTOSIZE);
     namedWindow("Blur7", CV_WINDOW_AUTOSIZE);
     namedWindow("GaussianBlur3", CV_WINDOW_AUTOSIZE);
     namedWindow("GaussianBlur5", CV_WINDOW_AUTOSIZE);
     namedWindow("GaussianBlur7", CV_WINDOW_AUTOSIZE);
     namedWindow("MedianBlur3", CV_WINDOW_AUTOSIZE);
     namedWindow("MedianBlur5", CV_WINDOW_AUTOSIZE);
     namedWindow("MedianBlur7", CV_WINDOW_AUTOSIZE);
     namedWindow("BilateralFilter3", CV_WINDOW_AUTOSIZE);
     namedWindow("BilateralFilter5", CV_WINDOW_AUTOSIZE);
     namedWindow("BilateralFilter7", CV_WINDOW_AUTOSIZE);

     //主要应用是去除图像中的不相干细节，“不相干”是指与滤波掩膜尺寸相比较小的像素区域。
     blur(src, dstBlur3, Size(3, 3));
     blur(src, dstBlur5, Size(5, 5));
     blur(src, dstBlur7, Size(7, 7));
     //对去除服从正态分布的噪声很有效。
     GaussianBlur(src, dstGaussianBlur3, Size(3, 3), 0);
     GaussianBlur(src, dstGaussianBlur5, Size(5, 5), 0);
     GaussianBlur(src, dstGaussianBlur7, Size(7, 7), 0);
     //对处理椒盐噪声非常有效。
     medianBlur(src, dstMedianBlur3, 3);
     medianBlur(src, dstMedianBlur5, 5);
     medianBlur(src, dstMedianBlur7, 7);
     //同高斯滤波，但是不会把边缘平滑掉
     bilateralFilter(src, dstBilateralFilter3, 3, 3 * 2, 3 / 2);
     bilateralFilter(src, dstBilateralFilter5, 5, 5 * 2, 5 / 2);
     bilateralFilter(src, dstBilateralFilter7, 7, 7 * 2, 7 / 2);

     imshow("Original", src);
     imshow("Blur3", dstBlur3);
     imshow("Blur5", dstBlur5);
     imshow("Blur7", dstBlur7);
     imshow("GaussianBlur3", dstGaussianBlur3);
     imshow("GaussianBlur5", dstGaussianBlur5);
     imshow("GaussianBlur7", dstGaussianBlur7);
     imshow("MedianBlur3", dstMedianBlur3);
     imshow("MedianBlur5", dstMedianBlur5);
     imshow("MedianBlur7", dstMedianBlur7);
     imshow("BilateralFilter3", dstBilateralFilter3);
     imshow("BilateralFilter5", dstBilateralFilter5);
     imshow("BilateralFilter7", dstBilateralFilter7);
     */

    g_srcImage = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", CV_LOAD_IMAGE_COLOR);

    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();
    g_dstImage4 = g_srcImage.clone();

    namedWindow("Original", 1);
    imshow("Original", g_srcImage);

    namedWindow("Mean Filter", 1);
    namedWindow("Gaussian Filter", 1);
    namedWindow("Median Filter", 1);
    namedWindow("Bilateral Filter", 1);

    createTrackbar("Threshold:", "Mean Filter", &g_nBlurValue, 50, on_Blur);
    createTrackbar("Threshold:", "Gaussian Filter", &g_nGaussianBlurValue, 50, on_GaussianBlur);
    createTrackbar("Threshold:", "Median Filter", &g_nMedianBlurValue, 50, on_MedianBlur);
    createTrackbar("Threshold:", "Bilateral Filter", &g_nBilateralFilterValue, 50, on_BilateralFilter);

    on_Blur(g_nBlurValue, 0);
    on_GaussianBlur(g_nGaussianBlurValue, 0);
    on_MedianBlur(g_nMedianBlurValue, 0);
    on_BilateralFilter(g_nBilateralFilterValue, 0);

    waitKey(0);
}

static void on_Blur(int, void *) {
    blur(g_srcImage, g_dstImage1, Size(g_nBlurValue + 1, g_nBlurValue + 1), Point(-1, -1));
    imshow("Mean Filter", g_dstImage1);
}

static void on_GaussianBlur(int, void *) {
    GaussianBlur(g_srcImage, g_dstImage2, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
    imshow("Gaussian Filter", g_dstImage2);
}

static void on_MedianBlur(int, void *) {
    medianBlur(g_srcImage, g_dstImage3, g_nMedianBlurValue * 2 + 1);
    imshow("Median Filter", g_dstImage3);
}

static void on_BilateralFilter(int, void *) {
    bilateralFilter(g_srcImage, g_dstImage4, g_nBilateralFilterValue, g_nBilateralFilterValue * 2, g_nBilateralFilterValue / 2);
    imshow("Bilateral Filter", g_dstImage4);
}

// 噪点处理
static void salt(Mat &I, int n = 6000) {
    for (int k = 0; k < n; k++) {
        int i = rand() % I.cols;
        int j = rand() % I.rows;
        if (I.channels()) {
            I.at<uchar>(j, i) = 255;
        }
        else {
            I.at<Vec3b>(j, i)[0] = 255;
            I.at<Vec3b>(j, i)[1] = 255;
            I.at<Vec3b>(j, i)[2] = 255;
        }
    }
}

/*	//opencv 1.0:
 IplImage *in = cvLoadImage("Test5.jpg");
 IplImage *out = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);
 cvSmooth(in, out, CV_BLUR, 3, 3);
 cvNamedWindow("In", CV_WINDOW_AUTOSIZE);
 cvNamedWindow("Out", CV_WINDOW_AUTOSIZE);
 cvShowImage("In", in);
 cvShowImage("Out", out);
 */
