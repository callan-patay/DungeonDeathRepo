#include "Room.h"


Room::~Room()
{
	delete mainEnemy;
	mainEnemy = nullptr;
}

std::string Room::getName()
{
	return name;
}

std::string Room::getDescription()
{
	return description;
}

const Room::RoomLink& Room::getNorth() const
{
	return north;
}

const Room::RoomLink& Room::getEast() const
{
	return east;
}
const Room::RoomLink& Room::getWest() const
{
	return west;
}
const Room::RoomLink& Room::getSouth() const
{
	return south;
}

void Room::setEnemy(Enemy* enemy)
{
	mainEnemy = enemy;
}

Enemy * Room::getEnemy()
{
	return mainEnemy;
}
