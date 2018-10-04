#include <Engine/Sprite.h>
#include <time.h>
#include "Player.h"

/**
*   @brief   Default Constructor.
*/
Player::Player()
{
	srand((int)time(NULL));
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Player::~Player()
{

}

/**
*   @brief   Checks collisions and updates accordingly
*   @details This function is used to check the position of the player 
paddle against the edge of the screen
*   @see     KeyEvent
*   @return  void
*/
void Player::atEdge()
{
	// if the paddle is at the edge of the screen stop moving
	if ((paddle->yPos() <= 0) &&
		(velocity == -PADDLE_SPEED))
	{
		velocity = 0.f;
	}
	if ((paddle->yPos() >= WINDOW_HEIGHT - paddle->height()) &&
		(velocity == PADDLE_SPEED))
	{
		velocity = 0.f;
	}

}

/**
*   @brief   Get the score
*   @details This function is used to get the score of the player
*   @see     KeyEvent
*   @return  int
*/
int Player::getScore()
{
	return score;
}

/**
*   @brief   Set the score
*   @details This function is used to set the score of the player
*   @see     KeyEvent
*   @return  void
*/
void Player::setScore(int new_setting)
{
	score = new_setting;
}

/**
*   @brief   Get the velocity
*   @details This function is used to get the velocity of the player paddle
*   @see     KeyEvent
*   @return  float
*/
float Player::getVelocity()
{
	return velocity;
}

/**
*   @brief   Set the velocity
*   @details This function is used to set the velocity of the player paddle
*   @see     KeyEvent
*   @return  void
*/
void Player::setVelocity(float new_setting)
{
	velocity = new_setting;
}

/**
*   @brief   Set the speed setting
*   @details This function is used to set the velocity of the player paddle
*   @see     KeyEvent
*   @return  void
*/
void Player::setSpeedSetting(float new_setting)
{
	speed_setting = new_setting;
}

/**
*   @brief   Get the speed setting
*   @details This function is used to get the speed setting of the player paddle
*   @see     KeyEvent
*   @return  float
*/
float Player::getSpeedSetting()
{
	return speed_setting;
}
/**
*   @brief   Calculate ball destination
*   @details This function is used to calculate where the ball will
be on the y axis when it reaches the paddle on the x axis
*   @see     KeyEvent
*   @return  float
*/
float Player::judgeBallDest(float ball_pos_x, float ball_pos_y, Vector ball_vel, 
	float ball_speed_setting, Character aiChar)
{
	//variable to judge time for ball to reach paddle on the x axis at
	// current velocity
	int time_to_hit = 0;
	// destination of the ball on the y axis
	float y_dest = 0.f;
	// balls current y velocity 
	float y_velocity = 0.f;

	// get current ball position and velocity on the y axis
	y_velocity = ball_vel.getVectorY();
	y_dest = ball_pos_y;
	// count how many times the ball has to travel the current x velocity
	// till the ball reaches the paddle
	for (float i = ball_pos_x; i < (WINDOW_WIDTH - (BALL_SIZE * 2.f));
		i = i + (ball_vel.getVectorX() * ball_speed_setting))
	{
		time_to_hit++;
	}

	// for the number of times the ball has to travel in the x axis till
	// the ball reaches the paddle get the y position of the ball
	for (int j = 0; j < time_to_hit; j++)
	{
		// check if the ball hits the edge and update velocity
		if (y_dest <= 0.f) 
		{
			y_velocity = (0.f - y_velocity);
		}
		else if (y_dest > WINDOW_HEIGHT - BALL_SIZE)
		{
			y_velocity = (0.f - y_velocity);
		}
		// destination is the current destination plus the overall velocity
		y_dest = (y_dest + (y_velocity * ball_speed_setting));
	}

	return y_dest;
}

/**
*   @brief   Shot choice
*   @details This function is used to generate a shot choice for the AI
*   @see     KeyEvent
*   @return  void
*/
void Player::shotChoice(float dest, Character aiChar)
{


	// generate random number between 1 and 7 and update shot chosen bool
	shot_choice = (rand()%7 + 1);
	shot_chosen = true;


	switch (shot_choice)
	{
	case 1:
		// top corner of paddle
		ai_dest = (dest - (paddle->height() * 0.07f));
		break;
	case 2:
		// top center of paddle
		ai_dest = (dest - (paddle->height() * 0.21f));
		break;
	case 3:
		// top inside of paddle
		ai_dest = (dest - (paddle->height() * 0.36f));
		break;
	case 4:
		// center of paddle
		ai_dest = (dest - (paddle->height() * 0.5f));
		break;
	case 5:
		// bottom inside of paddle
		ai_dest = (dest - (paddle->height() * 0.64f));
		break;
	case 6:
		// bottom center of paddle
		ai_dest = (dest - (paddle->height() * 0.85f));
		break;
	case 7:
		// bottom corner of paddle
		ai_dest = (dest - (paddle->height() * 0.92f));
		break;

	}

	// generate random number between 1 and 10. if the number is below the 
	// characters error rate adjust the paddle destination by the character's 
	// error margin
	if (rand() % 10 < aiChar.error_rate)
	{
		if (ai_dest + (paddle->height() / 2) < dest)
		{
			ai_dest -= aiChar.error_margin;
		}
		else
		{
			ai_dest += aiChar.error_margin;
		}
	}
	// check and adjust in case the target is above or below the edges of the 
	// window
	if (ai_dest < 0.f)
	{
		ai_dest = 0.f;
	}
	if (ai_dest > (WINDOW_HEIGHT - paddle->height()))
	{
		ai_dest = WINDOW_HEIGHT - paddle->height();
	}
}

/**
*   @brief   AI controller
*   @details This function is used to control the ai paddle until it reaches its
destination and control if a shot choice is made
*   @see     KeyEvent
*   @return  void
*/
void Player::aiCont(float ball_pos_x, float ball_pos_y, Vector ball_vel, 
	float ball_speed_setting, Character aiChar)
{
	// if no shot choice has been made 
	if ((shot_chosen == false) && (ball_vel.getVectorX() > 0))
	{
		// calculate where the ball will hit
		float ball_dest = judgeBallDest(ball_pos_x, ball_pos_y, ball_vel,
			ball_speed_setting, aiChar);
		// decide on a shot choice 
		shotChoice(ball_dest, aiChar);
	}
	
	// if the ai hit the ball return the paddle to the center until a new 
	// shot choice is made
	if (ball_vel.getVectorX() < 0.f)
	{
		ai_dest = ((WINDOW_HEIGHT * 0.5f) - (paddle->height() * 0.5f));
	}
	
	// reset shot chosen bool to false when ball reaches specific point on 
	// the screen depending on the character settings
	if ((ball_vel.getVectorX() > 0) && (ball_pos_x > (WINDOW_WIDTH * 0.5f) +
		aiChar.reaction_time) && (ball_pos_x <
		(WINDOW_WIDTH * 0.5f) + 20.f + aiChar.reaction_time))

	{
		shot_chosen = false;
	}

	// depending on characters nerve rating and a random number test
	// if failed chose a new shot at the last minute
	if ((rand() % 10 + 1 < aiChar.nerve)
		&& (ball_vel.getVectorX() > 0.f) && (ball_pos_x >
		(WINDOW_WIDTH * 0.9f)) && (ball_pos_x <(WINDOW_WIDTH * 0.91f)))
	{
		shot_chosen = false;
	}
	
	// move paddle towards target until within 3 pixel of target
	if (ai_dest > paddle->yPos() + 6.f)
	{
		velocity = (PADDLE_SPEED * 0.75f);
	}
	else if (ai_dest < paddle->yPos() - 6.f)
	{
		velocity = -(PADDLE_SPEED * 0.75f);
	}
	else 
	{
		velocity = 0;
	}

}