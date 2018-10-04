#pragma once
#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>
#include <Engine/OGLGame.h>

#include "GameFont.h"
#include "Ball.h"
#include "Player.h"
#include "Vector.h"

struct GameFont;

/**
*  Pong. An OpenGL Game based on ASGE.
*/
struct Score
{
	long score = 0;
	std::string initials;
};



class PongGame :
	public ASGE::OGLGame
{
public:
	PongGame();
	~PongGame();
	virtual bool init() override;


private:
	// keyboard input handler function
	void keyHandler(ASGE::SharedEventData data);
	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;
	// function to reset paddle and ball positions
	void reset();
	// function to start a new game
	void newGame();
	// function to handle collision detection
	void collisionDetection();
	// function to update when a point has been scored
	void pointScored();
	// function to display main menu
	void renderMainMenu();
	// function to display single player opponent choice menu
	void renderOpponentMenu();
	// function to display settings menu
	void renderSettingsMenu();
	// function to display high scores
	void renderHighScores();
	// function to display new high score intital entry menu
	void renderNewHighScore();
	// function to display the game over screen
	void renderGameOver();
	// function to display a game
	void renderInGame();
	// function to display the splash screen
	void renderSplash();
	// function to set all velocities to zero
	void zeroVelocities();
	// function to update settings on exit of settings menu
	bool updateHighScores();
	// function to update settings on exit of settings menu
	void updateSettings();
	// function to clear arrays during initialisation
	void clearArrays();
	// function to load game files during initialisation
	void loadFiles();
	// function to save high scores
	void saveHighScores();
	// function to save character file
	void saveCharacters();
	// function to set character attributes in array during initialisation
	void setupCharacters();

	/**< Sprite Object. The splash screen sprite for the main game. */
	ASGE::Sprite* splash_screen = nullptr;
	/**< Sprite Object. The background sprite for the main game. */
	ASGE::Sprite* background = nullptr;    
	/**< Sprite Object. The background sprite for the opponent selection menu.*/
	ASGE::Sprite* cafe = nullptr;    
    /**< Sprite Objects. The character sprites. */
	ASGE::Sprite* mavis = nullptr;
	ASGE::Sprite* nina = nullptr;     
	ASGE::Sprite* paula = nullptr;   
	ASGE::Sprite* john = nullptr;		 
	ASGE::Sprite* raul = nullptr;    

	/**< Sprite Objects. The character portrait sprites. */
	ASGE::Sprite* mavis_head = nullptr;    
	ASGE::Sprite* nina_head = nullptr;     
	ASGE::Sprite* paula_head = nullptr;    
	ASGE::Sprite* john_head = nullptr;     
	ASGE::Sprite* raul_head = nullptr;    
	

	// ball object contains sprite, collision detection etc.
	Ball ball1;
	// ball object contains sprite, collision detection etc.
	Ball ball2;
	// ball object contains sprite, collision detection etc.
	Ball ball3;
	// player objects contains sprite, edge detection etc.
	Player player_1;
	Player player_2;

	// character array to hold opponent attributes
	Character characters[NUM_CHARACTERS];
	// High scores array to hold high scores
	Score high_scores[NUM_HIGH_SCORES];

	/**< Exit boolean. If true the game loop will exit. */
	bool exit = false;
	/**< New game boolean. If true a new game will be setup. */
	bool new_game = false;
	/**< Winner boolean. If true player 1 won. Used to determine which game 
	over message to display */
	bool player_1_winner = false;
	/**< one player boolean. If true a game over screen will reflect this. */
	bool one_player = false;
	/**< pause boolean. If true the game will pause. */
	bool pause = false;

	/**< Key Input Callback ID. */
	int  key_callback_id = -1;
	/**< Used to determine which screen will be displayed. */
	int screen_to_display = SPLASH_SCREEN;
	// used to determine if a point has been scored or if the paddle hit the ball
	// or no collision detected (returned from collision detection)
	int collision_result = 0;
	// main menu option
	int menu_option = ONE_PLAYER;
	// settings menu option
	int settings_menu_option = BALL_SPEED_SETTING;
	// ball speed settings menu option
	int ball_speed_setting = NORMAL;
	// number of balls settings menu option
	int number_of_balls = MIN_BALLS;
	// paddle size settings menu option
	int paddle_size = STANDARD;
	// paddle speed settings menu option
	int paddle_speed = NORMAL;
	// opponent selection menu option for single player
	int opponent = MAVIS;
	// rally count used to speed up ball at set intervals
	int rally_count = 0;
	// used to decide which tip to display
	int tip = 0;
	// used to decide which index to update in high score array
	int high_score_idx_to_update = 0;
	// used to decide which index to update in initials string
	int initial = 0;
	// single player score calculation result
	long single_player_score = 0;
	// game speed float used to increase the speed of the ball over time
	float game_speed = 1.f;
	// used to decide which index to update in initials string
	char new_initial = 'A';
	// string to hold the new initials for a new high score
	std::string new_initials = "AAA";
};

