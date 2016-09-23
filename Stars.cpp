#include "Stars.h"

Stars::Stars()
{

}

Stars::Stars(float image_id, float x, float y)
{
	texture_id = image_id;
	star_x = x;
	star_y = y;
}




//*****REDO******





void Stars::reset_positions(float & x, float & y)
{
	x = rand() % screen_width;
	y = screen_height;

}
