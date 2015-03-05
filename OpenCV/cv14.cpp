//
//  cv14.cpp
//  OpenCV
//
//  Created by Armour on 2/24/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

void cv14(void) {
    //VideoCapture capture(0);
    Mat frame;
    Mat edges;
    Mat ele = getStructuringElement(MORPH_RECT, Size(2 * 5 + 1, 2 * 5 + 1), Point(5, 5));
    
    //bool stop = false;
    //while (!stop) {
        //capture >> frame;
        frame = imread("/Users/armour/Desktop/can/6.jpg");
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7, 7), 0, 0);
        //Canny(edges, edges, 10, 30, 3);
        threshold(edges, edges, 150, 255, THRESH_BINARY_INV);
        morphologyEx(edges, edges, MORPH_CLOSE, ele);
        morphologyEx(edges, edges, MORPH_OPEN, ele);

        vector<vector<Point>>contours;
        findContours(edges, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        //findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
        Mat result(edges.size(), CV_8U, Scalar(255));
        drawContours(result, contours, -1, Scalar(0), 1);
        
        // 包围盒
        Rect r0 = boundingRect(Mat(contours[0]));
        rectangle(result, r0, Scalar(0), 2);

        // 360度包围盒
        vector<vector<Point>>::const_iterator i;
        for (i = contours.begin(); i < contours.end(); i++)
            if (contourArea(Mat(*i)) > 5000) {
                RotatedRect rRect = minAreaRect(Mat(*i));
                Point2f vertices[4];
                rRect.points(vertices);
                for (int i = 0; i < 4; i++)
                    line(result, vertices[i], vertices[(i+1)%4], Scalar::all(0), 2);
            }

        // 包围圈
        float radius;
        Point2f center;
        minEnclosingCircle(Mat(contours[0]), center, radius);
        circle(result, Point2f(center), static_cast<int>(radius), Scalar(0), 2);
        
        // 多边形近似
        vector<Point>poly;
        approxPolyDP(Mat(contours[0]), poly, 5, true);
        vector<Point>::const_iterator itp = poly.begin();
        while (itp != (poly.end()-1)) {
            line(result, *itp, *(itp + 1), Scalar(0), 2);
            ++itp;
        }
        line(result, *(poly.begin()), *(poly.end() - 1), Scalar(20), 2);
        
        // 凸包
        vector<Point>hull;
        convexHull(Mat(contours[0]), hull);
        vector<Point>::const_iterator ith = hull.begin();
        while (ith != (hull.end()-1)) {
            line(result, *ith, *(ith + 1), Scalar(0), 2);
            ++ith;
        }
        line(result, *(hull.begin()), *(hull.end() - 1), Scalar(20), 2);

        // 力矩
        vector<vector<Point>>::const_iterator itc = contours.begin();
        while (itc != contours.end()) {
            Moments mom = moments(Mat(*itc++));
            circle(result, Point(mom.m10/mom.m00, mom.m01/mom.m00), 2, Scalar(0), 2);
        }
        //namedWindow("camera", CV_WINDOW_NORMAL);
        imshow("camera", result);
    //}
    waitKey(0);
}
