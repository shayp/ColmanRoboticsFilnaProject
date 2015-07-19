#include "Helper.h"
#include <iostream>

using namespace std;

int Helper::DegreesToIndex(int degrees)
{
	int indexDifference = degrees * Helper::DEGREES_INDEX_RATIO;
	return Helper::HALF_SCAN_SPAN + indexDifference;
}

int Helper::IndexToDegrees(int index)
{
	int relativeIndex = index - Helper::HALF_SCAN_SPAN;
	return relativeIndex / Helper::DEGREES_INDEX_RATIO;
}

double Helper::IndexToRadians(int index)
{
	int degrees = IndexToDegrees(index);
	return degrees * PI / 180;
}

int Helper::RadiansToIndex(double radians)
{
	int degrees = radians * 180 / PI;
	return DegreesToIndex(degrees);
}

double Helper::MetersToCentimeters(double meters)
{
	return meters * 100;
}

double Helper::CentimetersToMeters(double centimeters)
{
	return centimeters / 100;
}

 double Helper::CalcRadToWaypointWithoutYaw(double fromX, double fromY, double toX, double toY)
 {
	 double xDelta = toX - fromX;
	 double yDelta = toY - fromY;
	 double rad;

	 //The two point on the X axis
	 if (yDelta ==0)
	 {
		 if(xDelta<0)
		 {
			 return PI;
		 }
		 return 0;
	 }

	 rad = atan(yDelta/xDelta);

	 if(yDelta>0)
	 {
		 //Second q-> the toY is bigger than fromY and the toX is smaller than fromX
		 if(xDelta<0)
		 {
			 rad+=PI;
		 }
		 //First q ->no change, the toX and toY are bigger than fromX and fromY
	 }
	 else
	 {
		 //Third q-> the toY  and toX is smaller than fromY and fromX
		 if(xDelta<0)
		 {
			 rad+=PI;
		 }
		 //Forth q-> the toY  is smaller than fromY and toX is bigger than fromX
		 else
		 {
			 rad+=2*PI;

		 }
	 }
	 return rad;
 }


 //Calc the angle we need to pass for been in straight line to the to point
  double Helper::CalcRadDeltaToWaypoint(double fromX, double fromY, double toX, double toY,  double fromYaw)
  {
 	 double toYaw = Helper::CalcRadToWaypointWithoutYaw(fromX, fromY, toX, toY);
 	 //cout << "#### In the calc #####" << endl;
 	 //cout << "from yaw: " << fromYaw << " to yaw: " << toYaw << endl;
 	 double deltaRad;
 	 if(toYaw>PI)
 	 {
 		 //
 		 if(fromYaw > 0)
 		 {
 			 deltaRad = toYaw - fromYaw;
 		 }
 		 else
 		 {
 			 deltaRad = toYaw - fromYaw -2*PI;
 		 }

 	 }
 	 else
 	 {
 		 if(fromYaw > 0)
 		 {
 			 deltaRad = toYaw - fromYaw;
 		 }
 		 else
 		 {
 			deltaRad =  toYaw-fromYaw-2*PI;
 			//cout << "MY DELTA:: " <<deltaRad << endl;
 		 }
 	 }
 	 if(deltaRad<-PI)
 	 {
 		 deltaRad = deltaRad + 2*PI;
 		 //cout << "AFTER FIX = " << deltaRad << endl;
 	 }
 	 else if(deltaRad>PI)
 	 {
 		 deltaRad = deltaRad - 2*PI;
 	 }
 	 return deltaRad;
  }

 double Helper::ConvertTo2PI(double rad)
  {

 	 double deg = rad*180/PI;

 	 if(rad<0)
 	 {
 		 deg = deg * (-1);
 		 if(deg<90)
 		 {
 			 deg+=270;
 		 }
 		 else
 		 {
 			 deg+=180;
 		 }

 	 }
 	 return deg;
 }

	double Helper::SpinSpeedByDeg(double rad)
	{
		//cout << "the rad: " << rad << endl;
		double deg = Helper::ConvertTo2PI(rad);
		//cout << "the deg: " << deg << endl;
		//cout << "deg: " << deg << endl;
		//Look for func that return 1 for 180 and 0 for 0 or 360
		double newSpeed = (-0.00003*pow(deg,2.0))+0.01111 *deg;
		//cout << "speed: " << newSpeed << endl;
		//We don't want the speed too slow
		newSpeed+=0.1;
		//cout << "after add 0.1: " << newSpeed << endl;
		//Chose the direction to spin
		if(deg>180)
		{
			newSpeed*=(-1);
		}
		//cout << "after direction: " << newSpeed << endl;
		//cout << "return speed: " << newSpeed << endl;
		return newSpeed;
		//return 0;
	}


	double Helper::KeepYawInRange(double rad)
	{
		while(rad < -PI || rad > PI)
		{
			if(rad < -PI)
			{
				rad+=2*PI;
			}
			else
			{
				rad-=2*PI;
			}
		}
		return rad;
	}
