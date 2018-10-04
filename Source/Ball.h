#pragma once
#include <windows.h>
#include <math.h>
#include "Constants.h"
#include "Player.h"
#include "Vector.h"


class Ball
{
public:
	Ball();
	~Ball();

	/**< Sprite Object. The ball sprite. */
	ASGE::Sprite* ball = nullptr;  

	// vector to hold ball direction
	Vector velocity;


	// ball collision detection functions
	int isCollision(Player* player_one, Player* player_two);
	void ballCollision(Ball* ball_to_check, Player* player_one, Player* player_two);
	// function to change serve direction
	void serve();
	// function to set serve bool
	void setServeBool(bool new_setting);
	// function to set vertical bool
	void setVertical(bool new_setting);
	// function to change speed setting
	void setSpeedSetting(float new_setting);
	// function to change speed setting
	float getSpeedSetting();
	// function to get the serve setting
	bool getServe();
	// function to get the serve setting
	bool getVertical();

private:

	// ball speed setting
	float speed_setting = 1.0f;
	// bool to determine serve direction
	bool player_1_serve = false;
	// bool to determine if ball is travelling vertically but not horizontally
	bool vertical = false;

};

