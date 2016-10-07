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
void colorReduce_bitwise(cv::Mat  &image,  int  div)
{
	int nl = image.rows;   //행의 개수  
	int nc = image.cols*image.channels(); //각 행의 원소 총 개수
	for(int j=0; j<nl; j++)
	{
		const uchar*  data_in = image.ptr<uchar>(j); 
		uchar* data_out = image.ptr<uchar>(j);
		for(int i=0;  i<nc;  i++)
		{
			data_out[i] = data_in[i]/div*div + div/2; 
		}
	}
}
void colorReduce_iterator_Mat(cv::Mat  &image,  int  div)
{
	//cv::Mat_<cv::Vec3b>::iterator  it = image.begin<cv::Vec3b>( ); 
	cv::MatIterator_<cv::Vec3b> it =  image.begin<cv::Vec3b>( ); 
	//cv::Mat_<cv::Vec3b>::iterator  itend = image.end<cv::Vec3b>( );  
	cv::MatIterator_<cv::Vec3b> itend =  image.end<cv::Vec3b>( );     
	for(  ;  it !=itend; ++it){
		(*it)[0] = (*it)[0]/div*div + div/2;
		(*it)[1] = (*it)[1]/div*div + div/2;
		(*it)[2] = (*it)[2]/div*div + div/2;
	}
}
void colorReduce_iterator_Mat_(cv::Mat  &image,  int  div)
{
	cv::Mat_<cv::Vec3b>::iterator  it = image.begin<cv::Vec3b>( ); 
	//cv::MatIterator_<cv::Vec3b> it =  image.begin<cv::Vec3b>( ); 
	cv::Mat_<cv::Vec3b>::iterator  itend = image.end<cv::Vec3b>( );  
	//cv::MatIterator_<cv::Vec3b> itend =  image.end<cv::Vec3b>( );     
	for(  ;  it !=itend; ++it){
		(*it)[0] = (*it)[0]/div*div + div/2;
		(*it)[1] = (*it)[1]/div*div + div/2;
		(*it)[2] = (*it)[2]/div*div + div/2;
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
	
	image1 = image.clone();
	int64 start5 = cv::getTickCount();
	colorReduce_Pointer(image1,64);
	double duration5 = (cv::getTickCount() - start5)/cv::getTickFrequency()*1000;
	cout<<"Bitwise time = "<<duration5<<endl;
	imshow("Bitwise",image1);

	image1 = image.clone();
	int64 start3 = cv::getTickCount();
	colorReduce_iterator_Mat(image1,64);
	double duration3 = (cv::getTickCount() - start3)/cv::getTickFrequency()*1000;
	cout<<"Iterator_Mat time = "<<duration3<<endl;
	imshow("Iterator_Mat",image1);

	image1 = image.clone();
	int64 start4 = cv::getTickCount();
	colorReduce_iterator_Mat_(image1,64);
	double duration4 = (cv::getTickCount() - start4)/cv::getTickFrequency()*1000;
	cout<<"Iterator_Mat_ time = "<<duration4<<endl;
	imshow("Iterator_Mat_",image1);

	waitKey(0);
	return 0;
}