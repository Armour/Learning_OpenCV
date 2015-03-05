//
//  cv18.cpp
//  OpenCV
//
//  Created by Armour on 2/27/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

/*void cv18(void) {
    Mat src, gray;
    src = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg");
    cvtColor( src, gray, CV_BGR2GRAY );
    //创建MSER类
    MSER mser;
    //用于组块区域的像素点集
    vector<vector<Point>> regions;
    mser(gray, regions, Mat());
    //在灰度图像中用椭圆形绘制组块
    for (int i = 0; i < regions.size(); i++) {
        ellipse(gray, fitEllipse(regions[i]), Scalar(255));
    }
    imshow("mser", gray);
    waitKey(0);
}*/

void cv18(void) {
    Mat image = imread("/Users/armour/Desktop/OpenCV/Image/Pedestrian3.jpg");

    // 定义HOG对象
    HOGDescriptor hog; // 采用默认参数

    // 设置SVM分类器
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());   // 采用已经训练好的行人检测分类器

    // 在测试图像上检测行人区域
    vector<cv::Rect> regions;
    hog.detectMultiScale(image, regions, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 1);

    // 显示
    for (size_t i = 0; i < regions.size(); i++) {
        rectangle(image, regions[i], Scalar(0, 0, 255),2);  //对判定是行人的区域画一个正方形标记一下。
    }

    imshow("hog", image);
    waitKey(0);
}