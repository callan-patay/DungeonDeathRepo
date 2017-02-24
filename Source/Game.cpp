#include "Game.h"
#include "Constants.h"
#include "Font.h"
#include "Player.h"
#include "Action.h"
#include "Dungeon.h"

#include <iostream>
#include <sstream>

#include <Engine/Input.h>
#include <Engine/Sprite.h>

#include <irrKlang.h>

//USER INTERFACE
#include "Panel.h"
#include "InputPanel.h"
#include "GamePanel.h"
#include "MapPanel.h"
#include "ViewportPanel.h"
#include "StatsPanel.h"
#include "EnemyType.h"
#include "Enemy.h"
#include "Room.h"
#include "Die.h"

DungeonDeathGame::DungeonDeathGame()
{
	player_one = nullptr;
}

DungeonDeathGame::~DungeonDeathGame()
{

	
	for (auto& font : Font::fonts)
	{
		delete font;
		font = nullptr;
	}

	audio_engine->stopAllSounds();




	


}

bool DungeonDeathGame::run()
{
	while (!renderer->exit() && game_state != GameState::EXIT)
	{
		if (game_state == GameState::MAIN_MENU)
		{
			updateMenu();
		}
		else if (game_state == GameState::PLAYING)
		{
			processGameActions();
			beginFrame();
			drawFrame();
			endFrame();
		}
		else if (game_state == GameState::GAME_OVER)
		{
			updateGameOver();
		}
	}

	return true;
}

bool DungeonDeathGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	dungeon = std::make_unique<Dungeon>();
	dungeon->create();



	die = std::make_unique<Die>(6);


	// create player
	player_one = std::make_unique<Player>(Player::PlayerClass::BARBARIAN);
	player_one->loadAvatar(renderer);
	player_one->setRoom(dungeon->getRoom(0));


	EnemyType::load();
	auto room = dungeon.get()->getRoom(0);
	generateEnemy(player_one->getRoom());
	//room->setEnemy(EnemyType::enemy_types[0].createEnemy());


	// load fonts
	Font::fonts[0] = new Font(renderer->loadFont("..\\..\\Resources\\Fonts\\DroidSansMono.ttf", 22), "default", 22);
	Font::fonts[1] = new Font(renderer ->loadFont("..\\..\\Resources\\Fonts\\comic.ttf", 32), "heading", 32);
	Font::fonts[2] = new Font(renderer ->loadFont("..\\..\\Resources\\Fonts\\comic.ttf", 16), "small", 16);
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	
	std::unique_ptr<GamePanel> game_panel;
	game_panel = std::make_unique <GamePanel>();
	game_panel->setPosX(1);
	game_panel->setPosY(70);
	game_panel->setHeight(35);
	game_panel->setWidth(35);
	game_panel->addOutput("Welcome to Meme Land");
	game_panel->addOutput(player_one->getRoom()->getDescription());


	std::unique_ptr<ViewportPanel> viewport_panel;
	viewport_panel = std::make_unique <ViewportPanel>();
	viewport_panel->setPosX((game_panel->getPosX() + (game_panel->getWidth() * BORDER_CELL_WIDTH) + PANEL_PADDING));
	viewport_panel->setPosY(340);
	viewport_panel->setWidth(20);
	viewport_panel->setHeight(20);
	viewport_panel->setObject(room->getEnemy());


	std::unique_ptr<StatsPanel> stats_panel;
	stats_panel = std::make_unique <StatsPanel>();
	stats_panel->setPosX(viewport_panel->getPosX());
	stats_panel->setPosY(game_panel->getPosY());
	stats_panel->setWidth(viewport_panel->getWidth()*1.8);
	stats_panel->setHeight(game_panel->getHeight() - viewport_panel->getHeight());
	stats_panel->init(player_one.get());


	std::unique_ptr<MapPanel> map_panel;
	map_panel = std::make_unique <MapPanel>();
	map_panel->setPosX(viewport_panel->getPosX() + (viewport_panel->getWidth() * BORDER_CELL_WIDTH));
	map_panel->setPosY(viewport_panel->getPosY());
	map_panel->setWidth(stats_panel->getWidth() - viewport_panel->getWidth());
	map_panel->setHeight(game_panel->getHeight() - stats_panel->getHeight());


	std::unique_ptr<InputPanel> input_panel;
	input_panel = std::make_unique <InputPanel>();
	input_panel->setPosX(0);
	input_panel->setPosY(700);


	panels[0] = std::move(game_panel);
	panels[1] = std::move(viewport_panel);
	panels[2] = std::move(stats_panel);
	panels[3] = std::move(map_panel);
	panels[4] = std::move(input_panel);

	initAudio();


	auto state_callback_id = this->inputs->addCallbackFnc(&DungeonDeathGame::stateInput, this);
	return true;
}

void DungeonDeathGame::drawFrame()
{
	renderer->setFont(Font::fonts[1]->id);
	renderer->renderText("Dungeon Death 2016", 0, 30, 1.0, ASGE::COLOURS::DARKORANGE);

	renderer->setFont(Font::fonts[0]->id);
	for (auto& panel : panels)
	{
		panel->render(renderer);
	}
}

bool DungeonDeathGame::initAudio()
{
	using namespace irrklang;
	audio_engine.reset(createIrrKlangDevice());

	if (!audio_engine)
	{
		return false;
	}

	return true;

}

