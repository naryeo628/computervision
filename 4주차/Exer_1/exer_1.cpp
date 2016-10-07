#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("puppy.bmp");
	imshow("Original", image);
	circle(image, cv::Point(155,110), 65, 255, 3);
	putText(image, "This is a dog.", cv::Point(40,200), cv::FONT_HERSHEY_PLAIN, 2.0, Scalar(255,255,255), 2);
	Mat logo = imread("logo.bmp");
	imshow("logo",logo);
	Mat imageROI(image,cv::Rect(image.cols - logo.cols, image.rows -logo.rows, logo.cols, logo.rows));
	//logo.copyTo(imageROI);
	Mat mask = imread("logo.bmp",0);
	logo.copyTo(imageROI,mask);
	imshow("circle",image);
	waitKey(0);


	return 0;
}