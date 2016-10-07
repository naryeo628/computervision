#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;

int main()
{
	cv::Mat image;
	image = cv::imread("puppy.bmp");
	if(image.empty())
	{
		cout<< "image unloaded" <<endl;
		return 0;
	}
	cout<<"Rows= "<<image.rows<<"  Cols= "<<image.cols<<endl;
	cv::namedWindow("Original");
	cv::imshow("Original",image);
	
	cv::Mat image1;
	image1 = cv::imread("puppy.bmp",0);			//그레이 스케일
	cv::imshow("Gray",image1);
	cout<<"Color depth= "<<image.depth()<<"  Type= "<<image.type()<<endl;
	cout<<"Gray depth= "<<image1.depth()<<" Type= "<<image.type()<<endl;


	cv::Mat result;
	cv::flip(image, result, 1);					//이미지 뒤집기 1 변수는 x축 반전
	cv::imshow("Output", result);
	cv::imwrite("output.bmp", result);
	vector<int> param_jpg, param_png;
	param_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	param_jpg.push_back(50);
	param_png.push_back(cv::IMWRITE_PNG_COMPRESSION);
	param_png.push_back(3);
	cv::imwrite("puppy.jpg", result, param_jpg);
	cv::imwrite("puppy.png", result, param_png);
	
	cv::Mat image2;
	image2 = cv::imread("bear.jpg");
	cv::imshow("Bear", image2);
	cout<<"Rows= "<<image.rows<<"  Cols= "<<image.cols<<endl;
	
	cv::waitKey(0);
	return 0;
}