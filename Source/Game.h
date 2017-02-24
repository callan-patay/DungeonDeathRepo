#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Keys.h>
#include "Action.h"

#include <memory>
class Player;
class UIPanel;
class Dungeon;
class Room;
class Enemy;
class Die;
struct Font;

namespace irrklang
{
	class ISoundEngine;
}


class DungeonDeathGame:
	public ASGE::OGLGame
{
public:
	enum class GameState
	{
		MAIN_MENU = 0,
		PLAYING = 1,
		GAME_OVER = 2,
		EXIT = 3
	};


	DungeonDeathGame();
	~DungeonDeathGame();

	// Inherited via Game
	virtual bool run() override;

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();
	bool initAudio();
	void processGameActions();
	bool movePlayer(Room * new_room);
	void processMoveAction(GameAction action);
	void printToGamePanel(std::string && str);
	void generateEnemy(Room* current_room);

	void updateGame();
	void updateMenu();
	void updateGameOver();

	void stateInput(int key, int action);

private:
	int state_called_id = -1;
	int game_callback_id = -1;


	GameState game_state = GameState::MAIN_MENU;
	std::unique_ptr<Die> die = nullptr;
	std::unique_ptr<UIPanel> panels[5];
	std::unique_ptr<Player> player_one = nullptr;
	std::unique_ptr<irrklang::ISoundEngine> audio_engine = nullptr;
	std::unique_ptr<Dungeon> dungeon = nullptr;
};

