//
//  cv19.cpp
//  OpenCV
//
//  Created by Armour on 2/27/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

static void gray(void) {
    int histSize[1];
    float hranges[2];
    const float *ranges[1];
    int channels[1];
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;

    Mat srcImage1, srcImage2;
    MatND hist1, hist2;
    srcImage1 = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg", 0);
    srcImage2 = imread("/Users/armour/Desktop/OpenCV/Image/Comp2.jpg", 0);
    calcHist(&srcImage1, 1, channels, Mat(), hist1, 1, histSize, ranges, true);
    calcHist(&srcImage2, 1, channels, Mat(), hist2, 1, histSize, ranges, true);
    normalize(hist1, hist1, 1.0);
    normalize(hist2, hist2, 1.0);

    float sum1 = 0;
    float sum2 = 0;
    for (int i = 0; i < 256; i++) {
        //cout << hist1.at<float>(i) << endl;
        sum1 += hist1.at<float>(i);
        sum2 += hist2.at<float>(i);
    }
    cout << sum1 << endl;
    cout << sum2 << endl;
    cout << "Correl:" << compareHist(hist1, hist2, CV_COMP_CORREL) << endl;
    cout << "Chisqr:" << compareHist(hist1, hist2, CV_COMP_CHISQR) << endl;
    cout << "Intersect:" << compareHist(hist1, hist2, CV_COMP_INTERSECT) << endl;
    cout << "Bhattacharyya:" << compareHist(hist1, hist2, CV_COMP_BHATTACHARYYA) << endl;

    //for (int i=0; i<256; i++)
    //    cout << "Value" << i << " : " << hist1.at<float>(i) << " " << hist2.at<float>(i) << endl;

    Mat histImg1(histSize[0], histSize[0], CV_8U, Scalar(255));
    Mat histImg2(histSize[0], histSize[0], CV_8U, Scalar(255));
    double maxVal1, maxVal2 = 0;
    double minVal1, minVal2 = 0;
    minMaxLoc(hist1, &minVal1, &maxVal1, 0, 0);
    minMaxLoc(hist2, &minVal2, &maxVal2, 0, 0);
    int hpt = static_cast<int>(0.9 * histSize[0]);
    for (int h = 0; h < histSize[0]; h++) {
        float binval1 = hist1.at<float>(h);
        int intensity1 = static_cast<int>(binval1 / maxVal1 * hpt);
        line(histImg1, Point(h, histSize[0]), Point(h, histSize[0] - intensity1), Scalar::all(0));

        float binval2 = hist2.at<float>(h);
        int intensity2 = static_cast<int>(binval2 / maxVal2 * hpt);
        line(histImg2, Point(h, histSize[0]), Point(h, histSize[0] - intensity2), Scalar::all(0));
    }
    /*
     Mat thresholded;
     threshold(srcImage1, thresholded, 80, 255, THRESH_BINARY);
     imshow("Thresholded1", thresholded);
    */
    imshow("Original1", srcImage1);
    imshow("Original2", srcImage2);
    imshow("Histogram1", histImg1);
    imshow("Histogram2", histImg2);

    Mat equalImg1, equalImg2;
    Mat histImg3(histSize[0], histSize[0], CV_8UC1, Scalar(255));
    Mat histImg4(histSize[0], histSize[0], CV_8UC1, Scalar(255));
    equalImg1 = srcImage1.clone();
    equalImg2 = srcImage2.clone();
    equalizeHist(srcImage1, equalImg1);
    equalizeHist(srcImage2, equalImg2);
    calcHist(&equalImg1, 1, channels, Mat(), hist1, 1, histSize, ranges);
    calcHist(&equalImg2, 1, channels, Mat(), hist2, 1, histSize, ranges);

    maxVal1 = maxVal2 = 0;
    minVal1 = minVal2 = 0;
    minMaxLoc(hist1, &minVal1, &maxVal1, 0, 0);
    minMaxLoc(hist2, &minVal2, &maxVal2, 0, 0);
    hpt = static_cast<int>(0.9 * histSize[0]);
    for (int h = 0; h < histSize[0]; h++) {
        float binval1 = hist1.at<float>(h);
        int intensity1 = static_cast<int>(binval1 / maxVal1 * hpt);
        line(histImg3, Point(h, histSize[0]), Point(h, histSize[0] - intensity1), Scalar::all(0));

        float binval2 = hist2.at<float>(h);
        int intensity2 = static_cast<int>(binval2 / maxVal2 * hpt);
        line(histImg4, Point(h, histSize[0]), Point(h, histSize[0] - intensity2), Scalar::all(0));
    }

    imshow("Equalize1", equalImg1);
    imshow("Equalize2", equalImg2);
    imshow("HistEqual1", histImg3);
    imshow("HistEqual2", histImg4);

    /*int minValue = 100;
    int imin = 0;
    for (; imin < histSize[0]; imin++) {
        if (hist1.at<float>(imin) > minValue)
            break;
    }
    int imax = histSize[0] - 1;
    for (; imax >0; imax--) {
        if (hist1.at<float>(imax) > minValue)
           break;
    }

    int dim(256);
    Mat lookup(1, &dim, CV_8U);
    for (int i = 0; i < 256; i++) {
        if (i < imin) lookup.at<uchar>(i) = 0;
        else if (i > imax) lookup.at<uchar>(i) = 255;
        else lookup.at<uchar>(i) = static_cast<uchar>(255.0 * (i - imin) / (imax + imin) * 0.5);
    }*/

    Mat result;
    applyColorMap(srcImage1, result, 5);
    //applyColorMap(srcImage1, result, lookup);
    imshow("Colormap_Ocean", result);

    Mat imageROI;
    Mat imageBack;
    MatND histROI;

    imageROI = Mat(srcImage1, Rect(430, 250, 50, 50));
    calcHist(&imageROI, 1, channels, Mat(), histROI, 1, histSize, ranges, true);
    normalize(histROI, histROI);
    calcBackProject(&srcImage1, 1, channels, histROI, imageBack, ranges, 255.0);
    imshow("BackProject", imageBack);

    waitKey(0);
}

