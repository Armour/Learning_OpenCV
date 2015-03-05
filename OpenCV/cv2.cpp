#include "my_cv.h"

void cv2(void) {    // three camera at the same time =w=
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		//exit
    }
    VideoCapture capture1(1);
    if (!capture1.isOpened()) {
        //exit
    }
    VideoCapture capture2(2);
    if (!capture2.isOpened()) {
        //exit
    }

	Mat frame, frame1, frame2;
	Mat edges;

	bool stop = false;
	while (!stop) {
		capture >> frame;
        capture1 >> frame1;
        capture2 >> frame2;
		//cvtColor(frame, edges, CV_BGR2GRAY);
		//GaussianBlur(edges, edges, Size(7, 7), 0, 0);
		//Canny(edges, edges, 10, 30, 3);
		//int blockSize = 5;
		//int offset = 15;
		//adaptiveThreshold(edges, edges, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, offset);
		imshow("camera", frame);
        imshow("camera1", frame1);
        imshow("camera2", frame2);
    }
    waitKey(0);
}