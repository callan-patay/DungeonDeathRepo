#include "Dungeon.h"
#include "Room.h"
void Dungeon::create()
{
	rooms = { 5,  Room() };

	Room& room1 = rooms[0];
	Room& room2 = rooms[1];
	Room& room3 = rooms[2];
	Room& room4 = rooms[3];
	Room& room5 = rooms[4];
	

	room1.name = "Room1";
	room1.description = "A very grand room, with a large chandelier in the middle";
	room1.north.description = "The room north of you";
	room1.west.description = "The room to the west of you";
	room1.east.description = "The room to the east of you";
	room1.south.description = "The room to the south of you";
	room1.north.room = &room2;
	room1.west.room = &room5;
	room1.south.room = &room4;
	room1.east.room = &room3;


	room2.name = "Room2";
	room2.description = "A lifeless room";
	room2.south.description = "The room south of you";
	room2.south.room = &room1;

	room3.name = "Room3";
	room3.description = "A cold, dusty room";
	room3.west.description = "The room east of you";
	room3.west.room = &room1;

	room4.name = "Room4";
	room4.description = "A damp, creaky room";
	room4.north.description = "The room south of you";
	room4.north.room = &room1;

	room5.name = "Room5";
	room5.description = "A corrupt and haunting room";
	room5.east.description = "The room west of you";
	room5.east.room = &room1;
}

Room * Dungeon::getRoom(int idx)
{
	return &rooms[idx];
}
