#pragma once
#include <string>
#include <atomic>

enum class Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

//namespace ActionStringLiterals
//{
//	const std::string attack = "ATTACK";
//}

extern std::atomic<Direction> direction;