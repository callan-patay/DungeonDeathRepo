#pragma once
#include <string>

class Enemy;


class Room
{
	friend class Dungeon;
	struct RoomLink
	{
		Room* room = nullptr;
		std::string description = "Dead End";
	};

public:
	Room() = default;
	~Room();

	std::string getName();
	std::string getDescription();

	const Room::RoomLink & getNorth() const;

	const Room::RoomLink & getEast() const;

	const Room::RoomLink & getWest() const;

	const Room::RoomLink & getSouth() const;

	void setEnemy(Enemy* enemy);
	Enemy* getEnemy();



private:
	std::string name;
	std::string description;
	Enemy* mainEnemy = nullptr;
	RoomLink north;
	RoomLink east;
	RoomLink west;
	RoomLink south;
};

