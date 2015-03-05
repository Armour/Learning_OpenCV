#include "my_cv.h"

static Mat g_srcImage, g_srcGrayImage, g_dstImage;
static Mat g_gaussian, dst_laplace, abs_dst;

//Canny边缘检测相关变量
static Mat g_cannyDetectedEdges;
static int g_cannyLowThreshold = 1;	//TrackBarŒª÷√≤Œ ˝    

//Sobel边缘检测相关变量
static Mat g_sobelGradient_X, g_sobelGradient_Y;
static Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
static int g_sobelKernelSize = 1;	//TrackBarŒª÷√≤Œ ˝    

//Scharr滤波器相关变量
static Mat g_scharrGradient_X, g_scharrGradient_Y;
static Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;

static void on_Canny(int, void*);
static void on_Sobel(int, void*);
static void Scharr();
static void Laplace();

void cv8(void) {
    g_srcImage = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg");

	namedWindow("Original");
	imshow("Original", g_srcImage);

	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	cvtColor(g_srcImage, g_srcGrayImage, CV_BGR2GRAY);

	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	namedWindow("Sobel", CV_WINDOW_AUTOSIZE);

	createTrackbar("Threshold:", "Canny", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("Threshold:", "Sobel", &g_sobelKernelSize, 3, on_Sobel);

	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();

	Laplace();

	waitKey(0);
}

static void on_Canny(int, void*) {
    // 先使用3x3内核来降噪
    blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));
    
    // 运行我们的Canny算子
    Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);
    
    //先将g_dstImage内的所有元素设置为0
    g_dstImage = Scalar::all(0);
    
    //使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷到目标图g_dstImage中
    g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

    //显示效果图
    imshow("Canny", g_dstImage);
}

static void on_Sobel(int, void*) {
    // 求 X方向梯度
    Sobel(g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_X, g_sobelAbsGradient_X);//计算绝对值，并将结果转换成8位
    
    // 求Y方向梯度
    Sobel(g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);//计算绝对值，并将结果转换成8位
    
    // 合并梯度
    addWeighted(g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage);
    
    //显示效果图
    imshow("Sobel", g_dstImage);
    
}

static void Scharr() {
    // 求 X方向梯度
    Scharr(g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);//计算绝对值，并将结果转换成8位
    
    // 求Y方向梯度
    Scharr(g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);//计算绝对值，并将结果转换成8位
    
    // 合并梯度
    addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);
    
    //显示效果图
    imshow("Scharr", g_dstImage);
}

static void Laplace() {
    //使用高斯滤波消除噪声
    GaussianBlur(g_srcGrayImage, g_gaussian, Size(3, 3), 0, 0, BORDER_DEFAULT);
    
    //使用Laplace函数
    Laplacian(g_gaussian, dst_laplace, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    
    //计算绝对值，并将结果转换成8位  
    convertScaleAbs(dst_laplace, abs_dst);
    
    //显示效果图  
    imshow("Laplace", abs_dst);
    
}