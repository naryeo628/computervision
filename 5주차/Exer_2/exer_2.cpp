//#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include  "colorDetctor.h"

using namespace cv;
using namespace std;

int main()
{
	ColorDetector   cdetect;
	cv::Mat  image = cv::imread("boldt.jpg ");
	if(!image.data)
		return 0;
	imshow("Original", image);
	cdetect.setTargetColor(230, 190, 130); //B,G,R

	cv::Mat tmp(1,1, CV_8UC3);
	tmp.at<cv::Vec3b>(0,0) = cdetect.getTargetColor();
	cv::cvtColor(tmp, tmp,  CV_BGR2Lab);
	cdetect.setTargetColor(tmp.at<cv::Vec3b>(0,0));
	cv::namedWindow("Result");

	cout<<"Target"<<tmp<<endl;
	cv::imshow("Result", cdetect.process(image));


	cv::waitKey(0);

	return  0;
}     