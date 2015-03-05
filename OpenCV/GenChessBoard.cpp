//The example of using BPNetwork in OpenCV
#include "my_cv.h"

#define numx 9
#define numy 9
#define size 200

void GenChessBoard(void) {
    IplImage* image = cvCreateImage(cvSize(numx*size, numy*size), 8, 1);
    ///生成黑白条
    for(int i = 0; i < image->height; i++) {
        uchar* data = (uchar*)image->imageData + image->widthStep*i;
        for(int j = 0; j < image->width; j++) {
            if ((j/size)%2 == 1)
                *data=255;
            else
                *data=0;
            data++;
        }
    }
    //生成棋盘格
    for(int i = 0; i < image->height; i++) {
        if ((i/size)%2==1) {
            uchar* data = (uchar*)image->imageData + image->widthStep*i;
            for(int j = 0; j < image->width; j++) {
                *data = 255 - *data;
                data++;
            }
        }
    }
    cvSaveImage("/Users/armour/Desktop/OpenCV/OpenCV/chessboard.jpg", image);
}