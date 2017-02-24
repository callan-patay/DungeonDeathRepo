#include "Player.h"
#include "Key.h"
#include <Engine/Renderer.h>
#include <sstream>

Player::Player(PlayerClass c)
	: player_class(c)
{
	switch (player_class)
	{

	case PlayerClass::WIZARD:
	{
		strength = 5;
		dexterity = 10;
		intelligence = 15;
		luck = 10;
		mana = 100;
		break;
	} 

	case PlayerClass::BARBARIAN:
	{
		strength = 15;
		dexterity = 10;
		intelligence = 5;
		luck = 5;
		mana = 0;
		break;
	} 

	case PlayerClass::ROGUE:
	{
		strength = 10;
		dexterity = 15;
		intelligence = 10;
		luck = 10;
		mana = 0;
		break;
	}

	}

	inventory = std::make_unique<Inventory>();
	inventory->addItem(std::make_unique<Key>());
}

Player::~Player()
{

	delete avatar;

}

void Player::loadAvatar(std::shared_ptr<ASGE::Renderer> renderer)
{
	avatar = renderer->createSprite();
	avatar->loadTexture("..\\..\\Resources\\Textures\\avatar2");
	avatar->size[0] = 92;
	avatar->size[1] = 92;
}

ASGE::Sprite * Player::getAvatar()
{
	return avatar;
}

int Player::getXP() const
{
	return experience;
}

int Player::getStrength() const
{
	return strength;
}

int Player::getDexterity() const
{
	return dexterity;
}

int Player::getIntellect() const
{
	return intelligence;
}

int Player::getLuck() const
{
	return luck;
}

int Player::getMana() const
{
	return mana;
}


std::string Player::getManaAsString() const
{
	std::stringstream ss;
	for (int i = 0; i < mana; i += 5)
	{
		ss << '#';
	}

	return ss.str().c_str();
}

std::string Player::getDescription() const
{
	return std::string("A brave adventurer!");
}

std::string Player::getInventoryAsString() const
{
	return inventory->getRenderString();
}

Room * Player::getRoom() const
{
	return player_room;
}

void Player::setRoom(Room * rm)
{
	player_room = rm;
}

std::string Player::getRenderString() const
{
	return std::string();
}

std::string Player::getHealthAsString() const
{
	std::stringstream ss;
	for (int i = 0; i < health; i+=5)
	{
		ss << '#';
	}

	return ss.str().c_str();
}

