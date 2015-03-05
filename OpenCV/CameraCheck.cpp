//
//  CameraCheck.cpp
//  OpenCV
//
//  Created by Armour on 2/24/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

static string input_image(int k) {
    string name = "/Users/armour/Desktop/OpenCV/CameraCheck/Image";
    ostringstream oss;
    oss << name << k;
    name = oss.str();
    name += ".jpg";
    return name;
}

static void GenData() {
    VideoCapture capture(1);
    Mat frame;
    Mat edges;
    int count = 0;
    bool stop = false;
    while (!stop) {
        capture >> frame;
        imshow("camera", frame);
        string name = input_image(count++);
        imwrite(name, frame);
        waitKey(1000);
        if (count > 100) stop = true;
    }
}

void CameraCheck(void) {
    //GenData();
    /*
    VideoCapture capture(1);
    Mat frame;
    Mat result;
    Mat tmp, tmp2;
    Mat R;
    Mat cameraMatrix2, distCoeffs2;

     //camera matrix:
     //[808.9572019831613, 0, 639.5;
     //0, 812.2736024571125, 479.5;
     //0, 0, 1]
     //distortion coeffs:
     //[-0.41812043512949;
     //0.192156197357496;
     //-0.001465331612662334;
     //-0.0001573659098307722;
     //-0.04243128384861684]

    
    FileStorage fs2("/Users/armour/Desktop/OpenCV/OpenCV/camera.xml", FileStorage::READ);
    fs2["camera_matrix"] >> cameraMatrix2;
    fs2["distortion_coefficients"] >> distCoeffs2;
    
    cout << "camera matrix: " << cameraMatrix2 << endl
    << "distortion coeffs: " << distCoeffs2 << endl;
    
    namedWindow("camera", CV_WINDOW_AUTOSIZE);
    namedWindow("undistort", CV_WINDOW_AUTOSIZE);
    
    while (true) {
        capture >> frame;
        resize(frame, tmp, Size(frame.cols / 2, frame.rows / 2));
        undistort(frame, result, cameraMatrix2, distCoeffs2);
        resize(result, tmp2, Size(result.cols / 2, result.rows / 2));
        imshow("camera", tmp);
        imshow("undistort", tmp2);
    }
    
    // projectPoints
    vector<Point2f> imagePoint;
    vector<Point3f> objectPoints;
    Vec3f rvec(0,0,0), tvec(0,0,0);
    Point3f newPoint;
    newPoint.x = 100;
    newPoint.y = 100;
    newPoint.z = 100;
    objectPoints.push_back(newPoint);
    projectPoints(objectPoints, rvec, tvec, cameraMatrix2, distCoeffs2, imagePoint);
    cout << imagePoint[0].x <<  " " << imagePoint[0].y << endl;*/

    Mat fuck = imread("/Users/armour/Desktop/CameraCheck copy/Image2.jpg");
    vector<Point2f>imageCorners;
    Size boardSize(8,8);
    bool found = findChessboardCorners(fuck, boardSize, imageCorners);
    drawChessboardCorners(fuck, boardSize, imageCorners, found);
    imshow("fuck~", fuck);
    waitKey();
    
}
