#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("boldt.jpg");
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);
	Mat result;
	for(int i = 0; i < image.rows; i++)
		for(int j = 0; j < image.cols;j++)
		{
			srcX.at<float>(i,j) = image.cols-j;
			srcY.at<float>(i,j) = image.rows-i;
		}

	remap(image, result, srcX, srcY,  cv::INTER_LINEAR);

	imshow("flip",result);

	
	waitKey(0);

	return 0;
}