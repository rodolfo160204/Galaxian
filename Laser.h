#pragma once
class Laser
{
	//variables concerning the sprites

private:
	float m_height;
	float m_width;
	float m_x;
	float m_y;
	float m_speed;
	float m_id;
	float m_laser_y_increment;
	
public:
	Laser();

	void setSpeed(float speed);
	float getSpeed();

	void setX(float x);
	float getX();

	void setY(float x);	
	float getY();

	float getWidth();
	float getHeight();
	
	void shootLaser(int &laser_y_increment, float x, float y, float timer, bool &shoot);
	void setImageId(unsigned int id);
	unsigned int getImageId();

};