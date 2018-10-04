#pragma once

/*! \file Constants.h
@brief   Constants that are used throughout the game.
@details Add any new constants to this file.
*/

/**< The window width. Defines how wide the game window is. */
constexpr int WINDOW_WIDTH = 1280;
/**< The window height. Defines the height of the game window */
constexpr int WINDOW_HEIGHT = 720;

/**< Value of PI. */
constexpr float PI = 3.14159265f; 
/**< Value of the amount of energy left after a collision. */
constexpr float RESTITUTION = 1.f;
/**< The background image width. Defines how wide the image is. */
constexpr float CAFE_WIDTH = 1024.f;

/**< Defines the width of a single character image. */
constexpr float SPLASH_WIDTH = 640.f;
/**< Defines the height of a single character image. */
constexpr float SPLASH_HEIGHT = 360.f;

/**< Defines the width of a single character image. */
constexpr float CHARACTER_WIDTH = 144.f;
/**< Defines the height of a single character image. */
constexpr float CHARACTER_HEIGHT = 256.f;
/**< Defines the width and height of a single character portrait image. */
constexpr float CHARACTER_FACE = 120.f;

/**< Defines the width and height of a single character portrait image. */
constexpr float BALL_SIZE = 16.f;
/**< Defines the maximum positive speed of the ball in any direction. */
constexpr float MAX_BALL_VELOCITY = 5.f;
/**< Defines the minimum number of balls. */
constexpr int MIN_BALLS = 1;
/**< Defines the maximum number of balls. */
constexpr int MAX_BALLS = 3;

/**< Defines the maximum number of characters. */
constexpr int NUM_CHARACTERS = 5;
/**< Defines the maximum number of High scores. */
constexpr int NUM_HIGH_SCORES = 10;
/**< Defines the game over indicator. */
constexpr int GAME_OVER = 15;

/**< Defines the standard height of the player paddle. */
constexpr float PADDLE_HEIGHT = 72.f;
/**< Defines the standard width of the player paddle. */
constexpr float PADDLE_WIDTH = 16.f;
/**< Defines the standard speed of the player paddle. */
constexpr float PADDLE_SPEED = 3.f;

// defines screen to display options
enum { MAIN_SCREEN, OPPONENT_SCREEN, SETTINGS_SCREEN, HIGH_SCORES_SCREEN, 
	GAME_OVER_SCREEN, NEW_HIGH_SCORE, IN_GAME , SPLASH_SCREEN};
// defines main menu options
enum { ONE_PLAYER, TWO_PLAYER, SETTINGS, HIGH_SCORES, EXIT_GAME };
// defines settings menu options
enum { BALL_SPEED_SETTING, NUMBER_BALLS_SETTING, PADDLE_SIZE_SETTING, 
	PADDLE_SPEED_SETTING, SAVE_SETTINGS };
// defines opponents menu options
enum {	MAVIS, NINA, JOHN, PAULA, RAUL };
// defines speed setting options
enum { VERY_SLOW, SLOW, NORMAL, FAST, VERY_FAST };
// defines paddle size setting options
enum { VERY_SMALL, SMALL, STANDARD, LARGE, VERY_LARGE };

// constant definitions for paddle speed setting modifiers
constexpr float VERY_EASY_SPEED = 0.5;
constexpr float EASY_SPEED = 0.75;
constexpr float NORMAL_SPEED = 1.0;
constexpr float HARD_SPEED = 1.25;
constexpr float VERY_HARD_SPEED = 1.5;

// constant definitions for paddle size modifiers
constexpr float VERY_EASY_PADDLE = 1.5;
constexpr float EASY_PADDLE = 1.25;
constexpr float NORMAL_PADDLE = 1.0;
constexpr float HARD_PADDLE = 0.75;
constexpr float VERY_HARD_PADDLE = 0.5;

// defines collision results
enum { NO_HIT, PLAYER_HIT, POINT_SCORED };