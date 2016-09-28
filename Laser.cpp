#include "Laser.h"
#include <iostream>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

Laser::Laser()
{
	m_width = 5;
	m_height = 15;
}

Laser::Laser(unsigned int image_id, float x, float y, float width, float height, float speed)
{
	//std::cout << "SUPER CONSTRUCTOR LASER DINOSAURR\n";
	//Laser super constructor called!
	m_id = image_id;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	//std::cout << "id: " << m_id << " x: " << m_x << " y: " << m_y << " width: " << m_width << " height: " << m_height << std::endl;

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

void Laser::setLaserYIncrement(float input)
{
	m_laser_y_increment = input;
}

float Laser::getX()
{
	return m_x;
}

float Laser::getY()
{
	return m_y;
}

void Laser::shootLaser( float x, float y, float timer, bool &shoot, int laser_source)
{
	//if player shot, follow the isntructions below
	
		if (m_laser_y_increment == 0)
		{
			setX(x);
			setY(y);
		}

		if (m_y <= DEFAULT_SCREENHEIGHT)
		{
			setY(getSpeed()*timer + getY());
			if (laser_source == 1)
			{
				m_laser_y_increment++;
			}
			if (laser_source == 2)
			{
				m_laser_y_increment--;
			}
		}

		else if (m_y > DEFAULT_SCREENHEIGHT)
		{
			shoot = false;
			m_laser_y_increment = 0;
		}

	
	//if alien shot, follow the instructions below
	/*if (laser_source == 2)
	{
		if()
	}*/
}

void Laser::setImageId(unsigned int id)
{
	m_id = id;
}

unsigned int Laser::getImageId()
{
	return m_id;
}
