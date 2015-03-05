#include "my_cv.h"

//全局变量
static Mat src1, src1_gray, src2, src2_gray;

static int maxCorners = 500;
static int maxTrackbar = 175;

static string source_window1 = "Shi-Tomasi_1";
static string source_window2 = "Shi-Tomasi_2";
static string refine_window1 = "Subpix1";
static string refine_window2 = "Subpix2";

void goodFeaturesToTrack_Demo(int, void*)
{
    //参数初始化
    if(maxCorners < 1)//允许返回的最多角点个数
        maxCorners = 1;
    vector<Point2f> corners1,corners2;//角点容器
    vector<Point2f> corners1_sub,corners2_sub;//角点容器
    double qualityLevel = 0.01;//最小特征值小于qualityLevel*最大特征值的点将被忽略
    double minDistance = 10;//两角点间最小距离
    int blockSize = 3;//邻域尺寸
    bool useHarrisDetector = false;//是否使用Harris
    double k = 0.04;

    //拷贝原图
    Mat src1_copy = src1.clone();
    Mat src2_copy = src2.clone();
    Mat src1_refine_copy = src1.clone();
    Mat src2_refine_copy = src2.clone();

    //调用函数进行Shi-Tomasi角点检测
    goodFeaturesToTrack( src1_gray,
                        corners1,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        useHarrisDetector,
                        k );
    goodFeaturesToTrack( src2_gray,
                        corners2,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        useHarrisDetector,
                        k );
 

    //画出角点
    for( int i = 0; i < corners1.size(); i++ )
    {
        circle( src1_copy, corners1[i], 4, Scalar(0,255,255), 2, 8, 0);
        circle( src2_copy, corners2[i], 4, Scalar(0,255,255), 2, 8, 0);
    }

    //显示图像
    imshow( source_window1, src1_copy );
    imshow( source_window2, src2_copy );

    /// 角点位置精准化参数
    Size winSize = Size( 5, 5 );
    Size zeroZone = Size( -1, -1 );
    TermCriteria criteria = TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,
                                         maxCorners, //maxCount=40
                                         0.001 );	//epsilon=0.001
    /// 计算精准化后的角点位置
    cornerSubPix( src1_gray, corners1, winSize, zeroZone, criteria );
    cornerSubPix( src2_gray, corners2, winSize, zeroZone, criteria );

    /// 显示精准化后的角点
    for( int i = 0; i < corners1.size(); i++ )
        circle( src1_refine_copy, corners1[i], 4, Scalar(255,0,255), 2, 8, 0 );
    for( int i = 0; i < corners2.size(); i++ )
        circle( src2_refine_copy, corners2[i], 4, Scalar(255,0,255), 2, 8, 0 );

    // 显示亚像素图像
    imshow( refine_window1, src1_refine_copy );
    imshow( refine_window2, src2_refine_copy );
}

void cv17(void)
{
    //加载源图并转换为灰度图
    src1 = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg");
    src2 = imread("/Users/armour/Desktop/OpenCV/Image/Comp2.jpg");
    cvtColor( src1, src1_gray, CV_BGR2GRAY );
    cvtColor( src2, src2_gray, CV_BGR2GRAY );

    //创建窗口
    namedWindow( source_window1, CV_WINDOW_AUTOSIZE );
    namedWindow( source_window2, CV_WINDOW_AUTOSIZE );

    //创建滑块条，调节允许的角点个数
    createTrackbar( "corner number:", source_window1, &maxCorners, maxTrackbar, goodFeaturesToTrack_Demo );

    goodFeaturesToTrack_Demo( 0, 0 );

    waitKey(0);
}
