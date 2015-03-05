#include "my_cv.h"

void cv10(void) {
    Mat srcImage = imread("/Users/armour/Desktop/OpenCV/Image/Test4.jpg");
    Mat midImage, dstImage;
    
    imshow("Original", srcImage);

    cvtColor(srcImage, midImage, CV_BGR2GRAY);
    GaussianBlur(midImage, midImage, Size(11, 11), 0, 0);
    
    // 霍夫圆变换
    vector<Vec3f> circles;
    HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
    
    // 依次在图中绘制出圆
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //绘制圆心
        circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        //绘制圆轮廓
        circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
    }
     
    imshow("HoughCircle", srcImage);
    waitKey(0);
    
}