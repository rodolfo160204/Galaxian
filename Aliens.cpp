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
	 attacking = false;
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

void Enemy::setAttackingStatus(bool input)
{
	attacking = input;
}

bool Enemy::getAttackingStatus()
{
	return attacking;
}

void Enemy::setCrossedScreen(bool input)
{
	crossedScreen = input;
}

bool Enemy::getCrossedScreen()
{
	return crossedScreen;
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

void Army::attack(const std::vector <Enemy*> &fleet, std::vector <Laser*> &laserGuns, unsigned int alien_laser_id, float timer)
{
	
	//generate random number from 0 to 29 so a random alien will 
	//be selected and then it will leave formation to attack player
	//std::cout << "Attack method called." << std::endl;
	
	int chosen_one = -1;
	//while the random number is a dead alien, generate another random number.
	do 
	{
		generateRandomNumber(chosen_one, 30);		
		//std::cout << "trying... chose: " << chosen_one << std::endl;
	} while (fleet[chosen_one]->getFlag() == true);

	//get coordinates of chosen alien so that laser can be shot from its position
	
	//fleet[chosen_one]->setX(fleet[chosen_one]->getX()-fleet[chosen_one]->getAttackSpeed()*timer);
	fleet[chosen_one]->setAttackingStatus(true);

	float laser_start_x = fleet[chosen_one]->getX();
	float laser_start_y = fleet[chosen_one]->getY();

	//CREATES A NEW OBJECT OF LASER AND PUSHES IT TO THE VECTOR. Initializes the variables through the constructor.
	laserGuns.push_back(new Laser(alien_laser_id, laser_start_x, laser_start_y, 5, 15, 45.0f));	
}

void Army::createEnemy(int damaged_ships)
{
}

/*Since the vector is used for read-only purposes, the 'const' keyword is used so that the data inside the vector is
//safe from unwanted changes. Also, for performance purposes, a reference to the vector is passed so that the method
//does not make a copy of the entire vector, which would create too much overhead. Instead, I am using an alias to the 
same vector*/ 
void Army::check_aliens(const std::vector<Enemy*>& fleet)
{
	int alien_life = 0;
	for (int i = 0; i < fleet.size(); i++)
	{
		if (fleet[i]->getFlag() == false)
			alien_life++;
	}
	
	set_operating_ships(alien_life);
	
}

