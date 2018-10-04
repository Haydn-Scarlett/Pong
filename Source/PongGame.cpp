#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "PongGame.h"

/**
*   @brief   Default Constructor.
*/
PongGame::PongGame()
{


}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
PongGame::~PongGame()
{
	this->inputs->unregisterCallback(key_callback_id);

	// Delete sprites
	if (splash_screen)
	{
		delete splash_screen;
		splash_screen = nullptr;
	}
	// Background
	if (background)
	{
		delete background;
		background = nullptr;
	}
	// Player Paddles
	if (player_1.paddle)
	{
		delete player_1.paddle;
		player_1.paddle = nullptr;
	}
	if (player_2.paddle)
	{
		delete player_2.paddle;
		player_2.paddle = nullptr;
	}

	// Ball
	if (ball1.ball)
	{
		delete ball1.ball;
		ball1.ball = nullptr;
	}

	// Single Player Menu background
	if (cafe)
	{
		delete cafe;
		cafe = nullptr;
	}
	// Character Sprites
	if (mavis)
	{
		delete mavis;
		mavis = nullptr;
	}
	if (mavis_head)
	{
		delete mavis_head;
		mavis_head = nullptr;
	}
	if (nina)
	{
		delete nina;
		nina = nullptr;
	}
	if (nina_head)
	{
		delete nina_head;
		nina_head = nullptr;
	}
	if (paula)
	{
		delete paula;
		paula = nullptr;
	}
	if (paula_head)
	{
		delete paula_head;
		paula_head = nullptr;
	}
	if (john)
	{
		delete john;
		john = nullptr;
	}
	if (john_head)
	{
		delete john_head;
		john_head = nullptr;
	}
	if (raul)
	{
		delete raul;
		raul = nullptr;
	}
	if (raul_head)
	{
		delete raul_head;
		raul_head = nullptr;
	}
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The keyHandler callback should also
be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool PongGame::init()
{
	// Set the window dimensions
	game_width = WINDOW_WIDTH;
	game_height = WINDOW_HEIGHT;

	if (!initAPI())
	{
		return false;
	}

	// Setup The Renderer
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

	// Set the window title
	renderer->setWindowTitle("Pong Cafe");

	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	// enable noob mode
	inputs->use_threads = false;

	// input handling functions
	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &PongGame::keyHandler, this);

	// load the splash screen sprite
	splash_screen = renderer->createRawSprite();
	splash_screen->loadTexture(".\\Resources\\Textures\\splash_screen.png");
	splash_screen->width(SPLASH_WIDTH);
	splash_screen->height(SPLASH_HEIGHT);

	// load the background sprites
	background = renderer->createRawSprite();
	background->loadTexture(".\\Resources\\Textures\\background.jpg");
	background->width((float)WINDOW_WIDTH);
	background->height((float)WINDOW_HEIGHT);

	cafe = renderer->createRawSprite();
	cafe->loadTexture(".\\Resources\\Textures\\cafe.png");
	cafe->width(CAFE_WIDTH);
	cafe->height((float)WINDOW_HEIGHT);


	// load the ball sprite
	ball1.ball = renderer->createRawSprite();
	ball1.ball->loadTexture(".\\Resources\\Textures\\pong_ball.png");
	ball1.ball->width(BALL_SIZE);
	ball1.ball->height(BALL_SIZE);
	ball1.ball->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
	// load the ball sprite
	ball2.ball = renderer->createRawSprite();
	ball2.ball->loadTexture(".\\Resources\\Textures\\pong_ball.png");
	ball2.ball->width(BALL_SIZE);
	ball2.ball->height(BALL_SIZE);
	ball2.ball->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
	// load the ball sprite
	ball3.ball = renderer->createRawSprite();
	ball3.ball->loadTexture(".\\Resources\\Textures\\pong_ball.png");
	ball3.ball->width(BALL_SIZE);
	ball3.ball->height(BALL_SIZE);
	ball3.ball->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	// load the paddles
	player_1.paddle = renderer->createRawSprite();
	player_1.paddle->loadTexture(".\\Resources\\Textures\\paddle.png");
	player_1.paddle->width(PADDLE_WIDTH);
	player_1.paddle->height(PADDLE_HEIGHT);
	player_1.paddle->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
	player_1.setSpeedSetting(NORMAL_SPEED);


	// load the paddles
	player_2.paddle = renderer->createRawSprite();
	player_2.paddle->loadTexture(".\\Resources\\Textures\\paddle.png");
	player_2.paddle->width(PADDLE_WIDTH);
	player_2.paddle->height(PADDLE_HEIGHT);
	player_2.paddle->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
	player_2.setSpeedSetting(NORMAL_SPEED);


	// load the characters
	mavis = renderer->createRawSprite();
	mavis->loadTexture(".\\Resources\\Textures\\Mavis.png");
	mavis->width(CHARACTER_WIDTH);
	mavis->height(CHARACTER_HEIGHT);
	mavis->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	mavis_head = renderer->createRawSprite();
	mavis_head->loadTexture(".\\Resources\\Textures\\Mavis_head.png");
	mavis_head->width(CHARACTER_FACE);
	mavis_head->height(CHARACTER_FACE);
	mavis_head->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);


	nina = renderer->createRawSprite();
	nina->loadTexture(".\\Resources\\Textures\\Nina.png");
	nina->width(CHARACTER_WIDTH);
	nina->height(CHARACTER_HEIGHT);
	nina->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
	
	nina_head = renderer->createRawSprite();
	nina_head->loadTexture(".\\Resources\\Textures\\Nina_head.png");
	nina_head->width(CHARACTER_FACE);
	nina_head->height(CHARACTER_FACE);
	nina_head->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	paula = renderer->createRawSprite();
	paula->loadTexture(".\\Resources\\Textures\\Paula.png");
	paula->width(CHARACTER_WIDTH);
	paula->height(CHARACTER_HEIGHT);
	paula->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	paula_head = renderer->createRawSprite();
	paula_head->loadTexture(".\\Resources\\Textures\\Paula_head.png");
	paula_head->width(CHARACTER_FACE);
	paula_head->height(CHARACTER_FACE);
	paula_head->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	john = renderer->createRawSprite();
	john->loadTexture(".\\Resources\\Textures\\JP.png");
	john->width(CHARACTER_WIDTH);
	john->height(CHARACTER_HEIGHT);
	john->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	john_head = renderer->createRawSprite();
	john_head->loadTexture(".\\Resources\\Textures\\JP_head.png");
	john_head->width(CHARACTER_FACE);
	john_head->height(CHARACTER_FACE);
	john_head->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	raul = renderer->createRawSprite();
	raul->loadTexture(".\\Resources\\Textures\\Raul.png");
	raul->width(CHARACTER_WIDTH);
	raul->height(CHARACTER_HEIGHT);
	raul->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	raul_head = renderer->createRawSprite();
	raul_head->loadTexture(".\\Resources\\Textures\\Raul_head.png");
	raul_head->width(CHARACTER_FACE);
	raul_head->height(CHARACTER_FACE);
	raul_head->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

	

	// clear the arrays
	clearArrays();
	loadFiles();
	reset();
	zeroVelocities();
	return true;
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
keyboard input. For this assignment, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void PongGame::keyHandler(ASGE::SharedEventData data)
{

	// converts the system event into a key one
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
		
	// checks to see if the spacebar key was released
	if (key->key == ASGE::KEYS::KEY_SPACE &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if ((number_of_balls == 2 && ball1.getVertical() && ball2.getVertical())
			|| (number_of_balls == 3 && ball1.getVertical() && 
				ball2.getVertical() && ball3.getVertical()))
		{
			ball1.serve();
			ball2.serve();
			ball3.serve();
			ball1.setVertical(false);
			ball2.setVertical(false);
			ball3.setVertical(false);
		}
		
	}
	// checks to see if the esc key was released
	if (key->key == ASGE::KEYS::KEY_ESCAPE &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		// exit the game
		signalExit();
	}
	// checks to see if the right key was released
	if (key->key == ASGE::KEYS::KEY_RIGHT &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		// if in the settings menu
		if (screen_to_display == SETTINGS_SCREEN)
		{
			// Update setting of current option
			switch (settings_menu_option)
			{
			case 0:
				ball_speed_setting += 1;
				if (ball_speed_setting > VERY_FAST)
				{
					ball_speed_setting = VERY_SLOW;
				}
				break;
			case 1:
				number_of_balls += 1;
				if (number_of_balls > MAX_BALLS)
				{
					number_of_balls = MIN_BALLS;
				}
				break;
			case 2:
				paddle_size += 1;
				if (paddle_size > VERY_LARGE)
				{
					paddle_size = VERY_SMALL;
				}
				break;
			case 3:
				paddle_speed += 1;
				if (paddle_speed > VERY_FAST)
				{
					paddle_speed = VERY_SLOW;
				}
				break;
			default:
				break;

			}
		}
		// if in the new high score
		else if (screen_to_display == NEW_HIGH_SCORE)
		{
			initial += 1;
			if (initial > 2)
			{
				initial = 0;
			}
			new_initial = new_initials[initial];
		}
		// if in the single player menu
		else if (screen_to_display == OPPONENT_SCREEN)
		{

			opponent += 1;
			if (opponent > RAUL)
			{
				opponent = MAVIS;
			}
		}
	}
	// checks to see if the left key was released
	if (key->key == ASGE::KEYS::KEY_LEFT &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		// If in settings menu
		if (screen_to_display == SETTINGS_SCREEN)
		{
			// Update setting of current option
			switch (settings_menu_option)
			{
			case BALL_SPEED_SETTING:
				ball_speed_setting -= 1;
				if (ball_speed_setting < VERY_SLOW)
				{
					ball_speed_setting = VERY_FAST;
				}
				break;
			case NUMBER_BALLS_SETTING:
				number_of_balls -= 1;
				if (number_of_balls < MIN_BALLS)
				{
					number_of_balls = MAX_BALLS;
				}
				break;
			case PADDLE_SIZE_SETTING:
				paddle_size -= 1;
				if (paddle_size < VERY_SMALL)
				{
					paddle_size = VERY_LARGE;
				}
				break;
			case PADDLE_SPEED_SETTING:
				paddle_speed -= 1;
				if (paddle_speed < VERY_SLOW)
				{
					paddle_speed = VERY_FAST;
				}
				break;
			default:
				break;

			}
			
		}
		// if in the new high score
		else if (screen_to_display == NEW_HIGH_SCORE)
		{
			initial -= 1;
			if (initial < 0)
			{
				initial = 2;
			}
			new_initial = new_initials[initial];
		}
		// If in single player menu
		else if (screen_to_display == OPPONENT_SCREEN)
		{

			opponent -= 1;
			if (opponent < MAVIS)
			{
				opponent = RAUL;
			}
		}
	}
	// checks to see if the up key was released
	if (key->key == ASGE::KEYS::KEY_UP &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Main menu
		if (screen_to_display == MAIN_SCREEN)
		{
			
			menu_option -= 1;
			// if we go below the first option go to end
			if (menu_option < ONE_PLAYER)
			{
				menu_option = EXIT_GAME;
			}
		}
		// Settings menu
		else if (screen_to_display == SETTINGS_SCREEN)
		{
			settings_menu_option -= 1;
			// if we go below the first option go to end
			if (settings_menu_option < BALL_SPEED_SETTING)
			{
				settings_menu_option = SAVE_SETTINGS;
			}

		}
		// if in the new high score
		else if (screen_to_display == NEW_HIGH_SCORE)
		{
			new_initial += 1;
			if (new_initial > 'Z')
			{
				new_initial = 'A';
			}
			new_initials[initial] = new_initial;
		}
		// else in game or no effect in single player menu / game
		else
		{
			player_2.setVelocity(0.f);
		}
	}
	if (key->key == ASGE::KEYS::KEY_DOWN &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//If in main menu
		if (screen_to_display == MAIN_SCREEN)
		{
			menu_option += 1;
			// if we go over the number of options go to start
			if (menu_option > EXIT_GAME)
			{
				menu_option = ONE_PLAYER;
			}
		}
		// If in settings menu
		else if (screen_to_display == SETTINGS_SCREEN)
		{
			settings_menu_option += 1;
			// if we go over the number of options go to start
			if (settings_menu_option > SAVE_SETTINGS)
			{
				settings_menu_option = BALL_SPEED_SETTING;
			}

		}
		// if in the new high score
		else if (screen_to_display == NEW_HIGH_SCORE)
		{
			new_initial -= 1;
			if (new_initial < 'A')
			{
				new_initial = 'Z';
			}
			new_initials[initial] = new_initial;
		}
		// else in game or no effect in single player menu / game
		else
		{
			player_2.setVelocity(0.f);
		}
	}
	if (key->key == ASGE::KEYS::KEY_UP &&
		key->action == ASGE::KEYS::KEY_PRESSED && !pause &&
		screen_to_display == IN_GAME)
	{
		// player 2 paddle speed set to move the paddle up the screen
		player_2.setVelocity(-PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_UP &&
		key->action == ASGE::KEYS::KEY_REPEATED && !pause &&
		screen_to_display == IN_GAME)
	{
		// player 2 paddle speed set to move the paddle up the screen
		player_2.setVelocity(-PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_DOWN &&
		key->action == ASGE::KEYS::KEY_REPEATED && !pause && 
		screen_to_display == IN_GAME)
	{
		// player 2 paddle speed set to move the paddle down the screen
		player_2.setVelocity(PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_DOWN &&
		key->action == ASGE::KEYS::KEY_PRESSED && !pause && 
		screen_to_display == IN_GAME)
	{
		// player 2 paddle speed set to move the paddle down the screen
		player_2.setVelocity(PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_W &&
		key->action == ASGE::KEYS::KEY_PRESSED && !pause &&
		screen_to_display == IN_GAME)
	{
		// player 1 paddle speed set to move the paddle up the screen
		player_1.setVelocity(-PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_W &&
		key->action == ASGE::KEYS::KEY_REPEATED && !pause && 
		screen_to_display == IN_GAME)
	{
		// player 1 paddle speed set to move the paddle up the screen
		player_1.setVelocity(-PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_W &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		// player 1 paddle speed set to 0
		player_1.setVelocity(0.f);
	}
	if (key->key == ASGE::KEYS::KEY_S &&
		key->action == ASGE::KEYS::KEY_PRESSED && !pause && 
		screen_to_display == IN_GAME)
	{
		// player 1 paddle speed set to move the paddle down the screen
		player_1.setVelocity(PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_S &&
		key->action == ASGE::KEYS::KEY_REPEATED && !pause &&
		screen_to_display == IN_GAME)
	{
		// player 1 paddle speed set to move the paddle down the screen
		player_1.setVelocity(PADDLE_SPEED);
	}
	if (key->key == ASGE::KEYS::KEY_S &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		// player 1 paddle speed set to 0
		player_1.setVelocity(0.f);
	}
	if (key->key == ASGE::KEYS::KEY_P &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		// flip pause bool
		pause = 1 - pause;
	}
	if (key->key == ASGE::KEYS::KEY_ENTER &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		
		// If in the settings menu and save and exit is selected
		if ((screen_to_display == SETTINGS_SCREEN) && 
			(settings_menu_option == 4))
		{
			// update the settings of the paddles and ball
			updateSettings();
			// reset settings menu option to first option
			settings_menu_option = 0;
			tip = (rand() % 8);
			screen_to_display = MAIN_SCREEN;
		}
		// if in the new high score
		else if (screen_to_display == NEW_HIGH_SCORE)
		{
			high_scores[high_score_idx_to_update].initials = new_initials;
			saveHighScores();

			// reset menu variables
			initial = 0;
			new_initial = 'A';
			new_initials = "AAA";
			high_score_idx_to_update = 0;
			tip = (rand() % 8);
			screen_to_display = MAIN_SCREEN;
		}
		// if in the game over screen
		else if (screen_to_display == GAME_OVER_SCREEN)
		{
			// reset menu variables
			one_player = false;
			tip = (rand() % 8);
			screen_to_display = MAIN_SCREEN;
		}
		// If in the high scores display  
		else if (screen_to_display == HIGH_SCORES_SCREEN)
		{
			tip = (rand() % 8);
			screen_to_display = MAIN_SCREEN;
		}
		// If in the main menu 
		else if (screen_to_display == MAIN_SCREEN)
		{
			// change the game state depending on the menu option
			switch (menu_option)
			{
			case ONE_PLAYER:
				// set screen to opponent selection screen
				screen_to_display = OPPONENT_SCREEN;
				break;
			case TWO_PLAYER:
				// set new game bool to true
				new_game = true;
				screen_to_display = IN_GAME;
				break;
			case SETTINGS:
				tip = (rand() % 8);
				screen_to_display = SETTINGS_SCREEN;
				break;
			case HIGH_SCORES:
				tip = (rand() % 8);
				screen_to_display = HIGH_SCORES_SCREEN;
				break;
			case EXIT_GAME:
				// exit the program
				signalExit();
				break;
			default:
				break;
			}
		}
		// if in the single player menu
		else if (screen_to_display == OPPONENT_SCREEN)
		{
			one_player = true;
			// set new game bool to true
			new_game = true;
			screen_to_display = IN_GAME;
		}
	}
}

/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
current frame. Once the current frame is has finished
the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void PongGame::update(const ASGE::GameTime &us)
{
	// if not in a game the ball and the palyers velocitys are set to zero
	if (screen_to_display == SPLASH_SCREEN)
	{
		splash_screen->width((float)splash_screen->width() + 
			((SPLASH_WIDTH * 0.3f)
			* (float)(us.delta_time.count() / 1000.f)));
		splash_screen->height((float)splash_screen->height() + 
			((SPLASH_HEIGHT * 0.3f)
			* (float)(us.delta_time.count() / 1000.f)));
		splash_screen->xPos((WINDOW_WIDTH * 0.5f) - 
			(splash_screen->width() * 0.5f));
		splash_screen->yPos((WINDOW_HEIGHT * 0.5f) -
			(splash_screen->height() * 0.5f));
		if (splash_screen->xPos() < 0.f)
		{
			screen_to_display = MAIN_SCREEN;
		}
	}
	else if(screen_to_display == IN_GAME)
	{
		// if it is a new game initialise the points and start the ball moving
		if (new_game && !pause)
		{
			newGame();
		}
		if (!pause)
		{
			collisionDetection();
		}
		// if single player perform ai calculations
		if (one_player && !pause)
		{
			player_2.aiCont(ball1.ball->xPos(), ball1.ball->yPos(), ball1.velocity,
				ball1.getSpeedSetting(), characters[opponent]);
		}
		// move the game objects  in the right direction
		// update the position of the game objects 
		if (!pause)
		{
			ball1.ball->xPos((float)(ball1.ball->xPos() +
				(((ball1.velocity.getVectorX() * ball1.getSpeedSetting()) *
					game_speed) * 500.f) * (us.delta_time.count() / 1000.f)));
			ball1.ball->yPos((float)(ball1.ball->yPos() +
				(((ball1.velocity.getVectorY() * ball1.getSpeedSetting()) *
					game_speed) * 500.f) * (us.delta_time.count() / 1000.f)));
			player_1.paddle->yPos((float)(player_1.paddle->yPos() +
				((player_1.getVelocity() * player_1.getSpeedSetting()) * 150.f) *
				(us.delta_time.count() / 1000.f)));
			player_2.paddle->yPos((float)(player_2.paddle->yPos() +
				((player_2.getVelocity() * player_2.getSpeedSetting()) * 150.f) *
				(us.delta_time.count() / 1000.f)));
		}
		if (number_of_balls > MIN_BALLS && !pause)
		{
			ball2.ball->xPos((float)(ball2.ball->xPos() +
				(((ball2.velocity.getVectorX() * ball2.getSpeedSetting()) * 
					game_speed) * 500.f) * (us.delta_time.count() / 1000.f)));
			ball2.ball->yPos((float)(ball2.ball->yPos() +
				(((ball2.velocity.getVectorY() * ball2.getSpeedSetting()) *
					game_speed) * 500.f) * (us.delta_time.count() / 1000.f)));
			
			if (ball1.velocity.getVectorX() < 0.001f &&
				ball1.velocity.getVectorX() > -0.001f)
			{
				ball1.setVertical(true);
			}
			else
			{
				ball1.setVertical(false);
			}				
			if(ball2.velocity.getVectorX() < 0.001f &&
				ball2.velocity.getVectorX() > -0.001f)
			{
				ball2.setVertical(true);
			}
			else
			{
				ball2.setVertical(false);
			}
		}
		if (number_of_balls == MAX_BALLS && !pause)
		{
			ball3.ball->xPos((float)(ball3.ball->xPos() +
				(((ball3.velocity.getVectorX() * ball3.getSpeedSetting()) * 
					game_speed) * 500.f) * (us.delta_time.count() / 1000.f)));
			ball3.ball->yPos((float)(ball3.ball->yPos() +
				(((ball3.velocity.getVectorY() * ball3.getSpeedSetting()) * 
					game_speed) * 500.f) * (us.delta_time.count() / 1000.f)));

			if (ball3.velocity.getVectorX() < 0.001f &&
				ball3.velocity.getVectorX() > -0.001f)
			{
				ball3.setVertical(true);
			}
			else
			{
				ball3.setVertical(false);
			}
		}

	}
}

/**
*   @brief   resets paddles and balls
*   @details This function is used to reset the position of the  direction
of the ball and paddles.
*   @see     KeyEvent
*   @return  void
*/
void PongGame::reset()
{
	// set ball position to center of the window
	if (number_of_balls == MIN_BALLS)
	{
		ball1.serve();
		ball1.ball->xPos((WINDOW_WIDTH * 0.5f) - (BALL_SIZE * 0.5f));
		ball1.ball->yPos((WINDOW_HEIGHT * 0.5f) - (BALL_SIZE * 0.5f));
	}
	else if (number_of_balls == 2)
	{
		ball1.serve();
		ball2.serve();
		ball1.ball->xPos((WINDOW_WIDTH * 0.5f) - (BALL_SIZE * 0.5f));
		ball1.ball->yPos((WINDOW_HEIGHT * 0.75f) - (BALL_SIZE * 0.5f));
		ball2.ball->xPos((WINDOW_WIDTH * 0.5f) - (BALL_SIZE * 0.5f));
		ball2.ball->yPos((WINDOW_HEIGHT * 0.25f) - (BALL_SIZE * 0.5f));
	}
	else if (number_of_balls == MAX_BALLS)
	{
		ball1.serve();
		ball2.serve();
		ball3.serve();
		ball1.ball->xPos((WINDOW_WIDTH * 0.5f) - (BALL_SIZE * 0.5f));
		ball1.ball->yPos((WINDOW_HEIGHT * 0.75f) - (BALL_SIZE * 0.5f));
		ball2.ball->xPos((WINDOW_WIDTH * 0.5f) - (BALL_SIZE * 0.5f));
		ball2.ball->yPos((WINDOW_HEIGHT * 0.25f) - (BALL_SIZE * 0.5f));
		ball3.ball->xPos((WINDOW_WIDTH * 0.5f) - (BALL_SIZE * 0.5f));
		ball3.ball->yPos((WINDOW_HEIGHT * 0.5f) - (BALL_SIZE * 0.5f));
	}


	// set player 1 paddle position to center of the window on 
	// far left of window
	player_1.paddle->xPos(0);
	player_1.paddle->yPos((WINDOW_HEIGHT / 2) - (player_1.paddle->height() / 2));

	// set player 2 paddle position to center of the window on 
	// far right of window
	player_2.paddle->xPos(WINDOW_WIDTH - player_2.paddle->width());
	player_2.paddle->yPos((WINDOW_HEIGHT / 2) - (player_2.paddle->height() / 2));

	//reset rally count and game speed
	rally_count = 0;
	game_speed = 1.f;
}

/**
*   @brief   New game
*   @details This function is used to setup a new game
*   @see     KeyEvent
*   @return  void
*/
void PongGame::newGame()
{
	if (one_player)
	{

		// single player only supports one ball so reset number of balls
		number_of_balls = MIN_BALLS;
		// set the paddle to the selected characters speed and size
		player_2.setSpeedSetting(characters[opponent].speed_setting);
		player_2.paddle->height(PADDLE_HEIGHT *
			(characters[opponent].paddle_size_setting));
	}
	reset();
	// reset scores
	player_1.setScore(0);
	player_2.setScore(0);
	single_player_score = 0;
	ball1.serve();
	if (number_of_balls > 1)
	{
		ball2.setServeBool(0 + ball1.getServe());
		ball2.serve();
	}
	if (number_of_balls == 3)
	{
		ball3.setSpeedSetting(ball3.getSpeedSetting() * 0.5f);
		ball3.serve();
	}
	new_game = false;

}

/**
*   @brief   collisionDetection
*   @details This function is used to detect collisions during update
*   @see     KeyEvent
*   @return  void
*/
void PongGame::collisionDetection()
{
	// detect collisions and update if a point has been scored
	collision_result = ball1.isCollision(&player_1,	&player_2);
	// if a point has been scored
	if (collision_result == POINT_SCORED)
	{
		pointScored();
	}
	if (collision_result == PLAYER_HIT)
	{
		// reset collision result to no_hit
		collision_result = NO_HIT;
		rally_count++;
	}
	if (number_of_balls > MIN_BALLS)
	{
		// detect collisions and update if a point has been scored
		collision_result = ball2.isCollision(&player_1, &player_2);
		// if a point has been scored
		if (collision_result == POINT_SCORED)
		{
			pointScored();
		}
		if (collision_result == PLAYER_HIT)
		{
			// reset collision result to no_hit
			collision_result = NO_HIT;
			rally_count++;
		}
		ball1.ballCollision(&ball2, &player_1, &player_2);
	}
	if (number_of_balls == MAX_BALLS)
	{
		// detect collisions and update if a point has been scored
		collision_result = ball3.isCollision(&player_1, &player_2);
		// if a point has been scored
		if (collision_result == POINT_SCORED)
		{
			pointScored();
		}
		if (collision_result == PLAYER_HIT)
		{
			// reset collision result to no_hit
			collision_result = NO_HIT;
			rally_count++;
		}
		ball1.ballCollision(&ball3 , &player_1, &player_2);
		ball2.ballCollision(&ball3, &player_1, &player_2);
	}

	if (rally_count > 5)
	{
		game_speed = 1.f;
		for (int i = 0; i < rally_count; i = i + 6)
		{
			game_speed += 0.2f;
		}
	}
	// if a players paddle is at the edge of the screen stop it moving
	player_1.atEdge();
	player_2.atEdge();
}

/**
*   @brief   vero velocities
*   @details This function is used to set the velocities of the game objects 
to zero
*   @see     KeyEvent
*   @return  void
*/
void PongGame::zeroVelocities()
{
	ball1.velocity.setVector(0.f, 0.f);
	ball2.velocity.setVector(0.f, 0.f);
	ball3.velocity.setVector(0.f, 0.f);
	player_1.setVelocity(0.f);
	player_2.setVelocity(0.f);
}

/**
*   @brief   Point scored
*   @details This function is used to check if the game is over and update
various game variables
*   @see     KeyEvent
*   @return  void
*/
void PongGame::pointScored()
{
	if (one_player)
	{
		single_player_score += rally_count;
	}
	// if either player reaches the winning score return to main menu
	if ((player_1.getScore() == GAME_OVER) || (player_2.getScore() == GAME_OVER))
	{
		
		// turn of ai and update single player score
		if (one_player)
		{
			if (updateHighScores())
			{				
				screen_to_display = NEW_HIGH_SCORE;
			}
			else
			{
				screen_to_display = GAME_OVER_SCREEN;
			}
			// reset paddle speed setting and size
			player_2.setSpeedSetting(player_1.getSpeedSetting());
			player_2.paddle->height(player_1.paddle->height());
		}
		else
		{
			if (number_of_balls == 3)
			{
				ball3.setSpeedSetting(ball1.getSpeedSetting());
			}
			screen_to_display = GAME_OVER_SCREEN;
		}
	}
	// reset collision result to no hit
	collision_result = NO_HIT;
	// reset paddle and ball positions
	reset();

}

/**
*   @brief   Update high scores
*   @details This function is used to check and update if single player high 
score is higher than the current top ten
*   @see     KeyEvent
*   @return  bool
*/
bool PongGame::updateHighScores()
{
	bool update_score = false;
	high_score_idx_to_update = 0;
	single_player_score = (single_player_score *
		(player_1.getScore() - player_2.getScore())) * ((ball_speed_setting + 1) +
		((5 - paddle_size) + (5 - paddle_speed) + (opponent + 1)));
	for (int i = 9; i > -1; i--)
	{
		if (single_player_score > high_scores[i].score)
		{
			high_score_idx_to_update = i;
			update_score = true;
		}
	}
	if (update_score)
	{
		for (int i = 9; i > high_score_idx_to_update; i--)
		{
			high_scores[i].score = high_scores[i - 1].score;
			high_scores[i].initials = high_scores[i - 1].initials;
		}
		high_scores[high_score_idx_to_update].score = single_player_score;

	}
	return update_score;
}

/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
Once the current frame is has finished the buffers are
swapped accordingly and the image shown.
*   @return  void
*/
void PongGame::render(const ASGE::GameTime &)
{

	// use the default game font
	renderer->setFont(renderer->loadFont(".\\Resources\\Fonts\\Consolas.ttf", 20));


	// if in the main menu 
	if (screen_to_display == MAIN_SCREEN)
	{
		//display main menu
		renderMainMenu();
	}
	// if in the setting menu
	else if (screen_to_display == SETTINGS_SCREEN)
	{
		// display settings menu
		renderSettingsMenu();
	}
	// if in the single player menu
	else if (screen_to_display == OPPONENT_SCREEN)
	{
		// display single player opponent selection menu
		renderOpponentMenu();
	}
	// if in the single player menu
	else if (screen_to_display == HIGH_SCORES_SCREEN)
	{
		// display single player opponent selection menu
		renderHighScores();
	}
	// if in the new high score entry menu
	else if (screen_to_display == NEW_HIGH_SCORE)
	{
		// display the new high score entry menu
		renderNewHighScore();
	}
	// if in the single player menu
	else if (screen_to_display == GAME_OVER_SCREEN)
	{
		// display single player opponent selection menu
		renderGameOver();
	}
	// else if in game
	else if (screen_to_display == IN_GAME)
	{
		// display game 
		renderInGame();
	}
	else if (screen_to_display == SPLASH_SCREEN)
	{
		// display game 
		renderSplash();
	}
}

/**
*   @brief   Main menu
*   @details This function is used todisplay the main menu
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderMainMenu()
{
	// renders the main menu text
	renderer->renderText(
		"WELCOME TO PONG CAFE \n Press Esc to quit at any time.",
		150, 150, 1.2f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == ONE_PLAYER ? ">1 PLAYER" : "1 PLAYER",
		250, 250, 1.0f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == TWO_PLAYER ? ">2 PLAYER" : "2 PLAYER",
		250, 300, 1.0f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == SETTINGS ? ">SETTINGS" : "SETTINGS",
		250, 350, 1.0f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == HIGH_SCORES ? ">HIGH SCORES" : 
		"HIGH SCORES", 250, 400, 1.0f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == EXIT_GAME ? ">EXIT" : "EXIT",
		250, 450, 1.0f, ASGE::COLOURS::DARKORANGE);


	// renders an info tip about the game
	switch (tip)
	{
	case 0:
		renderer->renderText(
			"Longer Rallies equal higher scores in single player mode.",
			250, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 1:
		renderer->renderText(
			"A smaller paddle gets higher scores than a larger paddle in single player mode.",
			150, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 2:
		renderer->renderText(
			"A slower paddle gets higher scores than a faster paddle in single player mode.",
			150, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 3:
		renderer->renderText("Single player game only supports one ball.",
			350, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 4:
		renderer->renderText(
			"The harder the opponent the higher the score will be in single player mode.",
			150, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 5:
		renderer->renderText("High scores only apply to single player mode.",
			350, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 6:
		renderer->renderText(
			"The paddle deflects the ball at seven different angles dependant on where it hits.",
			100, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	case 7:
		renderer->renderText("The ball speeds up as a rally gets bigger.",
			350, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
		break;
	}



}

/**
*   @brief   Settings Menu
*   @details This function is used to display the settings menu
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderSettingsMenu()
{
	// re renders the main menu
	renderMainMenu();
	// renders the settings menu text
	renderer->renderText(settings_menu_option == BALL_SPEED_SETTING ?
		">BALL SPEED" : "BALL SPEED", 600, 270, 1.0, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("__________", 795, 262, 1.0, ASGE::COLOURS::DARKORANGE);
	switch (ball_speed_setting)
	{
	case VERY_SLOW:
		renderer->renderText(".", 780, 270, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case SLOW:
		renderer->renderText(".", 805, 270, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case NORMAL:
		renderer->renderText(".", 830, 270, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case FAST:
		renderer->renderText(".", 855, 270, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case VERY_FAST:
		renderer->renderText(".", 880, 270, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	default:
		break;
	}

	renderer->renderText(settings_menu_option == NUMBER_BALLS_SETTING ? 
		">NUMBER OF BALLS" : "NUMBER OF BALLS",	600, 320, 1.0,
		ASGE::COLOURS::DARKORANGE);
	renderer->renderText("__________", 795, 312, 1.0, ASGE::COLOURS::DARKORANGE);
	switch (number_of_balls)
	{
	case 1:
		renderer->renderText(".", 780, 320, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case 2:
		renderer->renderText(".", 830, 320, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case 3:
		renderer->renderText(".", 880, 320, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	default:
		break;
	}

	renderer->renderText(settings_menu_option == PADDLE_SIZE_SETTING ? 
		">PADDLE SIZE" : "PADDLE SIZE",	600, 370, 1.0,
		ASGE::COLOURS::DARKORANGE);
	renderer->renderText("__________", 795, 362, 1.0, ASGE::COLOURS::DARKORANGE);
	switch (paddle_size)
	{
	case VERY_SMALL:
		renderer->renderText(".", 780, 370, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case SMALL:
		renderer->renderText(".", 805, 370, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case STANDARD:
		renderer->renderText(".", 830, 370, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case LARGE:
		renderer->renderText(".", 855, 370, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case VERY_LARGE:
		renderer->renderText(".", 880, 370, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	default:
		break;
	}

	renderer->renderText(settings_menu_option == PADDLE_SPEED_SETTING ?
		">PADDLE SPEED" : "PADDLE SPEED", 600, 420, 1.0,
		ASGE::COLOURS::DARKORANGE);
	renderer->renderText("__________", 795, 412, 1.0, ASGE::COLOURS::DARKORANGE);
	switch (paddle_speed)
	{
	case VERY_SLOW:
		renderer->renderText(".", 780, 420, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case SLOW:
		renderer->renderText(".", 805, 420, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case NORMAL:
		renderer->renderText(".", 830, 420, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case FAST:
		renderer->renderText(".", 855, 420, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	case VERY_FAST:
		renderer->renderText(".", 880, 420, 4.0, ASGE::COLOURS::DARKORANGE);
		break;
	default:
		break;
	}

	renderer->renderText(settings_menu_option == SAVE_SETTINGS ? 
		">SAVE AND RETURN TO MAIN MENU" : "SAVE AND RETURN TO MAIN MENU",
		600, 470, 1.0, ASGE::COLOURS::DARKORANGE);


}

/**
*   @brief   In Game
*   @details This function is used to render the game objects 
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderInGame()
{
	if (!pause)
	{
	// render the background
	// to obtain a reference from a pointer, dereference it first
	renderer->renderSprite(*background);
	}
	// render the ball
	// to obtain a reference from a pointer, dereference it first
	renderer->renderSprite(*ball1.ball);
	if (number_of_balls > MIN_BALLS)
	{
		// render the second ball
		// to obtain a reference from a pointer, dereference it first
		renderer->renderSprite(*ball2.ball);
	}
	if (number_of_balls == MAX_BALLS)
	{
		// render the third ball
		// to obtain a reference from a pointer, dereference it first
		renderer->renderSprite(*ball3.ball);
	}
	// render the paddles
	// to obtain a reference from a pointer, dereference it first
	renderer->renderSprite(*player_1.paddle);
	renderer->renderSprite(*player_2.paddle);

	// creates a string with the score appended
	std::string player_1_score_str = std::to_string(player_1.getScore());

	// renders the string. a std string is not a c string so needs to be converted hence .c_str()
	renderer->renderText(player_1_score_str.c_str(), 40, 50, 2.0, ASGE::COLOURS::DARKORANGE);

	// creates a string with the score appended
	std::string player_2_score_str = std::to_string(player_2.getScore());

	// renders the string. a std string is not a c string so needs to be converted hence .c_str()
	renderer->renderText(player_2_score_str.c_str(), 1200, 50, 2.0, ASGE::COLOURS::DARKORANGE);

	if ((number_of_balls == 2 && ball1.getVertical() && ball2.getVertical()) ||
		(number_of_balls == 3 && ball1.getVertical() && ball2.getVertical() 
			&& ball3.getVertical()))
	{

		renderer->renderText("All balls currently travelling vertically"
			"\n Press SPACEBAR to serve the balls.",
			370, 600, 1.2f, ASGE::COLOURS::GHOSTWHITE);
	}
	else if (pause)
	{
		renderer->renderText("GAME PAUSED", 500, 300, 2.f, ASGE::COLOURS::DARKORANGE);
		renderer->renderText("Press P to continue.",
			500, 550, 1.2f, ASGE::COLOURS::GHOSTWHITE);
	}
}

/**
*   @brief   Opponent menu
*   @details This function is used to display the opponent selection menu
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderOpponentMenu()
{

	// render the background
	// to obtain a reference from a pointer, dereference it first
	renderer->renderSprite(*cafe);
	cafe->xPos(0);
	cafe->yPos(0);
	renderer->renderText("Choose your Opponent", 200, 100, 1.0, ASGE::COLOURS::DARKORANGE);
	// render the characters
	// to obtain a reference from a pointer, dereference it first
	renderer->renderSprite(*mavis);
	mavis->xPos(CHARACTER_WIDTH *.25f);
	mavis->yPos(WINDOW_HEIGHT - mavis->height());
	renderer->renderSprite(*nina);
	nina->xPos(CHARACTER_WIDTH * 1.65f);
	nina->yPos(WINDOW_HEIGHT - nina->height());
	renderer->renderSprite(*john);
	john->xPos(CHARACTER_WIDTH * 3.05f);
	john->yPos(WINDOW_HEIGHT - john->height());
	renderer->renderSprite(*paula);
	paula->xPos(CHARACTER_WIDTH * 4.45f);
	paula->yPos(WINDOW_HEIGHT - paula->height());
	renderer->renderSprite(*raul);
	raul->xPos(CHARACTER_WIDTH * 5.85f);
	raul->yPos(WINDOW_HEIGHT - raul->height());

	
	switch (opponent)
	{
	case 0:
		renderer->renderText("Mavis", 1100, 50, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderSprite(*mavis_head);
		mavis_head->xPos(1070);
		mavis_head->yPos(100);
		renderer->renderText("Difficulty: \nVery Easy", 1070, 250, 1.0, ASGE::COLOURS::DARKORANGE);
		break;
	case 1:
		renderer->renderText("Nina", 1100, 50, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderSprite(*nina_head);
		nina_head->xPos(1070);
		nina_head->yPos(100);
		renderer->renderText("Difficulty: \nEasy", 1070, 250, 1.0, ASGE::COLOURS::DARKORANGE);
		break;
	case 2:
		renderer->renderText("John", 1100, 50, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderSprite(*john_head);
		john_head->xPos(1070);
		john_head->yPos(100);
		renderer->renderText("Difficulty: \nAverage", 1070, 250, 1.0, ASGE::COLOURS::DARKORANGE);
		break;
	case 3:
		renderer->renderText("Paula", 1100, 50, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderSprite(*paula_head);
		paula_head->xPos(1070);
		paula_head->yPos(100);
		renderer->renderText("Difficulty: \nHard", 1070, 250, 1.0, ASGE::COLOURS::DARKORANGE);
		break;
	case 4:
		renderer->renderText("Raul", 1100, 50, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderSprite(*raul_head);
		raul_head->xPos(1070);
		raul_head->yPos(100);
		renderer->renderText("Difficulty: \nVery Hard", 1070, 250, 1.0, ASGE::COLOURS::DARKORANGE);
		break;

	default:
		break;
	}

}

/**
*   @brief   High scores
*   @details This function is used to display the high scores
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderHighScores()
{
	// re renders the main menu
	renderMainMenu();


	renderer->renderText("HIGH SCORES", 750, 150, 1.4f,
		ASGE::COLOURS::DARKORANGE);
	// renders the high scores
	int j = 0;
	for (int i = 200; i < 425; i = i + 25)
	{
		renderer->renderText(high_scores[j].initials.c_str(), 750, i, 1.0,
			ASGE::COLOURS::DARKORANGE);
		// creates a string with the score appended
		std::string score_str_1 = std::to_string(high_scores[j].score);
		renderer->renderText(score_str_1.c_str(), 850, i, 1.0,
			ASGE::COLOURS::DARKORANGE);
		j++;
	}
	renderer->renderText("Press Enter to return to Main Menu", 650, 475, 1.0, ASGE::COLOURS::DARKORANGE);
}

/**
*   @brief   New High score
*   @details This function is used to display the high score and update the 
players initials
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderNewHighScore()
{

	renderer->renderText("CONGRATULATIONS YOU SCORED A NEW HIGH SCORE", 
		350, 150, 1.2f, ASGE::COLOURS::DARKORANGE);
	// renders the settings menu text
	int j = 0;
	for (int i = 200; i < 425; i = i + 25)
	{
		renderer->renderText(high_score_idx_to_update == j ?
			new_initials.c_str() : high_scores[j].initials.c_str(),
			500, i, 1.0f, high_score_idx_to_update == j ?
			ASGE::COLOURS::GHOSTWHITE : ASGE::COLOURS::DARKORANGE);
		std::string score_str_1 = std::to_string(high_scores[j].score);
		renderer->renderText(score_str_1.c_str(), 600, i, 1.0, 
			high_score_idx_to_update == j ?
			ASGE::COLOURS::GHOSTWHITE : ASGE::COLOURS::DARKORANGE);
		j++;
	}



	renderer->renderText(
		"Use arrow keys to change initials and press Enter when finished",
		250, 475, 1.0f, ASGE::COLOURS::DARKORANGE);
}

/**
*   @brief   Game over
*   @details This function is used to display the game over screen
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderGameOver()
{
	if (one_player)
	{
		switch (opponent)
		{
		case MAVIS:
		{
			renderer->renderText(player_1.getScore() > player_2.getScore() ?
				"CONGRATULATIONS PLAYER 1 \n You beat MAVIS!" :
				"COMMISERATIONS. MAVIS WON! \n You are the loser!", 
				450, 150, 1.2f, ASGE::COLOURS::DARKORANGE);
			break;
		}
		case NINA:
		{
			renderer->renderText(player_1.getScore() > player_2.getScore() ?
				"CONGRATULATIONS PLAYER 1 \n You beat NINA!" :
				"COMMISERATIONS. NINA WON! \n You are the loser!",
				450, 150, 1.2f,	ASGE::COLOURS::DARKORANGE);
			break;
		}
		case JOHN:
		{
			renderer->renderText(player_1.getScore() > player_2.getScore() ?
				"CONGRATULATIONS PLAYER 1 \n You beat JOHN!" :
				"COMMISERATIONS. JOHN WON! \n You are the loser!",
				450, 150, 1.2f,	ASGE::COLOURS::DARKORANGE);
			break;
		}
		case PAULA:
		{
			renderer->renderText(player_1.getScore() > player_2.getScore() ?
				"CONGRATULATIONS PLAYER 1 \n You beat PAULA!" :
				"COMMISERATIONS. PAULA WON! \n You are the loser!", 
				450, 150, 1.2f, ASGE::COLOURS::DARKORANGE);
			break;
		}
		case RAUL:
		{
			renderer->renderText(player_1.getScore() > player_2.getScore() ?
				"CONGRATULATIONS PLAYER 1 \n You beat RAUL!" :
				"COMMISERATIONS. RAUL WON! \n You are the loser!",
				450, 150, 1.2f, ASGE::COLOURS::DARKORANGE);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else 
	{
	renderer->renderText(player_1.getScore() > player_2.getScore() ?
		"CONGRATULATIONS PLAYER 1 \n You are the winner!" :
		"CONGRATULATIONS PLAYER 2 \n You are the winner!", 
		450, 150, 1.2f, ASGE::COLOURS::DARKORANGE);
	}


	renderer->renderText("GAME OVER", 500, 300, 2.f, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("Press RETURN to continue.", 475, 475, 1.f,
		ASGE::COLOURS::DARKORANGE);
}

/**
*   @brief   Splash Screen
*   @details This function is used to render the splash Screen
*   @see     KeyEvent
*   @return  void
*/
void PongGame::renderSplash()
{

	// render the splash scren
	// to obtain a reference from a pointer, dereference it first
	renderer->renderSprite(*splash_screen);

}

/**
*   @brief   Update settings
*   @details This function is used to update the game settings when exiting the 
settings menu
*   @see     KeyEvent
*   @return  void
*/
void PongGame::updateSettings()
{
	// update the ball speed setting
	switch (ball_speed_setting)
	{
	case VERY_SLOW:
		ball1.setSpeedSetting(VERY_EASY_SPEED);
		ball2.setSpeedSetting(VERY_EASY_SPEED);
		ball3.setSpeedSetting(VERY_EASY_SPEED);
		break;
	case SLOW:
		ball1.setSpeedSetting(EASY_SPEED);
		ball2.setSpeedSetting(EASY_SPEED);
		ball3.setSpeedSetting(EASY_SPEED);
		break;
	case NORMAL:
		ball1.setSpeedSetting(NORMAL_SPEED);
		ball2.setSpeedSetting(NORMAL_SPEED);
		ball3.setSpeedSetting(NORMAL_SPEED);
		break;
	case FAST:
		ball1.setSpeedSetting(HARD_SPEED);
		ball2.setSpeedSetting(HARD_SPEED);
		ball3.setSpeedSetting(HARD_SPEED);
		break;
	case VERY_FAST:
		ball1.setSpeedSetting(VERY_HARD_SPEED);
		ball2.setSpeedSetting(VERY_HARD_SPEED);
		ball3.setSpeedSetting(VERY_HARD_SPEED);
		break;
	default:
		break;
	}

	// update the paddle size setting
	switch (paddle_size)
	{
	case VERY_SMALL:
		player_1.paddle->height(PADDLE_HEIGHT * VERY_HARD_PADDLE);
		player_2.paddle->height(PADDLE_HEIGHT * VERY_HARD_PADDLE);
		break;
	case SMALL:
		player_1.paddle->height(PADDLE_HEIGHT * HARD_PADDLE);
		player_2.paddle->height(PADDLE_HEIGHT * HARD_PADDLE);
		break;
	case STANDARD:
		player_1.paddle->height(PADDLE_HEIGHT * NORMAL_PADDLE);
		player_2.paddle->height(PADDLE_HEIGHT * NORMAL_PADDLE);
		break;
	case FAST:
		player_1.paddle->height(PADDLE_HEIGHT * EASY_PADDLE);
		player_2.paddle->height(PADDLE_HEIGHT * EASY_PADDLE);
		break;
	case VERY_FAST:
		player_1.paddle->height(PADDLE_HEIGHT * VERY_EASY_PADDLE);
		player_2.paddle->height(PADDLE_HEIGHT * VERY_EASY_PADDLE);
		break;
	default:
		break;
	}

	// update the paddle speed setting
	switch (paddle_speed)
	{
	case VERY_SLOW:
		player_1.setSpeedSetting(VERY_EASY_SPEED);
		player_2.setSpeedSetting(VERY_EASY_SPEED);
		break;
	case SLOW:
		player_1.setSpeedSetting(EASY_SPEED);
		player_2.setSpeedSetting(EASY_SPEED);
		break;
	case NORMAL:
		player_1.setSpeedSetting(NORMAL_SPEED);
		player_2.setSpeedSetting(NORMAL_SPEED);
		break;
	case FAST:
		player_1.setSpeedSetting(HARD_SPEED);
		player_2.setSpeedSetting(HARD_SPEED);
		break;
	case VERY_FAST:
		player_1.setSpeedSetting(VERY_HARD_SPEED);
		player_2.setSpeedSetting(VERY_HARD_SPEED);
		break;
	default:
		break;
	}
	reset();

}

/**
*   @brief   Setup Characters
*   @details This function is used to set the serve direction
of the ball i.e. spawn it.
*   @see     KeyEvent
*   @return  void
*/
void PongGame::setupCharacters()
{
	// set character one stats
	characters[MAVIS].speed_setting = VERY_EASY_SPEED;
	characters[MAVIS].paddle_size_setting = VERY_EASY_PADDLE;
	characters[MAVIS].reaction_time = 125.f;
	characters[MAVIS].error_rate = 8;
	characters[MAVIS].error_margin = (PADDLE_HEIGHT * 0.75f);
	characters[MAVIS].nerve = 8;

	// set character two stats
	characters[NINA].speed_setting = EASY_SPEED;
	characters[NINA].paddle_size_setting = EASY_PADDLE ;
	characters[NINA].reaction_time = 100.f;
	characters[NINA].error_rate = 6;
	characters[NINA].error_margin = (PADDLE_HEIGHT * 0.5f);
	characters[NINA].nerve = 6;

	// set character three stats
	characters[JOHN].speed_setting = NORMAL_SPEED;
	characters[JOHN].paddle_size_setting = NORMAL_PADDLE;
	characters[JOHN].reaction_time = 80.f;
	characters[JOHN].error_rate = 5;
	characters[JOHN].error_margin = (PADDLE_HEIGHT * 0.25f);
	characters[JOHN].nerve = 4;

	// set character four stats
	characters[PAULA].speed_setting = HARD_SPEED;
	characters[PAULA].paddle_size_setting = HARD_PADDLE;
	characters[PAULA].reaction_time = 40.f;
	characters[PAULA].error_rate = 2;
	characters[PAULA].error_margin = (PADDLE_HEIGHT *0.25f);
	characters[PAULA].nerve = 2;

	// set character five stats
	characters[RAUL].speed_setting = VERY_HARD_SPEED;
	characters[RAUL].paddle_size_setting = VERY_HARD_PADDLE;
	characters[RAUL].reaction_time = 10.f;
	characters[RAUL].error_rate = 1;
	characters[RAUL].error_margin = (PADDLE_HEIGHT * 0.25f);
	characters[RAUL].nerve = 1;
	saveCharacters();
}

/**
*   @brief   clear arrays
*   @details This function is used to initialise arrays.
*   @see     KeyEvent
*   @return  void
*/
void PongGame::clearArrays()
{
	for (int i = 0; i < NUM_CHARACTERS; i++)
	{
		characters[i].reaction_time = 0.f;
		characters[i].error_rate = 0;
		characters[i].error_margin = 0.f;
		characters[i].paddle_size_setting = 0.f;
		characters[i].speed_setting = 0.f;
		characters[i].nerve = 0;
	}

	for (int i = 0; i < NUM_HIGH_SCORES; i++)
	{
		high_scores[i].initials = "AAA";
		high_scores[i].score = 0;
	}
}

/**
*   @brief   Load files
*   @details This function is load the high scores and characters files
*   @see     KeyEvent
*   @return  void
*/
void PongGame::loadFiles()
{
	std::ifstream inFile_one;
	inFile_one.open("High_scores.txt");
	if (!inFile_one.fail())
	{
		for (int i = 0; i < NUM_HIGH_SCORES; i++)
		{
			std::string score;
			getline(inFile_one, high_scores[i].initials);
			getline(inFile_one, score);
			high_scores[i].score = atoi(score.c_str());
		}
		inFile_one.close();
	}
	std::ifstream inFile_two;
	inFile_two.open(".\\Resources\\Files\\Characters.txt");
	if (!inFile_two.fail())
	{
		for (int i = 0; i < NUM_CHARACTERS; i++)
		{
			std::string reaction_time;
			std::string error_margin;
			std::string error_rate;
			std::string paddle_size_setting;
			std::string speed_setting;
			std::string nerve;
			getline(inFile_two, reaction_time);
			characters[i].reaction_time = (float)atof(reaction_time.c_str());
			getline(inFile_two, error_margin);
			characters[i].error_margin = (float)atof(error_margin.c_str());
			getline(inFile_two, error_rate);
			characters[i].error_rate = atoi(error_rate.c_str());
			getline(inFile_two, paddle_size_setting);
			characters[i].paddle_size_setting = (float)atof(paddle_size_setting.c_str());
			getline(inFile_two, speed_setting);
			characters[i].speed_setting = (float)atof(speed_setting.c_str());
			getline(inFile_two, nerve);
			characters[i].nerve = atoi(nerve.c_str());
		}
		inFile_one.close();
	}
	else
	{
		setupCharacters();
	}
}

/**
*   @brief   Save files
*   @details This function is load the high scores and characters files
*   @see     KeyEvent
*   @return  void
*/
void PongGame::saveHighScores()
{

	std::ofstream outFile;
	outFile.open("High_scores.txt");
	if (!outFile.fail())
	{
		for (int i = 0; i < NUM_HIGH_SCORES; i++)
		{
			outFile << high_scores[i].initials << std::endl;
			outFile << high_scores[i].score << std::endl;
		}
		outFile.close();
	}

}

/**
*   @brief   Save files
*   @details This function is save the characters files
*   @see     KeyEvent
*   @return  void
*/
void PongGame::saveCharacters()
{

	std::ofstream outFile;
	outFile.open(".\\Resources\\Files\\Characters.txt");
	if (!outFile.fail())
	{
		for (int i = 0; i < NUM_CHARACTERS; i++)
		{
			outFile << characters[i].reaction_time << std::endl;
			outFile << characters[i].error_margin << std::endl;
			outFile << characters[i].error_rate << std::endl;
			outFile << characters[i].paddle_size_setting << std::endl;
			outFile << characters[i].speed_setting << std::endl;
			outFile << characters[i].nerve << std::endl;
		}
		outFile.close();
	}

}
