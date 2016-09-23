#pragma once
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include "Application.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720
//adapted from http://www.cplusplus.com/forum/general/33669/


/*Background
*Stars will fall from the top.
*generated randomly.
*Each will have its own colour.
*Each will blink.
*Timed falling.
*/


class Stars 
{
public:
	/*Constructor*/
	Stars();
	Stars(float texture_id, float x, float y);
	/*coordinates of a star*/
	float star_x;
	float star_y;
	float texture_id;


	/*
	Arguments:
	*two time_t values corresponding to the last time a star was placed and the time at which the function is being invoked. 
	*and an array of unsigned int (corresponding to an image loaded on the onCreate() method in GameLoop.cpp
	
	Function: 
	*places a random image of a star in a random location on the screen
	*After a specific time interval (2 sec)
	
	*/
	
	
	void reset_positions(float &x, float &y);

private:
	int screen_height = DEFAULT_SCREENHEIGHT;
	int screen_width = DEFAULT_SCREENWIDTH;
};

/*Functions generateRandomNumber and check_timing belong to the Stars.h, but not the Stars class.
//This makes it easier for functions outside the class to access it, because there will no longer be necessary
//To create an object to access them.*/
