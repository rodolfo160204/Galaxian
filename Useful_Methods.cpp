#include <stdlib.h>
#include <iostream>
#include <ctime>
#include "Useful_Methods.h"
#include <math.h>


void generateRandomNumber(int &x, int limit)
{
	//start = last_check;

	//generate random number
	//seed
	//srand(time(NULL));
	int random;
	//star_x will be assigned a value from 0 to 1279
	random = rand() % limit;

	x = random;


}

bool check_timing(time_t end, time_t & start, int interval)
{
	/*resets the value of 'start' variable, so the next time the function is called it can calculate the
	difference in seconds between the last time a star was placed on the screen and then place a new one
	if the difference is greater than the predefined interval.*/
	int seconds_elapsed;

	bool timing_complete = false;
	seconds_elapsed = difftime(end, start);

	if (seconds_elapsed >= interval)
	{
		timing_complete = true;
		start = end;
	}

	return timing_complete;
}

bool detect_collision(const float x1, const float y1, const int width1, const int height1, 
	const float x2, const float y2, const int width2, const int height2)
{
	float radius_distance;
	float x_difference;
	float y_difference;
	bool collide = false;
	//define x_difference
	x_difference = x1 - x2;	

	/*std::cout << " x1 : " << x1 << " y1: " << y1 << "\n";
	std::cout << " x2 : " << x2 << " y2: " << y2 << "\n";*/
	//define y_difference
	y_difference = y1 - y2;
	
	/*It does not matter if the x_difference or y_difference is negative, 
	//because the pow function will mathematically generate a positive number
	//regardless of the input signal.*/
	radius_distance = sqrt(pow(x_difference, 2) + pow(y_difference, 2));
	//std::cout << "radius_distance: " << radius_distance <<std::endl;

	if (((radius_distance < (width1 + width2) / 2)) && ((radius_distance < (height1 + height2) / 2)))
	{
		collide = true;
		//std::cout << "collision!!!\n";
	}

	return collide;

}
