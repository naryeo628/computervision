#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;

int main()
{
	cv::Mat image1;
	cv::Mat image2;
	cv::Mat image3 = cv::imread("puppy.bmp");
	cv::Mat image4(image3);			//1

	image1=image3;					//2
	image3.copyTo(image2);			//3
	cv::Mat image5=image3.clone();	//4

	cv::flip(image3, image3, 1);	//image3�� image3�� ����������� ����.
	cv::imshow("image", image3);
	cv::waitKey(0);

	return 0;
}