#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat boldt = imread("boldt.jpg");
	Mat image = imread("boldt.jpg");
	Mat rain = imread("rain.jpg");
	Mat gray = imread("rain.jpg",0);
	Mat result;
	imshow("Boldt", boldt);
	//imshow("Rain", rain);

	addWeighted(boldt, 0.7, rain, 0.9, 0, result);
	//imshow("Result", result);

	//vector<Mat> planes;
	//split(boldt, planes);
	//imshow("Blue", planes[0]);
	//imshow("Green", planes[1]);
	//imshow("Red", planes[2]);
	//planes[2] = planes[2] + gray;
	//merge(planes,result);
	//imshow("Result", result);

	cv::Mat  srcX(image.rows, image.cols, CV_32F);
	cv::Mat  srcY(image.rows, image.cols, CV_32F);
	//cv::Mat result;
	for(int i=0; i<image.rows; i++)
		for(int j=0;j<image.cols;j++)
		{
			srcX.at<float>(i,j) = j; //열은 그대로 유지
			srcY.at<float>(i,j) = i+5*sin(j/10.0); //i 행의 화소 이동
		}
		cv::remap(image, result, srcX, srcY,  cv::INTER_LINEAR);
	imshow("Result", result);


	waitKey(0);

	return 0;
}