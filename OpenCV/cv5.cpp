#include "my_cv.h"

#define TYPE_MORPH_RECT      (0)
#define TYPE_MORPH_CROSS     (1)
#define TYPE_MORPH_ELLIPSE   (2)
#define MAX_ELE_TYPE         (2)
#define MAX_ELE_SIZE         (20)

static void Erosion(int, void *);
static void Dilation(int, void *);

static string erode_wn = "eroding demo";
static string dilate_wn = "dilating demo";

static Mat src;
static Mat erode_dst;
static Mat dilate_dst;
static int erode_ele_type;
static int dilate_ele_type;
static int erode_ele_size;
static int dilate_ele_size;

void cv5(void) {
	src = imread("/Users/armour/Desktop/OpenCV/Image/Test5.jpg", CV_LOAD_IMAGE_COLOR);

	// Windows
	namedWindow(erode_wn, WINDOW_AUTOSIZE);
	namedWindow(dilate_wn, WINDOW_AUTOSIZE);
	
	// Track Bar for Erosion
	createTrackbar("Element Type\n0:Rect\n1:Cross\n2:Ellipse", erode_wn,
		&erode_ele_type, MAX_ELE_TYPE, Erosion);  // callback @Erosion
	createTrackbar("Element Size: 2n+1", erode_wn, &erode_ele_size, MAX_ELE_SIZE, Erosion);
	
	// Track Bar for Dilation
	createTrackbar("Element Type\n0:Rect\n1:Cross\n2:Ellipse", dilate_wn,
		&dilate_ele_type, MAX_ELE_TYPE, Dilation);  // callback @Dilation
	createTrackbar("Element Size: 2n+1", dilate_wn, &dilate_ele_size, MAX_ELE_SIZE, Dilation);

	/*	Track Bar:
		CV_EXPORTS int createTrackbar( const string& trackbarname, const string& winname,
                           int* value, int count,
                           TrackbarCallback onChange=0,
     void* userdata=0);
     trackbarname为滑动条的名称，将会显示在滑动条的前面，参见结果中的图片显示；
     winname为窗口名；
     value为滑动条关联的变量，如上面程序中第一个滑动条关联到erode_ele_type，表示——当滑动条滑动变化时，erode_ele_type的值发生响应的变化；
     count表示滑动条能滑动到的最大值；
     TrackbarCallback onChange其实是这个函数的关键，是滑动条变化时调用的回调函数。
     当滑动条滑动时，value值发生变化，系统立刻调用onChange函数，执行相关的操作，回调函数的定义形式是固定的： void onChange(int, void *)
     */

	// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	waitKey(0);
}

static void Erosion(int, void *) {
	int erode_type;

	switch (erode_ele_type) {
	case TYPE_MORPH_RECT:
		erode_type = MORPH_RECT;
		break;
	case TYPE_MORPH_CROSS:
		erode_type = MORPH_CROSS;
		break;
	case TYPE_MORPH_ELLIPSE:
		erode_type = MORPH_ELLIPSE;
		break;
	default:
		erode_type = MORPH_RECT;
		break;
	}

	Mat ele = getStructuringElement(erode_type, Size(2 * erode_ele_size + 1, 2 * erode_ele_size + 1),
		Point(erode_ele_size, erode_ele_size));

	erode(src, erode_dst, ele);

	imshow(erode_wn, erode_dst);
}

static void Dilation(int, void *) {
	int dilate_type;

	switch (dilate_ele_type) {
	case TYPE_MORPH_RECT:
		dilate_type = MORPH_RECT;
		break;
	case TYPE_MORPH_CROSS:
		dilate_type = MORPH_CROSS;
		break;
	case TYPE_MORPH_ELLIPSE:
		dilate_type = MORPH_ELLIPSE;
		break;
	default:
		dilate_type = MORPH_RECT;
		break;
	}

	Mat ele = getStructuringElement(dilate_type, Size(2 * dilate_ele_size + 1, 2 * dilate_ele_size + 1),
		Point(dilate_ele_size, dilate_ele_size));

	dilate(src, dilate_dst, ele);

	imshow(dilate_wn, dilate_dst);
}