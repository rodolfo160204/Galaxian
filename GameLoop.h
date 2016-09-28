#ifndef __Tutorial1_H_
#define __Tutorial1_H_

#include "Application.h"
#include "Stars.h"
#include "Aliens.h"
#include <glm/glm.hpp>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include "Useful_Methods.h"
#include "Laser.h"
#include "Background.h"
#include "Player.h"

// Derived application class that wraps up all globals neatly
class GameLoop : public NHTV::Application
{
public:

	GameLoop();
	virtual ~GameLoop();
	

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	/*void stand_by(std::vector<Enemy*> fleet, float &shif, float delta, int choice);
	void shift_army(std::vector<Enemy*> fleet, float shift, float delta, int choice);*/
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	//Sets the initial coordinates of each sprite
	void setImageId(int choice, bool first_time);
	void drawAliens();

	int m_iScreenWidth;
	int m_iScreenHeight;
	int sprite_choice = 1;
	

private:
	

	Stars star1;
	Army squad;

	//Variable that indicates if the player has fired (shot is true until the bullet is not on the screen anymore)
	bool shoot;	
	
	unsigned int m_iPlayerSprite;
	unsigned int player_laser_sprite;
	unsigned int background;
	unsigned int alien;
	unsigned int *alien_texture;
	//unsigned int constellation[9];

	 
	float back_x = 0, back_y = 0;
	float xPos = 0; 
	float yPos = 0;
	float laser_width = 5;
	float laser_height = 15;

	bool alien_hit = false;
	
	Enemy et;
	Background sky;
	Player hero;
	//player laser object
	Laser zap;

	//alien laser vector of pointers to Laser object
	std::vector <Laser*> laserGuns;
	
	float timer;
	time_t t_begin;
	time_t t_attack_begin;
	time_t t_animate;
	time_t t_attack;

	int star_index;
	int number_of_stars = 0;
	bool  new_star;
	//counter for the horizontal movement of the aliens while on hold.
	float alien_sliding_counter = 0.1f;
	unsigned int sad_alien_images;
	unsigned int happy_alien_images;
	unsigned int alien_laser;
	//vector of pointers to objects
	std::vector <Enemy*> fleet;
	
	float *x_pointer;
	float *y_pointer;
	

};

#endif // __Tutorial1_H_

