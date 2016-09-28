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
	/*m_laser_y_increment is a variable that keeps track of the first time a laser is shot by the player or an alien,
	//that is, just after the laser has been shot so it can be placed at the player/aliens intial position and 
	//then be moved downwards/upwards */
	float m_laser_y_increment;
	bool shoot;
	
public:
	Laser();
	Laser(unsigned int image_id, float x, float y, float height, float width, float speed);

	void setSpeed(float speed);
	float getSpeed();

	void setX(float x);
	float getX();

	void setY(float x);	
	float getY();

	float getWidth();
	float getHeight();

	void setLaserYIncrement(float input);
	

	void shootLaser( float x, float y, float timer, bool &shoot, int laser_source);
	void setImageId(unsigned int id);
	unsigned int getImageId();

};