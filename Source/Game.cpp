#include <string>
#include <Windows.h>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Game.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
and even seeding the random number generator.
*/
AngryBirdsGame::AngryBirdsGame()
{
	//std::srand(time(NULL));
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
AngryBirdsGame::~AngryBirdsGame()
{
	this->inputs->unregisterCallback(key_callback_id);
	this->inputs->unregisterCallback(mouse_callback_id);
	for (int i = 0; i < NUM_LEVELS; i++)
	{
		level_layer[i].~GameObject();
	}
	menu_layer.~GameObject();
	for (int i = 0; i < NUM_PROJECTILES; i++)
	{
		projectiles[i].~GameObject();
	}

}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The keyHandler and clickHandler
callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool AngryBirdsGame::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Angry Birds!");
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);

	mouse_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);

	clearArrays();
	loadFiles();



	gameplay_area.height = game_height * GAMEPLAY_AREA_HEIGHT;
	gameplay_area.length = game_height * GAMEPLAY_AREA_WIDTH;
	gameplay_area.y = game_height * .09f;
	gameplay_area.x = game_width - (gameplay_area.length * 0.5f);


	if (!loadBackgrounds())
	{
		return false;
	}
	if (!loadGameSprites())
	{
		return false;
	}
	return true;
}

/**
*   @brief   Loads the background and ui sprites
*   @details This function is used to load the sprites for the
background and ui gameobjects.
*   @return  bool
*/
bool AngryBirdsGame::loadBackgrounds()
{
	if (!splash.addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\splash_screen.png"))
	{
		return false;
	}
	if (!menu_layer.addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\menu.jpg"))
	{
		return false;
	}

	if (!level_layer[0].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\lvl1.png"))
	{
		return false;
	}

	if (!level_layer[1].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\lvl2.png"))
	{
		return false;
	}
	if (!level_layer[2].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\lvl3.png"))
	{
		return false;
	}
	if (!enemy_counter.addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\pig.png"))
	{
		return false;
	}

	ASGE::Sprite* splash_sprite = menu_layer.spriteComponent()->getSprite();
	splash_sprite->height(game_height * 0.5f);
	splash_sprite->width(game_width * 0.5f);
	splash_sprite->xPos((game_width * 0.5f) -
		(splash_sprite->width() * 0.5f));
	splash_sprite->yPos((game_height * 0.5f) -
		(splash_sprite->height() * 0.5f));

	ASGE::Sprite* menu_layer_sprite = menu_layer.spriteComponent()->getSprite();
	menu_layer_sprite->height(game_height);
	menu_layer_sprite->width(game_width * 0.7f);
	menu_layer_sprite->yPos(0.f);
	menu_layer_sprite->xPos(0.f);

	for (int i = 0; i < NUM_LEVELS; i++)
	{
		ASGE::Sprite* level_layer_sprite = level_layer[i].spriteComponent()->getSprite();
		level_layer_sprite->height(gameplay_area.height);
		level_layer_sprite->width(gameplay_area.length);
		level_layer_sprite->yPos(gameplay_area.y);
		level_layer_sprite->xPos(gameplay_area.x);
	}

	ASGE::Sprite* enemy_counter_sprite = enemy_counter.spriteComponent()->getSprite();
	enemy_counter_sprite->height(game_height * ENEMY_MEDIUM);
	enemy_counter_sprite->width(game_height * ENEMY_MEDIUM);
	enemy_counter_sprite->yPos(game_height * 0.05f);
	enemy_counter_sprite->xPos(gameplay_area.x);

	return true;
}


/**
*   @brief   Loads the gameplay sprites
*   @details This function is used to load the sprites for the
various gameplay objects.
*   @return  bool
*/
bool AngryBirdsGame::loadGameSprites()
{
	for (int i = 0; i < NUM_BLOCKS; i++)
	{

		if (i < 4)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Glass elements\\elementGlass012.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 8)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Glass elements\\elementGlass014.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_THIN);
			block_sprite->width(game_height * BLOCK_LONG);
		}
		else if (i < 14)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Glass elements\\elementGlass021.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_LONG);
			block_sprite->width(game_height * BLOCK_THIN);
		}
		else if (i < 18)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Glass elements\\elementGlass003.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 20)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Glass elements\\elementGlass005.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 28)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Wood elements\\elementWood010.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 40)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Wood elements\\elementWood019.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_THIN);
			block_sprite->width(game_height * BLOCK_LONG);
		}
		else if (i < 48)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Wood elements\\elementWood001.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_LONG);
			block_sprite->width(game_height * BLOCK_THIN);
		}
		else if (i < 56)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Wood elements\\elementWood003.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 60)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Wood elements\\elementWood005.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 64)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Stone elements\\elementStone012.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 68)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Stone elements\\elementStone013.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_THIN);
			block_sprite->width(game_height * BLOCK_LONG);
		}
		else if (i < 74)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Stone elements\\elementStone020.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_LONG);
			block_sprite->width(game_height * BLOCK_THIN);
		}
		else if (i < 78)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Stone elements\\elementStone002.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < 80)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Stone elements\\elementStone004.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		else if (i < NUM_BLOCKS)
		{
			if (!blocks[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\kenney_physicspack\\PNG\\Explosive elements\\elementExplosive011.png"))
			{
				return false;
			}
			ASGE::Sprite* block_sprite = blocks[i].spriteComponent()->getSprite();
			block_sprite->height(game_height * BLOCK_NORMAL);
			block_sprite->width(game_height * BLOCK_NORMAL);
		}
		enemies[i].setVisible(false);
	}

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (!enemies[i].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\pig.png"))
		{
			return false;
		}
		ASGE::Sprite* enemy_sprite = enemies[i].spriteComponent()->getSprite();
		if (i < 3)
		{
			enemy_sprite->height(game_height * ENEMY_MEDIUM);
			enemy_sprite->width(game_height * ENEMY_MEDIUM);
		}
		else if (i < 6)
		{
			enemy_sprite->height(game_height * ENEMY_LARGE);
			enemy_sprite->width(game_height * ENEMY_LARGE);
		}
		else
		{
			enemy_sprite->height(game_height * ENEMY_SMALL);
			enemy_sprite->width(game_height * ENEMY_SMALL);
		}
		enemies[i].setVisible(false);
	}

	for (int i = 0; i < NUM_PROJECTILES_SCATTER; i++)
	{
		if (!projectiles_scatter[i].addSpriteComponent(renderer.get(),
			".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\chick.png"))
		{
			return false;
		}
		projectiles_scatter[i].setVisible(false);
		ASGE::Sprite* projectile = projectiles_scatter[i].spriteComponent()->getSprite();
		projectile->height(gameplay_area.height * (PROJECTILE_SIZE * 0.5f));
		projectile->width(gameplay_area.length * (PROJECTILE_SIZE * 0.5f));
	}

	if (!bomb.addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\kenney_physicspack\\PNG\\Other\\coinDiamond.png"))
	{
		return false;
	}
	bomb.setVisible(false);
	ASGE::Sprite* bomb_sprite = bomb.spriteComponent()->getSprite();
	bomb_sprite->height(gameplay_area.height * BOMB_SIZE);
	bomb_sprite->width(gameplay_area.height * BOMB_SIZE);


	if (!projectiles[0].addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\duck.png"))
	{
		return false;
	}
	projectiles[0].setVisible(false);
	ASGE::Sprite* projectile = projectiles[0].spriteComponent()->getSprite();
	projectile->height(gameplay_area.height * PROJECTILE_SIZE);
	projectile->width(gameplay_area.length * PROJECTILE_SIZE);

	if (!projectiles[1].addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\owl.png"))
	{
		return false;
	}
	projectiles[1].setVisible(false);
	projectile = projectiles[1].spriteComponent()->getSprite();
	projectile->height(gameplay_area.height * PROJECTILE_SIZE);
	projectile->width(gameplay_area.length * PROJECTILE_SIZE);


	if (!projectiles[2].addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\penguin.png"))
	{
		return false;
	}
	projectiles[2].setVisible(false);
	projectile = projectiles[2].spriteComponent()->getSprite();
	projectile->height(gameplay_area.height * PROJECTILE_SIZE);
	projectile->width(gameplay_area.length * PROJECTILE_SIZE);

	if (!projectiles[3].addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\chick.png"))
	{
		return false;
	}
	projectiles[3].setVisible(false);
	projectile = projectiles[3].spriteComponent()->getSprite();
	projectile->height(gameplay_area.height * (PROJECTILE_SIZE * 0.5f));
	projectile->width(gameplay_area.length * (PROJECTILE_SIZE * 0.5f));


	if (!projectiles[4].addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\kenney_animalpackredux\\PNG\\round\\parrot.png"))
	{
		return false;
	}
	projectiles[4].setVisible(false);
	projectile = projectiles[4].spriteComponent()->getSprite();
	projectile->height(gameplay_area.height * PROJECTILE_SIZE);
	projectile->width(gameplay_area.length * PROJECTILE_SIZE);

	return true;
}

/**
*   @brief   Sets the game window resolution
*   @details This function is designed to create the window size, any
aspect ratio scaling factors and safe zones to ensure the
game frames when resolutions are changed in size.
*   @return  void
*/
void AngryBirdsGame::setupResolution()
{
	// how will you calculate the game's resolution?
	// will it scale correctly in full screen? what AR will you use?
	// how will the game be framed in native 16:9 resolutions?
	// here are some abritrary values for you to adjust as you see fit
	// https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/Scaling_and_MultiResolution_in_2D_Games.php
	game_height = GetSystemMetrics(SM_CYSCREEN);
	game_width = GetSystemMetrics(SM_CXSCREEN);
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
keyboard input. For this game, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}

	else if (key->key == ASGE::KEYS::KEY_ENTER &&
		key->action == ASGE::KEYS::KEY_PRESSED &&
		key->mods == 0x0004)
	{
		if (renderer->getWindowMode() == ASGE::Renderer::WindowMode::WINDOWED)
		{
			renderer->setWindowedMode(ASGE::Renderer::WindowMode::FULLSCREEN);
		}
		else
		{
			renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
		}
	}


	if (key->key == ASGE::KEYS::KEY_SPACE &&
		key->action == ASGE::KEYS::KEY_PRESSED
		&& game_state == IN_GAME)
	{


	}

	if (key->key == ASGE::KEYS::KEY_UP &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (game_state == MAIN_SCREEN)
		{
			menu_option--;
			if (menu_option < ONE_PLAYER)
			{
				menu_option = EXIT_GAME;
			}
		}
		else if (game_state == NEW_HIGH_SCORE)
		{
			new_initial += 1;
			if (new_initial > 'Z')
			{
				new_initial = 'A';
			}
			new_initials[initial] = new_initial;
		}
	}
	if (key->key == ASGE::KEYS::KEY_DOWN &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (game_state == MAIN_SCREEN)
		{
			menu_option++;
			if (menu_option > EXIT_GAME)
			{
				menu_option = ONE_PLAYER;
			}
		}
		else if (game_state == NEW_HIGH_SCORE)
		{
			new_initial -= 1;
			if (new_initial < 'A')
			{
				new_initial = 'Z';
			}
			new_initials[initial] = new_initial;
		}
	}

	if (key->key == ASGE::KEYS::KEY_ENTER &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{   //Main menu
		if (game_state == MAIN_SCREEN)
		{
			if (menu_option == ONE_PLAYER)
			{

				game_state = IN_GAME;
				new_game = true;
			}
			if (menu_option == HIGH_SCORES)
			{
				game_state = HIGH_SCORES_SCREEN;
			}
			if (menu_option == EXIT_GAME)
			{
				signalExit();
			}
		}
		else if (game_state == GAME_OVER_SCREEN)
		{
			if (updateHighScores())
			{
				game_state = NEW_HIGH_SCORE;
			}
			else
			{
				game_state = MAIN_SCREEN;
			}
		}
		else if (game_state == NEW_HIGH_SCORE)
		{
			high_scores[high_score_idx_to_update].initials = new_initials;
			saveHighScores();

			// reset menu variables
			initial = 0;
			new_initial = 'A';
			new_initials = "AAA";
			high_score_idx_to_update = 0;
			game_state = MAIN_SCREEN;
		}
		else if (game_state == HIGH_SCORES_SCREEN)
		{
			game_state = MAIN_SCREEN;
		}

	}

	if (key->key == ASGE::KEYS::KEY_LEFT &&
		key->action == ASGE::KEYS::KEY_PRESSED &&
		game_state == NEW_HIGH_SCORE)
	{
		initial -= 1;
		if (initial < 0)
		{
			initial = 2;
		}
		new_initial = new_initials[initial];
	}
	if (key->key == ASGE::KEYS::KEY_RIGHT &&
		key->action == ASGE::KEYS::KEY_PRESSED &&
		game_state == NEW_HIGH_SCORE)
	{
		initial += 1;
		if (initial > 2)
		{
			initial = 0;
		}
		new_initial = new_initials[initial];
	}
}

/**
*   @brief   Processes any click inputs
*   @details This function is added as a callback to handle the game's
mouse button input. For this game, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void AngryBirdsGame::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent*>(data.get());

	double x_pos, y_pos;
	inputs->getCursorPos(x_pos, y_pos);
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
current frame. Once the current frame is has finished
the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void AngryBirdsGame::update(const ASGE::GameTime& us)
{
	auto dt_sec = us.delta_time.count() / 1000.0;
	if (game_state == SPLASH_SCREEN)
	{

		ASGE::Sprite* splash_sprite = menu_layer.spriteComponent()->getSprite();
		splash_sprite->width((float)splash_sprite->width() +
			(((float)game_height * 0.5f) * 0.3f)	* (float)(us.delta_time.count() / 1000.f));
		splash_sprite->height((float)splash_sprite->height() +
			(((float)game_height * 0.5f) * 0.3f)	* (float)(us.delta_time.count() / 1000.f));
		splash_sprite->xPos(((float)game_width * 0.5f) -
			(splash_sprite->width() * 0.5f));
		splash_sprite->yPos(((float)game_height * 0.5f) -
			(splash_sprite->height() * 0.5f));
		if (splash_sprite->xPos() < 0.f)
		{
			game_state = MAIN_SCREEN;
		}
	}
	else if (game_state == IN_GAME)
	{
		if (new_game)
		{
			newGame();
		}
	}

	//make sure you use delta time in any movement calculations!


}

/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
Once the current frame is has finished the buffers are
swapped accordingly and the image shown.
*   @return  void
*/
void AngryBirdsGame::render(const ASGE::GameTime &)
{
	renderer->setFont(0);

	if (game_state == SPLASH_SCREEN)
	{
		renderSplash();
	}
	else if (game_state == MAIN_SCREEN)
	{
		renderMainMenu();
	}
	else if (game_state == IN_GAME)
	{
		renderInGame();
	}

	else if (game_state == GAME_OVER_SCREEN)
	{
		if (no_enemies_hit < NUM_ENEMIES)
		{
			renderGameOverL();
		}
		else
		{
			renderGameOverW();
		}
	}
	else if (game_state == NEW_HIGH_SCORE)
	{
		renderNewHighScore();
	}
	else if (game_state == HIGH_SCORES_SCREEN)
	{
		renderHighScores();
	}

}


/**
*   @brief   Splash Screen
*   @details This function is used to render the splash Screen
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderSplash()
{
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->renderSprite(*splash.spriteComponent()->getSprite());
}

/**
*   @brief   Main menu
*   @details This function is used todisplay the main menu
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderMainMenu()
{

	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::MIDNIGHTBLUE);
	renderer->renderSprite(*menu_layer.spriteComponent()->getSprite());
	// renders the main menu text
	renderer->renderText(
		"WELCOME TO ANGRY BIRDS \n Press Esc to quit at any time.", game_width * 0.2f,
		game_height * 0.15f, game_height * 0.002f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == 0 ? ">PLAY" : "PLAY", game_width * 0.2f,
		game_height * 0.3f, game_height * 0.002f, ASGE::COLOURS::WHITESMOKE);

	renderer->renderText(menu_option == 1 ? ">HIGH SCORES" : "HIGH SCORES", game_width * 0.2f,
		game_height * 0.4f, game_height * 0.002f, ASGE::COLOURS::WHITESMOKE);

	renderer->renderText(menu_option == 2 ? ">QUIT" : "QUIT", game_width * 0.2f,
		game_height * 0.5f, game_height * 0.002f, ASGE::COLOURS::WHITESMOKE);




}

/**
*   @brief   In Game Screen
*   @details This function is used todisplay the main menu
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderInGame()
{
	renderer->renderText("Score: ",
		(game_width * 0.60f), (game_height * 0.088f),
		game_height * 0.002f, ASGE::COLOURS::DARKORANGE);
	std::string score_string = std::to_string(current_score);
	renderer->renderText(score_string.c_str(),
		(game_width * 0.73f), (game_height * 0.088f),
		game_height * 0.002f, ASGE::COLOURS::DARKORANGE);

	std::string life_string = std::to_string(NUM_ENEMIES - no_enemies_hit);
	rect enemy_counter_sprite = enemy_counter.spriteComponent()->getBoundingBox();
	renderer->renderText(life_string.c_str(),
		(enemy_counter_sprite.x + (enemy_counter_sprite.length * 1.02f)),
		(enemy_counter_sprite.y + (enemy_counter_sprite.height * 0.95f)),
		game_height * 0.0025f, ASGE::COLOURS::DARKORANGE);


	if (bomb.getVisible() == true)
	{
		renderer->renderSprite(*bomb.spriteComponent()->getSprite());
	}
	for (int i = 0; i < NUM_PROJECTILES_SCATTER; i++)
	{
		if (projectiles_scatter[i].getVisible() == true)
		{
			renderer->renderSprite(*projectiles_scatter[i].spriteComponent()->getSprite());
		}

	}
	for (int i = 0; i < NUM_PROJECTILES; i++)
	{
		if (projectiles[i].getVisible() == true)
		{
			renderer->renderSprite(*projectiles[i].spriteComponent()->getSprite());
		}

	}

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		if (blocks[i].getVisible() == true)
		{
			renderer->renderSprite(*blocks[i].spriteComponent()->getSprite());
		}

	}
}

/**
*   @brief   Game Over loss
*   @details This function is used to display the game over screen
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderGameOverL()
{
	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	// renders the main menu text
	renderer->renderText(
		"GAME OVER out of lives \n Press Enter to return to main menu.",
		game_width * 0.25f, game_height * 0.2f, game_height * 0.002f, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("Final Score: ", (game_width * 0.3f), (game_height * 0.5f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);
	std::string score_string = std::to_string(current_score);
	renderer->renderText(score_string.c_str(),
		(game_width * 0.7f), (game_height * 0.50f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);

}

/**
*   @brief   Game Over Win
*   @details This function is used todisplay the the game over screen
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderGameOverW()
{
	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	// renders the main menu text
	renderer->renderText(
		"CONGRATULATIONS you cleared the game \n Press Enter to return to main menu.", game_width * 0.25f,
		game_height * 0.2f, game_height * 0.002f, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("Final Score: ", (game_width * 0.3f), (game_height * 0.5f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);
	std::string score_string = std::to_string(current_score);
	renderer->renderText(score_string.c_str(),
		(game_width * 0.7f), (game_height * 0.50f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);
}

/**
*   @brief   Update high scores
*   @details This function is used to check and update if single player high
score is higher than the current top ten
*   @see     KeyEvent
*   @return  bool
*/
bool AngryBirdsGame::updateHighScores()
{
	bool update_score = false;
	high_score_idx_to_update = 0;
	current_score = (current_score + (projectiles_left * 500));
	for (int i = 9; i > -1; i--)
	{
		if (current_score > high_scores[i].score)
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
		high_scores[high_score_idx_to_update].score = current_score;

	}
	current_score = 0;
	return update_score;
}

/**
*   @brief   High scores
*   @details This function is used to display the high scores
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderHighScores()
{
	// re renders the main menu
	renderMainMenu();


	renderer->renderText("HIGH SCORES", game_width * 0.68f, game_height * 0.15f, game_height * 0.002f,
		ASGE::COLOURS::DARKORANGE);
	// renders the high scores
	int j = 0;
	for (int i = game_height * 0.25f; i < game_height * 0.75f; i = i + game_height * 0.05f)
	{
		renderer->renderText(high_scores[j].initials.c_str(), game_width * 0.7f, i, game_height * 0.002f,
			ASGE::COLOURS::GHOSTWHITE);
		// creates a string with the score appended
		std::string score_str_1 = std::to_string(high_scores[j].score);
		renderer->renderText(score_str_1.c_str(), game_width * 0.75f, i, game_height * 0.002f,
			ASGE::COLOURS::GHOSTWHITE);
		j++;
	}
	renderer->renderText("Press Enter to return to Main Menu", game_width * 0.5f, game_height * 0.8f,
		game_height * 0.002f, ASGE::COLOURS::GHOSTWHITE);
}

/**
*   @brief   New High score
*   @details This function is used to display the high score and update the
players initials
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::renderNewHighScore()
{

	renderer->renderText("CONGRATULATIONS YOU SCORED A NEW HIGH SCORE",
		game_width * 0.1f, game_height * 0.15f, game_height * 0.003f, ASGE::COLOURS::DARKORANGE);
	int j = 0;
	for (int i = game_height * 0.25f; i < game_height * 0.75f; i = i + game_height * 0.05f)
	{
		renderer->renderText(high_score_idx_to_update == j ?
			new_initials.c_str() : high_scores[j].initials.c_str(),
			game_width * 0.45f, i, game_height * 0.002f, high_score_idx_to_update == j ?
			ASGE::COLOURS::GHOSTWHITE : ASGE::COLOURS::DARKORANGE);
		std::string score_str_1 = std::to_string(high_scores[j].score);
		renderer->renderText(score_str_1.c_str(), game_width * 0.5f, i, game_height * 0.002f,
			high_score_idx_to_update == j ?
			ASGE::COLOURS::GHOSTWHITE : ASGE::COLOURS::DARKORANGE);
		j++;
	}



	renderer->renderText(
		"Use arrow keys to change initials and press Enter when finished", game_width * 0.1f, game_height * 0.8f,
		game_height * 0.002f, ASGE::COLOURS::GHOSTWHITE);
}

/**
*   @brief   New Game
*   @details This function is used to reset a new game
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::newGame()
{



	// re-initialise bomb and scatter sprites
	resetBomb();
	resetProjectileScatter();
	// re-initialise game variables
	current_score = 0;
	new_game = false;
}



/**
*   @brief   Release Bomb
*   @details This function is used to release a bomb from the
provided projectiles co-ordinates
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::releaseBomb(rect projectile)
{
	ASGE::Sprite* bomb_sprite = bomb.spriteComponent()->getSprite();
	bomb_sprite->yPos(projectile.y);
	bomb_sprite->xPos(projectile.x + ((projectile.length * 0.5f) - (bomb_sprite->width() * 0.5f)));
	bomb.setVelocity(0.f, 0.5f);
	bomb.setVisible(true);
}

/**
*   @brief   Reset Bomb
*   @details This function is used to reset a bomb
position and velocity
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::resetBomb()
{
	// reset sprite position, velocity and visibility
	ASGE::Sprite* bomb_sprite = bomb.spriteComponent()->getSprite();
	bomb_sprite->yPos(0.f);
	bomb_sprite->xPos(0.f);
	bomb.setVisible(false);
	bomb.setVelocity(0.f, 0.f);
}

/**
*   @brief   Release Projectile Scatter
*   @details This function is used to reset a scatter shot's
position and velocity
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::releaseProjectileScatter(rect projectile, vector2 velocity)
{
	for (int i = 1; i < 2; i++)
	{
		// reset sprite position, velocity and visibility
		ASGE::Sprite* projectiles_scatter_sprite = projectiles_scatter[i].spriteComponent()->getSprite();
		projectiles_scatter_sprite->yPos(projectile.y);
		projectiles_scatter_sprite->xPos(projectile.x);
		projectiles_scatter[i].setVisible(true);
		if (i == 1)
		{
			projectiles_scatter[i].setVelocity(velocity.getX(), velocity.getY() - 0.02f);
		}
		else
		{
			projectiles_scatter[i].setVelocity(velocity.getX(), velocity.getY() + 0.02f);
		}
	}
}

/**
*   @brief   Reset Projectile Scatter
*   @details This function is used to reset a scatter shot's
position and velocity
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::resetProjectileScatter()
{
	for (int i = 1; i < 2; i++)
	{
		// reset sprite position, velocity and visibility
		ASGE::Sprite* projectiles_scatter_sprite = projectiles_scatter[i].spriteComponent()->getSprite();
		projectiles_scatter_sprite->yPos(0.f);
		projectiles_scatter_sprite->xPos(0.f);
		projectiles_scatter[i].setVisible(false);
		projectiles_scatter[i].setVelocity(0.f, 0.f);
	}
}


/**
*   @brief   Load files
*   @details This function is load the high scores and characters files
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::loadFiles()
{
	// load high scores
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
}

/**
*   @brief   Save files
*   @details This function is load the high scores and characters files
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::saveHighScores()
{
	// save high scores array to file
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
*   @brief   clear arrays
*   @details This function is used to initialise arrays.
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::clearArrays()
{
	for (int i = 0; i < NUM_HIGH_SCORES; i++)
	{
		high_scores[i].initials = "AAA";
		high_scores[i].score = 0;
	}
}