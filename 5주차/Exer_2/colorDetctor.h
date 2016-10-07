#pragma once
//#ifndef  COLORDETECT
//#define  COLORDETECT
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
class ColorDetector
{
private:
	int minDist;
	cv::Mat converted;	//

	cv::Vec3b  target;
	cv::Mat  result;
	int getDistance(const  cv::Vec3b&  color) const
	{   
		return (abs(color[0] - target[0]) + 	
			abs(color[1] - target[1])  + 
			abs(color[2] - target[2]));
	}  
public:
	ColorDetector() : minDist(40), target(0,0,0) { }//초기화
	void setColorDistanceThreshold( int  distance)
	{
		if(distance < 0) distance = 0;   minDist = distance;
	}     	//입력값 유효성 체크
	int getColorDistanceThreshold( ) const
	{
		return minDist;  
	}
	void setTargetColor(uchar blue, uchar  green,  uchar  red)
	{
		target = cv::Vec3b(blue, green, red);    
	}
	void setTargetColor(cv::Vec3b  color)
	{
		target =  color;   
	}
	cv::Vec3b  getTargetColor  ( )   const 
	{
		return target;   
	}
	cv::Mat process(const cv::Mat &image);
};
//#endif
