#include "colorDetctor.h"

/*
cv::Mat  ColorDetector::process(const  cv::Mat  &image)
{
cv::Mat  output;
cv::absdiff(image,  cv::Scalar(target),  output);
std::vector<cv::Mat>  images;
cv::split(output,  images);
output = images[0] + images[1] + images[2];
cv::threshold(output,  output,  minDist,  255,  cv::THRESH_BINARY_INV);
return  output;
} //imgproc249d.lib
*/
cv::Mat  ColorDetector::process(const  cv::Mat  &image)
{
	result.create(image.rows,  image.cols,  CV_8U);
	cv::cvtColor(image,  converted,  CV_BGR2Lab);
	cv::Mat_<cv::Vec3b>::const_iterator  it = converted.begin<cv::Vec3b>( ); 
	cv::Mat_<cv::Vec3b>::const_iterator  itend = converted.end<cv::Vec3b>( ); 
	cv::Mat_<uchar>::iterator  itout = result.begin<uchar>( );//이진영상
	for(  ;  it !=itend; ++it, ++itout)
	{
		if(getDistance(*it) <= minDist)
			*itout = 255;
		else
			*itout = 0;
	}
	return result;
}  
