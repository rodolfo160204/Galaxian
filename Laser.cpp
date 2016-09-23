#include "Laser.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

Laser::Laser()
{
	m_width = 5;
	m_height = 15;
}

void Laser::setSpeed(float speed)
{
	m_speed = speed;
}

float Laser::getSpeed()
{
	return m_speed;
}

void Laser::setX(float x)
{
	m_x = x;
}

void Laser::setY(float y)
{
	m_y = y;
}

float Laser::getWidth()
{
	return m_width;
}

float Laser::getHeight()
{
	return m_height;
}

float Laser::getX()
{
	return m_x;
}

float Laser::getY()
{
	return m_y;
}

void Laser::shootLaser(int &laser_y_increment, float x, float y, float timer, bool &shoot)
{
	if (laser_y_increment == 0)
	{
		setX(x);
		setY(y);
	}
	if (m_y < DEFAULT_SCREENHEIGHT)
	{	
		setY(getSpeed()*timer + getY());	
		laser_y_increment++;
	}
	else if (laser_y_increment >= DEFAULT_SCREENHEIGHT)
	{
		shoot = false;
		laser_y_increment = 0;
	}	
}

void Laser::setImageId(unsigned int id)
{
	m_id = id;
}

unsigned int Laser::getImageId()
{
	return m_id;
}
