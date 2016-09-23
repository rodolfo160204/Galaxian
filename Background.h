#pragma once

class Background
{
private:
	float m_x;
	float m_y;
	unsigned int m_id;
	float m_speed;

public:
	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setId(unsigned int id);
	unsigned int getId();

	void setSpeed(float speed);
	float getSpeed();
};