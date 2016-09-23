#include "Application.h"
#include "GameLoop.h"
#include "Stars.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "Useful_Methods.h"
#include "Aliens.h"

APPLICATION_ENTRY(GameLoop);
#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace std;


GameLoop::GameLoop()
{
	for (int i = 0; i < 30; i++)
	{
		fleet.push_back(new Enemy());
		//fleet[i] = nullptr;
	}

	
}

GameLoop::~GameLoop()
{
	
}

bool GameLoop::onCreate(int a_argc, char* a_argv[])
{
	//setBackgroundColor(NHTV::SColour(0x00, 0x00, 0x00, 0xFF));
	GetScreenSize(m_iScreenWidth, m_iScreenHeight);
	AddFont("./fonts/invaders.fnt");

	//Background setup
	background = CreateSprite("./images_assets/Stars/background_scroll.png", 1282, 1454, true);
	sky.setId(background);
	sky.setX(m_iScreenWidth*0.5);
	sky.setY(m_iScreenHeight*0.5);
	sky.setSpeed(5.0f);
	MoveSprite(sky.getId(), sky.getX(), sky.getY());



	//Player setup
	m_iPlayerSprite = CreateSprite("./images_assets/cannon.png", 64, 32, true);
	hero.setId(m_iPlayerSprite);
	hero.setX(m_iScreenWidth * 0.5f);
	hero.setY(100.0f);
	hero.setScore(0.0f);
	hero.setSpeed(30.0f);
	MoveSprite(hero.getId(), hero.getX(), hero.getY());

	//Laser setup
	player_laser_sprite = CreateSprite("./images_assets/Lasers/image15.png", zap.getWidth(), zap.getHeight(), true);	
	zap.setX(m_iScreenWidth * 0.5f);
	zap.setY(100);
	zap.setSpeed(45.0f);
	zap.setImageId(player_laser_sprite);
	
	//Aliens setup
	sad_alien_images = CreateSprite("./images_assets/Ships/invader_1_1.jpg", 60, 40, true);
	happy_alien_images = CreateSprite("./images_assets/Ships/invader_1_2.jpg", 60, 40, true);
	setImageId(1, true);
	//setImageId(2, true);

	for (int i = 0; i < fleet.size(); i++)
	{

		

		fleet[i]->setShiftSpeed(120.0f);

	}


	//stand_by(fleet, alien_sliding_counter, 0);
	//sets the value for the time1 variable, which indicates when the game has started.
	time1 = time(NULL);
	
	//Sets the sprites to their initial position
	
	//MoveSprite(alien, m_iScreenWidth*0.5f, m_iScreenHeight - 100);


	

	
	return true;
}
/**********CREATE************/


void GameLoop::onUpdate(float a_deltaTime)
{

	timer += a_deltaTime;

	if (timer >= 1 / 60.f)
	{
		//Every time the game updates, gets the time value assigns it to time2.
		time2 = time(NULL);

		//animate_aliens
		if (check_timing(time2, time1, 1))
		{
			sprite_choice = 1;

			if (time2 % 2 == 0)
			{
				sprite_choice = 2;
			}

		}

		//Background
		
		//Scrolling
		sky.setY(sky.getY() - sky.getSpeed()*timer);

		if (sky.getY() < 0)
		{
			sky.setY(DEFAULT_SCREENHEIGHT);
		}

		MoveSprite(sky.getId(), sky.getX(), sky.getY());


		//Player
		


		if (IsKeyDown(NHTV::KEY_RIGHT))
		{
			hero.setX(hero.getX() + hero.getSpeed()*timer);
			MoveSprite(hero.getId(), hero.getX(), hero.getY());
		}
		if (IsKeyDown(NHTV::KEY_LEFT))
		{
			hero.setX(hero.getX() - hero.getSpeed()*timer);
			MoveSprite(hero.getId(), hero.getX(), hero.getY());
		}
	
		if (IsKeyDown(NHTV::KEY_SPACE))
		{
			shoot = true;
		}

		if (shoot == true)
		{			
			zap.shootLaser(laser_speed_increment_y, hero.getX(), hero.getY()+10, timer, shoot);
			MoveSprite(zap.getImageId(), zap.getX(), zap.getY());

			//detect collision
			for (int i = 0; i < fleet.size(); i++)
			{
				if (fleet[i]->getFlag() == false)
				{
					bool kaboom = detect_collision(zap.getX(), zap.getY(), zap.getWidth(), zap.getHeight(),
						fleet[i]->getX(), fleet[i]->getY(), fleet[i]->getWidth(), fleet[i]->getHeight());

					if (kaboom == true)
					{
						fleet[i]->setFlag(true);
						shoot = false;
						laser_speed_increment_y = 0;
					}
				}
			}
		}


		// quit our application when escape is pressed
		if (IsKeyDown(NHTV::KEY_ESCAPE))
			destroy();

		//moves the alien sprites side ways while in stand by mode.
		for (int i = 0; i < fleet.size(); i++)
		{
			fleet[i]->setX(squad.shift_army(i, timer, fleet[i]->getShiftSpeed()));
		}
		//cout << "0th x after: "<<fleet[0]->getX() << endl;

		
		
		timer -= a_deltaTime;
	}
}

