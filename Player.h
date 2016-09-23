#pragma once
#include <iostream>

class Player
{

private:
	float m_x;
	float m_y;
	unsigned int m_id;
	float m_damage;
	float m_score;
	float m_speed;

public:
	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setId(unsigned int id);
	unsigned int getId();

	void setDamage(float damage);
	float getDamage();

	void setScore(float score);
	float getScore();

	void setSpeed(float speed);
	float getSpeed();
};