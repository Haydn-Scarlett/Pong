#pragma once

#include "Vector.h"
#include "Constants.h"

// struct for character information
struct Character
{
	// float to determine ai characters reaction time
	float reaction_time = 0.f;
	// int to define ai character error rate
	int error_rate = 0;
	// float to determine error margin used to ecide how far the paddle will 
	// move from the original shot choice destination
	float error_margin = 0.f;
	// int to determine ai characters nerve used to decide if ai will change 
	// their shot choice at the last minute
	int nerve = 0;
	// ai characters paddle speed setting
	float speed_setting = 0.f;
	// ai characters paddle size setting
	float paddle_size_setting = 0.f;
};

class Player
{
public:
	Player();
	~Player();

	// function to detect edge collision for player paddle
	void atEdge();
	// get and set functions
	float getVelocity();
	void setVelocity(float new_setting);
	float getSpeedSetting();
	void setSpeedSetting(float new_setting);
	int getScore();
	void setScore(int new_setting);

	// funtion to control ai player decisions and paddle movement
	void aiCont(float ball_pos_x, float ball_pos_y, Vector ball_velocity, 
		float ball_speed_setting, Character aiChar);




	/**< Sprite Object. The ball sprite. */
	ASGE::Sprite* paddle = nullptr;  

private:
	// function to work out where the ball will be on the y axis when it reaches 
	// the point that the paddle can hit it
	float judgeBallDest(float ball_pos_x, float ball_pos_y, Vector ball_velocity,
		float ball_speed_setting, Character aiChar);

	// function used to decide on the ai paddle's destination
	void shotChoice(float dest, Character aiChar);

	// integer used to determine shot choice
	int shot_choice = 0;
	// player score
	int score = 0;
	// paddle speed setting
	float speed_setting = 0.f;
	// paddle movement direction
	float velocity = 0.0f;
	// float to control ai paddle destination
	float ai_dest;
	// bool used to check if a shot choice needs to be made
	bool shot_chosen = false;
};


