#pragma once
#include <Engine/Sprite.h>
#include <string>
#include <memory>
#include "Actor.h"
#include "Room.h"
#include "Inventory.h"
namespace ASGE {
	class Renderer;
	class Sprite;
	class Room;
}

class Player: public Actor
{
public:



	enum class PlayerClass
	{
		BARBARIAN,
		ROGUE,
		WIZARD
	};


	Player(PlayerClass c);
	~Player();

	void loadAvatar(std::shared_ptr<ASGE::Renderer> renderer);
	ASGE::Sprite* getAvatar();


	int getXP() const;
	int getStrength() const;
	int getDexterity() const;
	int getIntellect() const;
	int getLuck() const;
	int getMana() const;


	virtual std::string getRenderString() const override;
	std::string getHealthAsString() const;
	std::string getManaAsString() const;
	std::string getDescription() const override;
	std::string getInventoryAsString() const;
	Room* getRoom() const;
	void setRoom(Room* rm);

private:
	PlayerClass player_class;
	Room* player_room;
	ASGE::Sprite* avatar = nullptr;
	std::unique_ptr<Inventory> inventory = nullptr;

	int experience = 0;
	int strength = 0;
	int dexterity = 0;
	int intelligence = 0;
	int luck = 0;
	int mana = 0;
};