//
//  FindContours.cpp
//  OpenCV
//
//  Created by Armour on 2/28/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

static Mat src;
static Mat dstOpen;
static Mat dstClose;
static Mat dstGradient;
static Mat dstTophat;
static Mat dstBlackhat;
static Mat dstErode;
static Mat dstDilate;
static Mat dstGradientGray;
static Mat dstFlood;
static Mat dstErodeFlood;
static Mat dstFloodGray;

void FindContours(void) {
    src = imread("/Users/armour/Desktop/can/5.jpg", CV_LOAD_IMAGE_COLOR);
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
    morphologyEx(src, dstClose, MORPH_CLOSE, ele);
    morphologyEx(src, dstOpen, MORPH_OPEN, ele);
    morphologyEx(src, dstBlackhat, MORPH_BLACKHAT, ele);

    Rect comp;
    dstFlood = src.clone();
    floodFill(dstFlood, Point(50,300), Scalar(255, 255, 255), &comp , Scalar(5, 5, 5), Scalar(5, 5, 5));

    Rect comp2;
    dstErodeFlood = dstErode.clone();
    floodFill(dstErodeFlood, Point(50,300), Scalar(255, 255, 255), &comp2 , Scalar(5, 5, 5), Scalar(5, 5, 5));

    dstGradientGray = dstGradient.clone();
    cvtColor(dstGradientGray, dstGradientGray, CV_BGR2GRAY);
    GaussianBlur(dstGradientGray, dstGradientGray, Size(7, 7), 0, 0);
    threshold(dstGradientGray, dstGradientGray, 80, 255, CV_THRESH_BINARY);
    //int blockSize = 5;
    //int offset = 11;
    //adaptiveThreshold(edges, edges, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, offset);

    dstFloodGray = dstFlood.clone();
    cvtColor(dstFloodGray, dstFloodGray, CV_BGR2GRAY);
    GaussianBlur(dstFloodGray, dstFloodGray, Size(7, 7), 0, 0);
    threshold(dstFloodGray, dstFloodGray, 150, 255, CV_THRESH_BINARY_INV);
    //int blockSize = 5;
    //int offset = 11;
    //adaptiveThreshold(edges, edges, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, offset);

    Mat rst2 = src.clone();
    vector<vector<Point>>contours2;
    findContours(dstFloodGray, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //findContours(dstFloodGray, contours2, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    Mat result2(dstFloodGray.size(), CV_8U, Scalar(255));
    drawContours(result2, contours2, -1, Scalar(0), 1);

    vector<vector<Point>>::const_iterator i;
    for (i = contours2.begin(); i < contours2.end(); i++)
        if (contourArea(Mat(*i)) > 15000) {
            //Rect r0 = boundingRect(Mat(*i));
            //rectangle(src, r0, Scalar::all(0), 2);
            //fitEllipse(Mat(*i));
            //cout << contourArea(Mat(*i)) << endl;
            RotatedRect rRect = minAreaRect(Mat(*i));
            Point2f vertices[4];
            rRect.points(vertices);
            for (int i = 0; i < 4; i++)
                line(rst2, vertices[i], vertices[(i+1)%4], Scalar::all(0), 2);

        }

    Mat rst1 = src.clone();
    vector<vector<Point>>contours;
    findContours(dstGradientGray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //findContours(dstGradient, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    Mat result(dstGradientGray.size(), CV_8U, Scalar(255));
    drawContours(result, contours, -1, Scalar(0), 1);

    //vector<vector<Point>>::const_iterator i;
    for (i = contours.begin(); i < contours.end(); i++)
        if (contourArea(Mat(*i)) > 15000) {
            //Rect r0 = boundingRect(Mat(*i));
            //rectangle(src, r0, Scalar::all(0), 2);
            //fitEllipse(Mat(*i));
            //cout << contourArea(Mat(*i)) << endl;
            RotatedRect rRect = minAreaRect(Mat(*i));
            Point2f vertices[4];
            rRect.points(vertices);
            for (int i = 0; i < 4; i++)
                line(rst1, vertices[i], vertices[(i+1)%4], Scalar::all(0), 2);

        }

    imshow("ErodeFloodfill", dstErodeFlood);
    imshow("Floodfill", dstFlood);
    imshow("FloodfillGray", dstFloodGray);
    imshow("Erode", dstErode);
    imshow("Dilate", dstDilate);
    imshow("Open", dstOpen);
    imshow("Close", dstClose);
    imshow("Tophat", dstTophat);
    imshow("Blackhat", dstBlackhat);
    imshow("Gradient", dstGradient);
    imshow("GradientGray", dstGradientGray);
    imshow("Result", rst1);
    imshow("Result2", rst2);

    waitKey();
}