static void rgb(void) {
    int channels[3] = {0, 1, 2};
    int histSize[3] = {256, 256, 256};
    float hranges[2] = {0, 255};
    const float *ranges[3]= {hranges, hranges, hranges};

    Mat srcImage1, srcImage2;
    MatND hist1, hist2;
    srcImage1 = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg", 1);
    srcImage2 = imread("/Users/armour/Desktop/OpenCV/Image/Comp2.jpg", 1);

    SparseMat histS1(3, histSize, CV_32F);
    SparseMat histS2(3, histSize, CV_32F);
    calcHist(&srcImage1, 1, channels, Mat(), histS1, 3, histSize, ranges);
    calcHist(&srcImage2, 1, channels, Mat(), histS2, 3, histSize, ranges);

    int sum = 0;
    int rgb[] = {256, 256, 256};
    for (int i = 0; i < 256; i++) {
        rgb[0] = i;
        for (int j = 0; j < 256; j++) {
            rgb[1] = j;
            for (int k = 0; k < 256; k++) {
                rgb[2] = k;
                //cout << i << " " << j << " " << k << " " << histS1.ref<float>(rgb) << endl;
                sum += histS1.ref<float>(rgb);
            }
        }
    }
    cout << sum ;

    /*Mat histImg1(histSize[0], histSize[0], CV_32FC3, Scalar(255));
    Mat histImg2(histSize[0], histSize[0], CV_32FC3, Scalar(255));
    double maxVal1, maxVal2 = 0;
    double minVal1, minVal2 = 0;
    minMaxLoc(histS1, &minVal1, &maxVal1, 0, 0);
    minMaxLoc(histS2, &minVal2, &maxVal2, 0, 0);
    int hpt = static_cast<int>(0.9 * histSize[0]);
    for (int h = 0; h < histSize[0]; h++) {
        float binval1 = hist1.at<float>(h);
        int intensity1 = static_cast<int>(binval1 / maxVal1 * hpt);
        line(histImg1, Point(h, histSize[0]), Point(h, histSize[0] - intensity1), Scalar::all(0));

        float binval2 = hist2.at<float>(h);
        int intensity2 = static_cast<int>(binval2 / maxVal2 * hpt);
        line(histImg2, Point(h, histSize[0]), Point(h, histSize[0] - intensity2), Scalar::all(0));
    }
    imshow("Original1", srcImage1);
    imshow("Original2", srcImage2);
    imshow("Histogram1", histImg1);
    imshow("Histogram2", histImg2);
     */

    /*Mat thresholded;
     threshold(srcImage1, thresholded, 80, 255, THRESH_BINARY);
     imshow("Thresholded1", thresholded);*/

    waitKey(0);
}

static void hsv(void) {
    Mat src = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", 1);
    Mat hsv;
    cvtColor(src, hsv, CV_BGR2HSV);

    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( &hsv, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(h*scale, s*scale),
                      Point( (h+1)*scale - 1, (s+1)*scale - 1),
                      Scalar::all(intensity),
                      CV_FILLED );
        }
    imshow( "Source", src );
    imshow( "H-S Histogram", histImg );
    waitKey(0);
}

void cv19(void) {
    gray();
    //rgb();
    //hsv();
}
