#pragma once
#include <iostream>

#include <vector>
#include <iostream>



class Enemy
{
private:
	unsigned int m_enemy_id;
	float m_enemy_x;
	float m_enemy_y;
	float m_enemy_height;
	float m_enemy_width;
	float m_enemy_shiftSpeed;
	float m_enemy_attackSpeed;
	bool m_dead_flag;

public:
	Enemy();
	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setId(unsigned int id);
	unsigned int getId();

	void setAttackSpeed(float speed);
	float getAttackSpeed();

	void setShiftSpeed(float speed);
	float getShiftSpeed();

	void setWidth(float width);
	float getWidth();

	void setHeight(float height);
	float getHeight();

	void setFlag(bool);
	bool getFlag();


};

class Army
{

	
private:
	//The pre-defined amount of alien ships that are to be on the screen - if one gets destroyed, another should replace it
	int m_standard_ships_number;
	//The current amount of alien ships alive on the screen
	int m_ships_alive;
	//total alien ships to be printed on the screen during the whole game
	int m_total_ships;
	float factor;
	float offset;
	float angle;

	float shift_standard_x_positions[30];
	float shift_standard_y_positions[30];

public:
	/*At the moment when an army object is created, it initializes the following parameters:
	-standard_ships number
	-total_ships
	*/
	Army();



	void setStandardPositions(int position, float value_x, float value_y);
	float *getStandardXPositions();
	float *getStandardYPositions();
	float shift_army(int position, float timer, float speed);

	void set_operating_ships(int alive_ships);
	int get_operating_ships();


	//void assemble(int number_of_ships);
	void attack(int offensive_ships);
	void createEnemy(int damaged_ships);
	/*void stand_by(std::vector <Enemy*> fleet, float shift);
	void shift_army(std::vector <Enemy*> fleet, float shift);*/
};