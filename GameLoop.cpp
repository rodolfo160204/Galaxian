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

	//Laser(player) setup
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

	//Laser (alien) setup
	alien_laser = CreateSprite("./Images_assets/Lasers/image7.png", zap.getWidth(), zap.getHeight(), true);



	for (int i = 0; i < fleet.size(); i++)
	{

		fleet[i]->setShiftSpeed(120.0f);
		fleet[i]->setAttackSpeed(20.0f);

	}


	//stand_by(fleet, alien_sliding_counter, 0);
	//sets the value for the t_begin variable, which indicates when the game has started.
	t_begin = time(NULL);
	t_attack_begin = time(NULL);
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
		//Check how many aliens are alive
		squad.check_aliens(fleet);

		//Every time the game updates, gets the time value assigns it to t_animate.
		t_animate = time(NULL);
		t_attack = time(NULL);
		//animate_aliens
		if (check_timing(t_animate, t_begin, 1))
		{
			sprite_choice = 1;

			if (t_animate % 2 == 0)
			{
				sprite_choice = 2;
			}

		}

		if (check_timing(t_attack, t_attack_begin, 5))
		{
			//cout << "attack!\n";
			squad.attack(fleet, laserGuns, alien_laser, timer);
		}

		//makes a chosen alien leave formation and, if it has not been hit, makes it go to the top of the screen again
		//and reassigns it to its standard position within the squad.
		for (int i = 0; i < fleet.size(); i++)
		{
			if(fleet[i]->getFlag() == false)
			{ 
				if (fleet[i]->getAttackingStatus() == true)
				{
					int chosen_one = i;
					//move chosen alien downwards.
					fleet[chosen_one]->setY(fleet[chosen_one]->getY() - fleet[chosen_one]->getAttackSpeed()*timer);

					//if alien has gone out of the screen boundaries, make it go up again and restore it to its position.
					//checks if alien is out of the screen, according to the images height, not an absolute value so 
					//it is more robust (any image can be inserted without causing problems to the functionality)
					if (fleet[chosen_one]->getY() < -fleet[chosen_one]->getHeight())
					{
						//makes it go to the top of the screen again
						fleet[chosen_one]->setY(DEFAULT_SCREENHEIGHT);
						fleet[chosen_one]->setCrossedScreen(true);
					}

					/*once the y coordinate of the alien that has is attacking is equal (within the range of 2 pixels 
					//above or below) to its standard y coordinate, assign the standard x position to the new x position 
					//of the alien */

					if (fleet[chosen_one]->getCrossedScreen() == true)
					{
						if (fleet[chosen_one]->getY() > *(squad.getStandardYPositions() + chosen_one) - 2 &&
							fleet[chosen_one]->getY() < *(squad.getStandardYPositions() + chosen_one) + 2)
						{
							//cout << "assemble!!\n\n";
							fleet[chosen_one]->setX(*(squad.getStandardXPositions() + chosen_one));
							fleet[chosen_one]->setAttackingStatus(false);
							fleet[chosen_one]->setCrossedScreen(false);
						}//close inner if
					}//close if (fleet[chosen_one]->getCrossedScreen() == true)
				}//close if (fleet[i]->getAttackingStatus() == true)
			}//close if(fleet[i]->getFlag() == false)
		}//close for (int i = 0; i < fleet.size(); i++)


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

		//collision player's laser and alien
		if (shoot == true)
		{			
			zap.shootLaser(hero.getX(), hero.getY()+10, timer, shoot,1);
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
						zap.setLaserYIncrement(0);
						//decrement the number of aliens that are alive
						squad.set_operating_ships(squad.get_operating_ships() - 1);
						//cout << "operating ships: " << squad.get_operating_ships() << "\n";
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
			//if one alien is attacking, then it wont be shifted sideways
			if (fleet[i]->getAttackingStatus() == false)
			{
				fleet[i]->setX(squad.shift_army(i, timer, fleet[i]->getShiftSpeed()));
			}
		}
		//cout << "0th x after: "<<fleet[0]->getX() << endl;

		
		
		timer -= a_deltaTime;
	}
	//cout << "operating ships: " << squad.get_operating_ships() << "\n";

	if (squad.get_operating_ships() == 0)
		onDestroy();
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
	//cout << "laserGuns vector size: " << laserGuns.size() << endl;

	//setImageId(sprite_choice, false);
	
	drawAliens();
	
	/*for (int a = 0; a < laserGuns.size(); a++)
	{
		//cout << "drawing alien lasers! " << a << "th time.\n";
		MoveSprite(laserGuns[a]->getImageId(), laserGuns[a]->getX(), laserGuns[a]->getY());
		DrawSprite(laserGuns[a]->getImageId());
	}*/
	
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
	cout << "game over!\n";
	system("pause");
	//this->~GameLoop();
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




