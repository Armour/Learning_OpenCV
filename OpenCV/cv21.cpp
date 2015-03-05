//
//  cv21.cpp
//  OpenCV
//
//  Created by Armour on 3/2/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

void cv21(void) {
    Mat image = imread("/Users/armour/Desktop/can/6.jpg");
    Rect rectangle(30, 220, 1500, 500);
    Mat result;
    Mat imageROI(image, rectangle);
    Mat bgModel, fgModel;
    grabCut(image, result, rectangle, bgModel, fgModel, 5, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);
    Mat foreground(image.size(), CV_8UC3, Scalar::all(255));
    image.copyTo(foreground, result);

    //result = result &1;
    //Mat foreground2(image.size(), CV_8UC3, Scalar::all(255));
    //image.copyTo(foreground2, result);

    imshow("ROI", imageROI);
    imshow("result", foreground);
    //imshow("result2", foreground2);
    waitKey();
}