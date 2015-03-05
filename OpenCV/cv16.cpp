#include "my_cv.h"

void cv16(void) {
    Mat src, dst;
    Mat warp_mat;     //多通道矩阵    warp_mat.create(3, 3, CV_32FC1);
    Point2f srcTri[4], dstTri[4];   //二维坐标下的点，类型为浮点
    
    src = imread( "/Users/armour/Desktop/OpenCV/Image/Test5.jpg", 1 );
    dst = src.clone();  //制作图像的完整拷贝
    dst.zeros(src.rows, src.cols, src.type());
    
    //计算矩阵仿射变换
    srcTri[0].x = 0;
    srcTri[0].y = 0;
    srcTri[1].x = src.rows;
    srcTri[1].y = 0;
    srcTri[2].x = 0;
    srcTri[2].y = src.cols;
    srcTri[3].x = src.rows;  //bot-right
    srcTri[3].y = src.cols;
    
    //改变目标图像大小
    dstTri[0].x = src.rows * 0.05;
    dstTri[0].y = src.cols * 0.33;
    dstTri[1].x = src.rows * 0.9;
    dstTri[1].y = src.cols * 0.25;
    dstTri[2].x = src.rows * 0.2;
    dstTri[2].y = src.cols * 0.7;
    dstTri[3].x = src.rows * 0.8;
    dstTri[3].y = src.cols * 0.9;
    
    warp_mat = getPerspectiveTransform(srcTri, dstTri);  //由三对点计算仿射变换
    warpPerspective(src, dst, warp_mat, Size(src.cols, src.rows));    //对图像做仿射变换
    imshow("Original", src);
    imshow("Perspective Warp", dst);
    waitKey(0);
}