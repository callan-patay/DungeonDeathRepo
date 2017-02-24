#pragma once
#include <vector>
class Room;
class Dungeon
{
public:
	Dungeon()=default;
	~Dungeon()=default;

	void create();
	Room* getRoom(int idx);
private:
	std::vector<Room> rooms;
};

