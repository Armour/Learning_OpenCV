#include "my_cv.h"

#define WINDOW_NAME1 "Corner1"
#define WINDOW_NAME2 "Corner2"

static Mat g_srcImage, g_srcImage1, g_grayImage;
static int thresh = 30; //当前阈值
static int max_thresh = 175; //最大阈值

static void CornerFast(void) {       // corner  (just like harris)
    Mat srcImageFast = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    vector<KeyPoint>keypoints;
    FastFeatureDetector fast(100);
    fast.detect(srcImageFast, keypoints);
    drawKeypoints(srcImageFast, keypoints, srcImageFast, Scalar(10, 10, 255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
    imshow("Fast", srcImageFast);
    waitKey(0);
}

static void on_CornerHarris(int, void*) {
    //---------------------------【1】定义一些局部变量-----------------------------
    Mat dstImage;//目标图
    Mat normImage;//归一化后的图
    Mat scaledImage;//线性变换后的八位无符号整型的图

    //---------------------------【2】初始化---------------------------------------
    //置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值
    dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
    g_srcImage1 = g_srcImage.clone();

    //---------------------------【3】正式检测-------------------------------------
    //进行角点检测
    cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
    // 归一化与转换
    normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(normImage, scaledImage);	//将归一化后的图线性变换成8位无符号整型

    //---------------------------【4】进行绘制-------------------------------------
    // 将检测到的，且符合阈值条件的角点绘制出来
    for (int j = 0; j < normImage.rows; j++)
    {
        for (int i = 0; i < normImage.cols; i++)
        {
            if ((int)normImage.at<float>(j, i) > thresh + 80)
            {
                circle(g_srcImage1, Point(i, j), 3, Scalar(10, 10, 255), 1, 8, 0);
                circle(scaledImage, Point(i, j), 3, Scalar(0, 10, 255), 1, 8, 0);
            }
        }
    }
    //---------------------------【4】显示最终效果---------------------------------
    imshow(WINDOW_NAME1, g_srcImage1);
    imshow(WINDOW_NAME2, scaledImage);
}

void cv9(void) {
    //【1】载入原始图并进行克隆保存
    g_srcImage = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", CV_LOAD_IMAGE_COLOR);
    imshow("Original", g_srcImage);
    g_srcImage1 = g_srcImage.clone();
    
    //【2】存留一张灰度图
    cvtColor(g_srcImage1, g_grayImage, CV_BGR2GRAY);
    
    //【3】创建窗口和滚动条
    namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
    createTrackbar("Threshold:", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);
    
    //【4】调用一次回调函数，进行初始化
    on_CornerHarris(0, 0);

    CornerFast();

    waitKey(0);
}
