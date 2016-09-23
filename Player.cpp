#include "Player.h"

void Player::setX(float x)
{
	m_x = x;
}

float Player::getX()
{
	return m_x;
}

void Player::setY(float y)
{
	m_y = y;
}

float Player::getY()
{
	return m_y;
}

void Player::setId(unsigned int id)
{
	m_id = id;
}

unsigned int Player::getId()
{
	return m_id;
}

void Player::setDamage(float damage)
{
	m_damage = damage;
}

float Player::getDamage()
{
	return m_damage;
}

void Player::setScore(float score)
{
	m_score = score;
}

float Player::getScore()
{
	return m_score;
}

void Player::setSpeed(float speed)
{
	m_speed = speed;
}

float Player::getSpeed()
{
	return m_speed;
}
