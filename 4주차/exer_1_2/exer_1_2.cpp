#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat  image1(240, 320, cv_8U, 100);
	cv::imshow("image", image1);
	image1.create(200, 200, CV_8U);  image1=200;//초기값 설정(Scalar)
	cv::imshow("image", image1);
	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0,0,255));
	cv::imshow("image", image2);  cv::waitKey(0);
	cv::Mat image3=cv::imread("puppy.bmp");
	cv::Mat  image4(image3);
	image1=image3;
	image3.copyTo(image2);
	cv::Mat image5=image3.clone();
	cv::flip(image3, image3,1);

	return 0;
}