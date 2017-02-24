#pragma once
#include <string>
#include <map>
#include <atomic>

enum class GameAction
{
	INVALID = -1,
	NONE	= 0,
	ATTACK,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	PRINT_INVENTORY,
	PRINT_HELP
};

namespace ActionStringLiterals
{
	const std::string attack = "ATTACK";
	const std::string inventory = "INVENTORY";
	const std::string north = "NORTH";
	const std::string south = "SOUTH";
	const std::string east = "EAST";
	const std::string west = "WEST";
	const std::string help = "HELP";
}


const std::map<const std::string, const std::string>
help_strings
{
	{ ActionStringLiterals::attack, "Attacks the enemy"},
	{ ActionStringLiterals::north, "Moves north" },
	{ ActionStringLiterals::east, "Moves east" },
	{ ActionStringLiterals::south, "Moves south" },
	{ ActionStringLiterals::west, "Moves west" },
	{ ActionStringLiterals::inventory, "Prints Inventory" }
};

const std::map<const std::string, const GameAction> actions
{
	{ ActionStringLiterals::attack, GameAction::ATTACK },
	{ ActionStringLiterals::north, GameAction::NORTH },
	{ ActionStringLiterals::east, GameAction::EAST },
	{ ActionStringLiterals::south, GameAction::SOUTH },
	{ ActionStringLiterals::west, GameAction::WEST },
	{ ActionStringLiterals::inventory, GameAction::PRINT_INVENTORY },
	{ ActionStringLiterals::help, GameAction::PRINT_HELP }
};



extern std::atomic<GameAction> game_action;