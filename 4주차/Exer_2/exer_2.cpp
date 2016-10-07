#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void salt(cv::Mat image, int n)
{
	int i,j;
	for(int k=0;  k<n;  k++)
	{
		i=rand()%image.cols;  j=rand()%image.rows;  //j=y, i=x
		if(image.type()== CV_8UC1){  image.at<uchar>(j,i) = 255;
		}
		else if(image.type()== CV_8UC3)  
		{
			//컬러 영상인 경우
			image.at<cv::Vec3b>(j,i)[0]=255;   
			image.at<cv::Vec3b>(j,i)[1]=255;
			image.at<cv::Vec3b>(j,i)[2]=255;
			// image.at<cv::Vec3b>(j,i)= cv::Vec3b(255, 255, 255);	//한꺼번에도 가능.
		}
	}
}
void colorReduce_Array(cv::Mat  &image,  int  div)
{
	int nl = image.rows;   //행의 개수  
	int nc = image.cols*image.channels(); //각 행의 원소 총 개수
	for(int j=0; j<nl; j++)
	{
		uchar*  data = image.ptr<uchar>(j); 
		for(int i=0;  i<nc;  i++)
		{
			data[i] = data[i]/div*div + div/2;  // *data=*data/div*div+div/2;  data++;
		}                                                  // *data++=*data/div*div+div/2;
	}
}
void colorReduce_Pointer(cv::Mat  &image,  int  div)
{
	int nl = image.rows;   //행의 개수  
	int nc = image.cols*image.channels(); //각 행의 원소 총 개수
	for(int j=0; j<nl; j++)
	{
		uchar*  data = image.ptr<uchar>(j); 
		for(int i=0;  i<nc;  i++)
			*data++=*data/div*div+div/2;
	}
}

int main()
{
	Mat image = imread("boldt.jpg");
	imshow("Original",image);
	/*
	salt(image, 3000);
	cv::namedWindow("image");
	imshow("image",image);
	cv::imwrite("salted.bmp",image);
	*/
	Mat image1 = image.clone();
	int64 start = cv::getTickCount();
	colorReduce_Array(image1,64);
	double duration = (cv::getTickCount() - start)/cv::getTickFrequency()*1000;
	cout<<"Array time = "<<duration<<endl;
	imshow("Array",image1);

	image1 = image.clone();
	int64 start2 = cv::getTickCount();
	colorReduce_Pointer(image1,64);
	double duration2 = (cv::getTickCount() - start2)/cv::getTickFrequency()*1000;
	cout<<"Pointer time = "<<duration2<<endl;
	imshow("Pointer",image1);


	waitKey(0);
	return 0;
}