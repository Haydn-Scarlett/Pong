
#include <Engine/Sprite.h>

#include "Ball.h"

/**
*   @brief   Default Constructor.
*/
Ball::Ball()
{

}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Ball::~Ball()
{

}

/**
*   @brief   Serve
*   @details This function is used to set the serve direction
of the ball after a point is scored
*   @see     KeyEvent
*   @return  void
*/
void Ball::serve()
{

	if (player_1_serve == false)
	{
		velocity.setVector(-1.0f, 0.0f);
		player_1_serve = true;
	}
	else
	{
		velocity.setVector(1.0f, 0.0f);
		player_1_serve = false;
	}
}

/**
*   @brief   Checks collisions and updates accordingly
*   @details This function is check ball collisions against the top and
bottom walls and the two player paddles
*   @see     KeyEvent
*   @return  int
*/
int Ball::isCollision(Player* player_one, Player* player_two)
{
	// if the ball is at the top or bottom edge of the window deflect in 
	// opposite direction on the y axis
	if (((ball->yPos() <= 0) && (velocity.getVectorY() < 0)) ||
		((ball->yPos() > WINDOW_HEIGHT - BALL_SIZE) &&
		(velocity.getVectorY() > 0)))
	{
		velocity.setVector(velocity.getVectorX(), (0 - velocity.getVectorY()));
		return NO_HIT;
	}

	// if the ball is at the left edge of the window check to see if it hits
	// the paddle or not
	if ((ball->xPos() < PADDLE_WIDTH) && (velocity.getVectorX() < 0.f))
	{
		// if the ball does not make contact with the paddle then increment 
		// opponents score, update ball velocity, return point scored to update 
		// function
		if ((ball->yPos() > (player_one->paddle->yPos() +
			player_one->paddle->height() + (BALL_SIZE / 2))) ||
			((ball->yPos() + BALL_SIZE) < player_one->paddle->yPos()))
		{
			if (ball->xPos() < 0.f)
			{
				player_two->setScore(player_two->getScore() + 1);
				return POINT_SCORED;
			}
		}

		// else if the ball makes contact with the paddle update the ball's 
		// velocity accordingly and return that a player hit the ball
		else if (ball->yPos() + (BALL_SIZE / 2) >=
			player_one->paddle->yPos() + (player_one->paddle->height() * 0.85))
		{
			velocity.setVector(0.707f, 0.707f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_one->paddle->yPos() +
			(player_one->paddle->height() * 0.71))
		{
			velocity.setVector(0.866f, 0.500f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_one->paddle->yPos() +
			(player_one->paddle->height() * 0.57))
		{
			velocity.setVector(0.966f, 0.259f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_one->paddle->yPos() +
			(player_one->paddle->height() * 0.43))
		{
			velocity.setVector(1.f, 0.f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_one->paddle->yPos() +
			(player_one->paddle->height() * 0.29))
		{
			velocity.setVector(0.966f, -0.259f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_one->paddle->yPos() +
			(player_one->paddle->height() * 0.14))
		{
			velocity.setVector(0.866f, -0.500f);
			return PLAYER_HIT;
		}
		else if ((ball->yPos() + BALL_SIZE) >= player_one->paddle->yPos())
		{
			velocity.setVector(0.707f, -0.707f);
			return PLAYER_HIT;
		}

	}
	// if the ball is at the right edge of the window check to see if it hits
	// the paddle or not
	else if ((ball->xPos() > WINDOW_WIDTH - (PADDLE_WIDTH + BALL_SIZE))
		&& (velocity.getVectorX() > 0))
	{
		// if the ball does not make contact with the paddle then increment 
		// opponents score, update ball velocity, return point scored to update 
		// function
		if ((ball->yPos() > (player_two->paddle->yPos() +
			player_two->paddle->height() + (BALL_SIZE / 2))) ||
			((ball->yPos() + BALL_SIZE) < player_two->paddle->yPos())) 
		{
			if(ball->xPos() > (WINDOW_WIDTH - BALL_SIZE))
			{
				player_one->setScore(player_one->getScore() + 1);
				return POINT_SCORED;
			}
		}
		// else if the ball makes contact with the paddle update the ball's 
		// velocity accordingly and return that a player hit the ball
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_two->paddle->yPos() +
			(player_two->paddle->height() * 0.85))
		{
			velocity.setVector(-0.707f, 0.707f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_two->paddle->yPos() +
			(player_two->paddle->height() * 0.71))
		{
			velocity.setVector(-0.866f, 0.500f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_two->paddle->yPos() +
			(player_two->paddle->height() * 0.57))
		{
			velocity.setVector(-0.966f, 0.259f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_two->paddle->yPos() +
			(player_two->paddle->height() * 0.43))
		{
			velocity.setVector(-1.f, 0.f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_two->paddle->yPos() +
			(player_two->paddle->height() * 0.29))
		{
			velocity.setVector(-0.966f, -0.259f);
			return PLAYER_HIT;
		}
		else if (ball->yPos() + (BALL_SIZE / 2) >= player_two->paddle->yPos() +
			(player_two->paddle->height() * 0.14))
		{
			velocity.setVector(-0.866f, -0.500f);
			return PLAYER_HIT;
		}
		else if ((ball->yPos() + BALL_SIZE) >= player_two->paddle->yPos())
		{
			velocity.setVector(-0.707f, -0.707f);
			return PLAYER_HIT;
		}

	}
	// if no collisions detected return no hit
	return NO_HIT;
}

/**
*   @brief   ball coliision
*   @details This function is used detect collisions between two balls and 
update velocities accordingly
*   @see     KeyEvent
*   @return  void
*/
void Ball::ballCollision(Ball* ball_to_check, Player* player_one, Player* player_two)
{
	Vector position_ball_1(ball->xPos(), ball->yPos());
	Vector position_ball_2(ball_to_check->ball->xPos(),
		ball_to_check->ball->yPos());
	// get the mtd
	Vector distance = (position_ball_1.subtract(position_ball_2));
	float dist2 = position_ball_1.getDistance(position_ball_2);

	if (dist2 <= BALL_SIZE)
	{
		// minimum translation distance to push balls apart after intersecting
		Vector reflection_angle;
		// if the balls are not in the eact same position 
		if (distance.getMagnitude() != 0.0f)
		{
			reflection_angle = distance.multiply((
				BALL_SIZE - distance.getMagnitude()) /
				distance.getMagnitude());

		}
		// the balls are in the same position 
		else 
		{
			// change the distance so its length is not 0.0f
			distance.setVector(BALL_SIZE, 0.0f);

			reflection_angle = distance.multiply((BALL_SIZE -
				(BALL_SIZE - 1.0f)) / (BALL_SIZE - 1.0f));
		}
		
		// impact speed
		Vector v = (velocity.subtract(ball_to_check->velocity));
		float vn = v.getScalar(reflection_angle.normalise());

		// if the impact speed is not positive the
		//balls are already moving away from each other
		if (vn <= 0.0f)
		{
			// inverse mass quantities
			float im1 = 1.f / getSpeedSetting();
			float im2 = 1.f / ball_to_check->getSpeedSetting();
			// collision impulse
			float i = (-(1.0f + RESTITUTION) * vn) / (im1 + im2);
			Vector impulse(reflection_angle.multiply(i));

			// change in momentum
			velocity = velocity.add(impulse.multiply(im1));
			ball_to_check->velocity = ball_to_check->velocity.subtract(
				impulse.multiply(im2));

			// get unit vectors if the vector is not already of magnitude 1.0
			if (velocity.getMagnitude() != 1.0f)
			{
				velocity.setVector(velocity.getVectorX() /
					velocity.getMagnitude(), velocity.getVectorY() /
					velocity.getMagnitude());
			
			}
			if (ball_to_check->velocity.getMagnitude() != 1.0f)
			{
				ball_to_check->velocity.setVector(
					ball_to_check->velocity.getVectorX() /
					ball_to_check->velocity.getMagnitude(),
					ball_to_check->velocity.getVectorY() /
					ball_to_check->velocity.getMagnitude());
				
			}

			// move the balls apart until they are no longer colliding
			while (dist2 <= (BALL_SIZE + 0.1f))
			{
				ball->xPos(ball->xPos() +
					(velocity.getVectorX() * getSpeedSetting()));
				ball->yPos(ball->yPos() +
					(velocity.getVectorY() * getSpeedSetting()));
				ball_to_check->ball->xPos(ball_to_check->ball->xPos() +
					(ball_to_check->velocity.getVectorX() *
						ball_to_check->getSpeedSetting()));
				ball_to_check->ball->yPos(ball_to_check->ball->yPos() +
					(ball_to_check->velocity.getVectorY() *
						ball_to_check->getSpeedSetting()));
				isCollision(player_one, player_two);
				position_ball_1.setVector(ball->xPos(), ball->yPos());
				position_ball_2.setVector(ball_to_check->ball->xPos(),
					ball_to_check->ball->yPos());
				dist2 = position_ball_1.getDistance(position_ball_2);
			}
		}
	}
}

/**
*   @brief   set Serve
*   @details This function is used to set the serve bool
*   @see     KeyEvent
*   @return  void
*/
void Ball::setServeBool(bool new_setting)
{
	player_1_serve = new_setting;
}


/**
*   @brief   set vertical bool
*   @details This function is used to set the vertical bool
*   @see     KeyEvent
*   @return  void
*/
void Ball::setVertical(bool new_setting)
{
	vertical = new_setting;
}

/**
*   @brief   set speed setting
*   @details This function is used to set the  speed setting
*   @see     KeyEvent
*   @return  void
*/
void Ball::setSpeedSetting(float new_setting)
{
	speed_setting = new_setting;
}

/**
*   @brief   get speed setting
*   @details This function is used to get the  speed setting
*   @see     KeyEvent
*   @return  float
*/
float Ball::getSpeedSetting()
{
	return speed_setting;
}

/**
*   @brief   get serve setting
*   @details This function is used to get the  serve
*   @see     KeyEvent
*   @return  bool
*/
bool Ball::getServe()
{
	return player_1_serve;
}

/**
*   @brief   get vertical bool setting
*   @details This function is used to get the vertical bool setting
*   @see     KeyEvent
*   @return  bool
*/
bool Ball::getVertical()
{
	return vertical;
}