void GameLoop::onDraw()
{
	clearScreen();

	

	float fDeltaT = GetDeltaTime();

	DrawSprite(sky.getId());
	DrawSprite(hero.getId());

	//assuming the bottom left is (0,0), if y is incremented then the y coordinate should augment, in other words, the laser should move up
	
	if (shoot)
	{
		//DrawLine(laser_x, laser_y + laser_speed_increment_y, laser_x, laser_y + 20 + laser_speed_increment_y);
		DrawSprite(zap.getImageId());
		//cout << " shoot! laser (x,y) = (" << zap.getX() << " , " << zap.getY() << ")"<< endl;
		//Test collision for every alien.
	}

	//setImageId(sprite_choice, false);
	
	drawAliens();
	
	
	SetFont("./fonts/invaders.fnt");
	DrawString("SCORE < 1 >", m_iScreenWidth * 0.025f, m_iScreenHeight - 2, 0.5f);
	DrawString("HI-SCORE", m_iScreenWidth * 0.4f, m_iScreenHeight - 2, 0.5f);

	DrawString("SCORE < 2 >", m_iScreenWidth * 0.725f, m_iScreenHeight - 2, 0.5f);
	DrawString("CREDIT", m_iScreenWidth * 0.65f, 38);

	DrawLine(0, 40, m_iScreenWidth, 40, NHTV::SColour(0x00, 0xFC, 0x00, 0xFF));
	std::string timeFrame = "DeltaTime: ";
	timeFrame.append(std::to_string(fDeltaT));
	SetFont(nullptr);

//	DrawString(timeFrame.c_str(), 10, 720, 0.75f);


}

void GameLoop::onDestroy()
{
	
}

void GameLoop::setImageId(int choice, bool first_time)
{
		//Sets the identifiers of the images to the class 'Enemy' atribute image_id
		for (int i = 0; i < 30; i++)
		{

			if (first_time)
			{
				//cout << "alien: " << alien << " fleet duplicated:  " << fleet[i][j].image_id << endl;
				//Keeps the aliens in formation (10x3)
				int j = i;

				if (i >= 10 && i < 20)
				{
					j -= 10;
				}
				if (i >= 20)
				{
					j -= 20;
				}

				fleet[i]->setX(235 + (fleet[i]->getWidth() *1.5) * j);
				fleet[i]->setY(m_iScreenHeight*0.9 - (i / 10) * (fleet[i]->getHeight() + 10));

				squad.setStandardPositions(i, fleet[i]->getX(), fleet[i]->getY());

			}
			//if first time
				 //For every ten (0-9), (10-19), (20-29)
				 if (choice == 1)
				 {
					 fleet[i]->setId(sad_alien_images);
					 MoveSprite(fleet[i]->getId(), fleet[i]->getX(), fleet[i]->getY());
				 }
				 if (choice == 2)
				 {
					 fleet[i]->setId(happy_alien_images);
					 MoveSprite(fleet[i]->getId(), fleet[i]->getX(), fleet[i]->getY());
				 }
			
			
			//cout << "x standard positions: " << *(squad.getStandardXPositions() + i) << endl;
		}//for

		
		
	
}
/*This function (drawAliens()) takes care of drawing the aliens in the following fashion:
Each column has an alternated set of sprites for the aliens.
To create a more elaborate feeling, each second the columns change their sprite.
The timing is possible thanks to the 'sprite_choice' variable.*/
void GameLoop::drawAliens()
{
	for (int i = 0; i < fleet.size(); i++)
	{
		if (fleet[i]->getFlag() == false)
		{
			if (sprite_choice == 1)
			{
				if (i % 2 == 0)
				{
					fleet[i]->setId(sad_alien_images);
					MoveSprite(fleet[i]->getId(), fleet[i]->getX(), fleet[i]->getY());
				}
				else
				{
					fleet[i]->setId(happy_alien_images);
					MoveSprite(fleet[i]->getId(), fleet[i]->getX(), fleet[i]->getY());
				}
			}//if sprite choice == 1
			if (sprite_choice == 2)
			{
				if (i % 2 != 0)
				{
					fleet[i]->setId(sad_alien_images);
					MoveSprite(fleet[i]->getId(), fleet[i]->getX(), fleet[i]->getY());
				}
				else
				{
					fleet[i]->setId(happy_alien_images);
					MoveSprite(fleet[i]->getId(), fleet[i]->getX(), fleet[i]->getY());
				}
			}//if sprite choice == 2

			DrawSprite(fleet[i]->getId());
		
		}//if flag
	}//for
}
//drawAlien




