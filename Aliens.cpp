#include "Aliens.h"
#include <vector>
#include "Application.h"
#include <math.h>
#define PI 3.14159265

Enemy::Enemy()
{
	 m_enemy_height = 40;
	 m_enemy_width = 60;
	 m_dead_flag = false;
}

void Enemy::setX(float x)
{
	m_enemy_x = x;
}

float Enemy::getX()
{
	return m_enemy_x;
}

void Enemy::setY(float y)
{
	m_enemy_y = y;
}

float Enemy::getY()
{
	return m_enemy_y;
}

void Enemy::setId(unsigned int id)
{
	m_enemy_id = id;
}

unsigned int Enemy::getId()
{
	return m_enemy_id;
}

void Enemy::setShiftSpeed(float speed)
{
	m_enemy_shiftSpeed = speed;
}

float Enemy::getShiftSpeed()
{
	return m_enemy_shiftSpeed;
}

void Enemy::setWidth(float width)
{
	m_enemy_width = width;
}

float Enemy::getWidth()
{
	return m_enemy_width;
}

void Enemy::setHeight(float height)
{
	m_enemy_height = height;
}

float Enemy::getHeight()
{
	return m_enemy_height;
}

void Enemy::setFlag(bool dead)
{
	m_dead_flag = dead;
}

bool Enemy::getFlag()
{
	return m_dead_flag;
}

void Enemy::setAttackSpeed(float speed)
{
	m_enemy_attackSpeed = speed;
}

float Enemy::getAttackSpeed()
{
	return m_enemy_attackSpeed;
}


Army::Army()
{
	angle = 0;
} 

void Army::setStandardPositions(int position, float value_x, float value_y)
{
	shift_standard_x_positions[position] = value_x;
	shift_standard_y_positions[position] = value_y;
}

float * Army::getStandardXPositions()
{
	return shift_standard_x_positions;
}

float * Army::getStandardYPositions()
{
	return shift_standard_y_positions;
}

float Army::shift_army(int position, float timer, float speed)
{
	angle+=0.01;

	if (angle == 360)
	{
		angle = 0;
	}
	
	factor = sinf(angle*PI / 180);
	offset = 10*speed*timer*factor;

	//std::cout << "offset: " << offset << std::endl;
	float result = shift_standard_x_positions[position] + offset;

	return result;
}

void Army::set_operating_ships(int alive_ships)
{
	m_ships_alive = alive_ships;
}

int Army::get_operating_ships()
{
	return m_ships_alive;
}

//void Army::assemble(int number_of_ships)
//{
//	m_total_ships = number_of_ships;
//}

void Army::attack(int offensive_ships)
{
}

void Army::createEnemy(int damaged_ships)
{
}