void DungeonDeathGame::processGameActions()
{
	if (game_action == GameAction::ATTACK)
	{
		if (player_one->getRoom()->getEnemy())
		{
			if (!player_one->getRoom()->getEnemy()->isAlive())
			{
				printToGamePanel("Enemy is deaded f00l");
				game_action = GameAction::NONE;
				return;
			}

			Enemy* enemy = player_one->getRoom()->getEnemy();
			auto dmg = player_one->attack(player_one->getRoom()->getEnemy());
			audio_engine->play2D("..\\..\\Resources\\Audio\\dspunch.wav", false);
			printToGamePanel("Take that you vile fiend!");
			std::string dstr("You deal ");
			dstr += std::to_string(dmg);
			dstr += " damage";
			printToGamePanel(std::move(dstr));

			if( enemy->isAlive() )
			{
				auto dmg = enemy->attack(player_one.get());
				std::string dstr("You take ");
				dstr += std::to_string(dmg);
				dstr += " damage";
				printToGamePanel(std::move(dstr));
				printToGamePanel(enemy->getAttackString());
				if (player_one->getHealth() <= 0)
				{
					audio_engine->play2D("..\\..\\Resources\\Audio\\dspdiehi.wav", false);
					game_state = GameState::GAME_OVER;
				}
			}
			else
			{
				audio_engine->play2D("..\\..\\Resources\\Audio\\dskntdth.wav", false);
				printToGamePanel(enemy->getDeathString());
			}
		}
	}
	else if (game_action == GameAction::NORTH)
	{
		processMoveAction(GameAction::NORTH);
	}
	else if (game_action == GameAction::SOUTH)
	{
		processMoveAction(GameAction::SOUTH);
	}
	else if (game_action == GameAction::EAST)
	{
		processMoveAction(GameAction::EAST);
	}
	else if (game_action == GameAction::WEST)
	{
		processMoveAction(GameAction::WEST);
	}
	else if (game_action == GameAction::PRINT_INVENTORY)
	{
		printToGamePanel(player_one->getInventoryAsString());
	}
	else if (game_action == GameAction::PRINT_HELP)
	{
		processMoveAction(GameAction::PRINT_HELP);
	}
	if (game_action == GameAction::INVALID)
	{
		printToGamePanel("Unsupported Action");
	}
	game_action = GameAction::NONE;



}

bool DungeonDeathGame::movePlayer(Room* new_room)
{
	if (!new_room)
	{
		return false;
	}

	player_one->setRoom(new_room);
	printToGamePanel("\n");
	printToGamePanel("You enter the" + new_room->getName());
	printToGamePanel(std::string(new_room->getDescription()));

	auto viewport = static_cast<ViewportPanel*>(panels[1].get());
	viewport->setObject(player_one->getRoom()->getEnemy());

	return true;
}

void DungeonDeathGame::processMoveAction(GameAction action)
{
	if (action == GameAction::NORTH)
	{
		auto& new_room = player_one->getRoom()->getNorth().room;
		if(!movePlayer(new_room))
		{
			printToGamePanel("You cannot move north");
		}
		else
		{
			generateEnemy(player_one->getRoom());
		}
	}
	else if (action == GameAction::EAST)
	{
		auto& new_room = player_one->getRoom()->getEast().room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move east");
		}
		else
		{
			generateEnemy(player_one->getRoom());
		}
	}
	else if (action == GameAction::SOUTH)
	{
		auto& new_room = player_one->getRoom()->getSouth().room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move south");
		}
		else
		{
			generateEnemy(player_one->getRoom());
		}
	}
	else if (action == GameAction::WEST)
	{
		auto& new_room = player_one->getRoom()->getWest().room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move west");
		}
		else
		{
			generateEnemy(player_one->getRoom());
		}
	}
	else if (action == GameAction::PRINT_HELP)
	{
		for (const auto& verbs : help_strings)
		{
			std::stringstream ss;
			ss << verbs.first << ": \t" << verbs.second;
			printToGamePanel(ss.str());
		}
	}
}

void DungeonDeathGame::printToGamePanel(std::string && str)
{
	auto panel = static_cast<GamePanel*>(panels[0].get());
	if (panel)
	{
		panel->addOutput(std::move(str));
	}
}

void DungeonDeathGame::generateEnemy(Room * current_room)
{
	if (!current_room->getEnemy())
	{
		if (die->rollDie() == 6 || die->rollDie() == 3)
		{
				current_room->setEnemy(EnemyType::enemy_types[die->rollDie()].createEnemy());
		}
	}
}

void DungeonDeathGame::updateGame()
{


}

void DungeonDeathGame::updateMenu()
{
	beginFrame();
	renderer->setFont(Font::fonts[1]->id);
	renderer->renderText("Dungeon Death 2016", 0, 30, 1.0, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("Welcome. \nAre you man or mouse?", 200, 200, ASGE::COLOURS::STEELBLUE);
	endFrame();
}

void DungeonDeathGame::updateGameOver()
{
	beginFrame();
	renderer->setFont(Font::fonts[1]->id);
	renderer->renderText("Dungeon Death 2016", 0, 30, 1.0, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("YOU IZ DED", 200, 200, ASGE::COLOURS::STEELBLUE);
	endFrame();
}

void DungeonDeathGame::stateInput(int key, int action)
{
	if (action == ASGE::KEYS::KEY_PRESS && game_state == GameState::MAIN_MENU)
	{
		game_state = GameState::PLAYING;
		auto input_panel = static_cast<InputPanel*>(panels[4].get());

		game_callback_id = this->inputs->addCallbackFnc(&InputPanel::input, input_panel);

	}

	if (action == ASGE::KEYS::KEY_PRESS && game_state == GameState::GAME_OVER)
	{
		game_state = GameState::PLAYING;
		auto input_panel = static_cast<InputPanel*>(panels[4].get());

		game_callback_id = this->inputs->addCallbackFnc(&InputPanel::input, input_panel);
	}
}

