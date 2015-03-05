#include "my_cv.h"

static Mat g_srcImage, g_dstImage, g_midImage;
static vector<Vec4i> g_lines;
static int g_nthreshold = 100;

static void on_HoughLines(int, void*);//回调函数

void cv11(void) {
    Mat g_srcImage = imread("/Users/armour/Desktop/OpenCV/Image/Test6.jpg");
    imshow("Original", g_srcImage);
    
    //创建滚动条
    namedWindow("HoughLineP", 1);
    createTrackbar("Threshold:", "HoughLineP", &g_nthreshold, 200, on_HoughLines);
    
    //进行边缘检测和转化为灰度图
    Canny(g_srcImage, g_midImage, 50, 200, 3);//进行一次canny边缘检测
    cvtColor(g_midImage, g_dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图
    
    //调用一次回调函数，调用一次HoughLinesP函数
    on_HoughLines(g_nthreshold, 0);
    HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);
    
    //显示效果图
    imshow("HoughLineP", g_dstImage);
    waitKey(0);
}

static void on_HoughLines(int, void*) {
    //定义局部变量储存全局变量
    Mat dstImage = g_dstImage.clone();
    Mat midImage = g_midImage.clone();
    
    //调用HoughLinesP函数
    vector<Vec4i> mylines;
    HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);
    
    //循环遍历绘制每一条线段
    for (size_t i = 0; i < mylines.size(); i++) {
        Vec4i l = mylines[i];
        line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, CV_AA);
    }
    //显示图像  
    imshow("HoughLineP", dstImage);
    
}