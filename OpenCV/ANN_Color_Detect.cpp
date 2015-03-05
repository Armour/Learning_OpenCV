#include "my_cv.h"

#define PIEXLS (128 * 96)

/*static float correct(Mat &predict, Mat &answer) {
	float sum = 0;
	for (int i = 0; i < answer.rows; i++) {
		if (predict.at<float>(i, 0) != answer.at<float>(i, 0))
			sum += 1;
	}
	return (1 - sum / answer.rows) * 100;
}*/

static string input_image(int k, string str) {
	string name = "/Users/armour/Desktop/OpenCV/Color_Detect_Data/";
	name += str;
	name += "/Image";
	ostringstream oss;
	oss << name << k;
	name = oss.str();
	name += ".jpg";
	return name;
}

static void GenData() {
	VideoCapture capture(0);
	Mat frame;
	Mat edges;
	int count = 0;
	bool stop = false;
	while (!stop) {
		capture >> frame;
		imshow("camera", frame);
		string name = input_image(count++, "yellow");
		imwrite(name, frame);
		waitKey(300);
		if (count > 100) stop = true;
	}
}

void ANN_Color_Detect(void) {
	//GenData();
	
	//Mat trainingInput(1000, 300 * 300, CV_32FC1);
	//Mat testInput(200, 300 * 300, CV_32FC1);
	//Mat trainingOutput(1000, 1, CV_32FC1);
	//Mat testOutput(200, 1, CV_32FC1);
	//Mat testPredict(200, 1, CV_32FC1);
	
	Mat temp;
	Mat trainingInput(400, PIEXLS * 3, CV_32FC1);
	//Mat testInput(10, PIEXLS * 3, CV_32FC1);
	Mat trainingOutput(400, 4, CV_32FC1);
	//Mat testOutput(10, 1, CV_32FC1);
	//Mat testPredict(10, 1, CV_32FC1);

	for (int k = 0; k < 100; k++) {
		string image = input_image(k, "red");
		temp = imread(image, CV_LOAD_IMAGE_COLOR);
		resize(temp, temp, Size(128, 96));
		for (int i = 0; i < temp.rows; i++)
			for (int j = 0; j < temp.cols; j++) {
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 0) = temp.at<cv::Vec3b>(i, j)[0];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 1) = temp.at<cv::Vec3b>(i, j)[1];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 2) = temp.at<cv::Vec3b>(i, j)[2];
			}
		trainingOutput.at<float>(k, 0) = 0;
		trainingOutput.at<float>(k, 1) = 1;
		trainingOutput.at<float>(k, 2) = 0;
		trainingOutput.at<float>(k, 3) = 0;
	}

	for (int k = 100; k < 200; k++) {
		string image = input_image(k - 100, "green");
		temp = imread(image, CV_LOAD_IMAGE_COLOR);
		resize(temp, temp, Size(128, 96));
		for (int i = 0; i < temp.rows; i++)
			for (int j = 0; j < temp.cols; j++) {
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 0) = temp.at<cv::Vec3b>(i, j)[0];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 1) = temp.at<cv::Vec3b>(i, j)[1];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 2) = temp.at<cv::Vec3b>(i, j)[2];
			}
		trainingOutput.at<float>(k, 0) = 0;
		trainingOutput.at<float>(k, 1) = 0;
		trainingOutput.at<float>(k, 2) = 1;
		trainingOutput.at<float>(k, 3) = 0;
	}

	for (int k = 200; k < 300; k++) {
		string image = input_image(k - 200, "blue");
		temp = imread(image, CV_LOAD_IMAGE_COLOR);
		resize(temp, temp, Size(128, 96));
		for (int i = 0; i < temp.rows; i++)
			for (int j = 0; j < temp.cols; j++) {
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 0) = temp.at<cv::Vec3b>(i, j)[0];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 1) = temp.at<cv::Vec3b>(i, j)[1];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 2) = temp.at<cv::Vec3b>(i, j)[2];
			}
		trainingOutput.at<float>(k, 0) = 0;
		trainingOutput.at<float>(k, 1) = 0;
		trainingOutput.at<float>(k, 2) = 0;
		trainingOutput.at<float>(k, 3) = 1;
	}
	for (int k = 300; k < 400; k++) {
		string image = input_image(k - 300, "yellow");
		temp = imread(image, CV_LOAD_IMAGE_COLOR);
		resize(temp, temp, Size(128, 96));
		for (int i = 0; i < temp.rows; i++)
			for (int j = 0; j < temp.cols; j++) {
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 0) = temp.at<cv::Vec3b>(i, j)[0];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 1) = temp.at<cv::Vec3b>(i, j)[1];
				trainingInput.at<float>(k, i * temp.cols * 3 + j * 3 + 2) = temp.at<cv::Vec3b>(i, j)[2];
			}
		trainingOutput.at<float>(k, 0) = 1;
		trainingOutput.at<float>(k, 1) = 0;
		trainingOutput.at<float>(k, 2) = 0;
		trainingOutput.at<float>(k, 3) = 0;
	}

	Mat layers = Mat(5, 1, CV_32SC1);
	layers.row(0) = Scalar(PIEXLS * 3);
	layers.row(1) = Scalar(100);
	layers.row(2) = Scalar(15);
	layers.row(3) = Scalar(8);
	layers.row(4) = Scalar(4);

	CvANN_MLP mlp;
	CvANN_MLP_TrainParams params;
	CvTermCriteria criteria;
	criteria.max_iter = 1;
	criteria.epsilon = 0.0001f;
	criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
	params.train_method = CvANN_MLP_TrainParams::BACKPROP;
	params.bp_dw_scale = 0.05f;
	params.bp_moment_scale = 0.05f;
	params.term_crit = criteria;

	mlp.create(layers);
	mlp.train(trainingInput, trainingOutput, Mat(), Mat(), params);
	mlp.save("/Users/armour/Desktop/OpenCV/OpenCV/color_detect.xml");
	//mlp.load("/Users/armour/Desktop/OpenCV/OpenCV/color_detect.xml");
	//mlp.predict(testInput, testPredict);

	Mat testInput(1, PIEXLS * 3, CV_32FC1);
	Mat testOutput(1, 4, CV_32FC1);
	Mat testPredict(1, 4, CV_32FC1);
	VideoCapture capture(0);
	Mat frame;
	Mat edges;
	bool stop = false;
	while (!stop) {
		capture >> frame;
		imshow("camera", frame);
		resize(frame, temp, Size(128, 96));
		for (int i = 0; i < temp.rows; i++)
			for (int j = 0; j < temp.cols; j++) {
				testInput.at<float>(0, i * temp.cols * 3 + j * 3 + 0) = temp.at<cv::Vec3b>(i, j)[0];
				testInput.at<float>(0, i * temp.cols * 3 + j * 3 + 1) = temp.at<cv::Vec3b>(i, j)[1];
				testInput.at<float>(0, i * temp.cols * 3 + j * 3 + 2) = temp.at<cv::Vec3b>(i, j)[2];
			}
		mlp.predict(testInput, testPredict);
		cout << "Yellow:  " << testPredict.at<float>(0, 0) * 100 << "%     ";
		cout << "Red:  " << testPredict.at<float>(0, 1) * 100 << "%     ";
		cout << "Green:  " << testPredict.at<float>(0, 2) * 100 << "%     ";
		cout << "Blue:  " << testPredict.at<float>(0, 3) * 100 << "%" << endl;
		waitKey(500);
	}

	//for (int i = 0; i < testPredict.rows; i++) { 
	//	cout << "Predict: " << testPredict.at<float>(i, 0) << "   ";
	//	cout << "Answer: " << testOutput.at<float>(i, 0) << endl;
	//}
	//cout << "Final correct percent is : " << correct(testPredict, testOutput) << "%" << endl;
}