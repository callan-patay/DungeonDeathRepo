#include "InputPanel.h"
#include <Engine/Keys.h>
#include <Engine/Renderer.h>
#include <sstream>
#include <algorithm>
#include "Action.h"

void InputPanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	std::stringstream ss;
	ss << "> " << str;

	renderer->setFont(0);
	renderer->renderText(ss.str().c_str(), getPosX(), getPosY(), 1.0, ASGE::COLOURS::FORESTGREEN);
}

void InputPanel::input(int key, int action)
{
	if (action == ASGE::KEYS::KEY_PRESS)
	{
		if (key == ASGE::KEYS::KEY_DELETE ||
			key == ASGE::KEYS::KEY_BACKSPACE && 
			str.size() )
		{
			str.pop_back();
		}
		else if (key == ASGE::KEYS::KEY_ENTER)
		{
			this->action(str);
			str.clear();
		}
		else
		{
			str += key;
			return;
		}
	}
}

void InputPanel::action(std::string & input)
{
	//if (input == ActionStringLiterals::attack)
	//{
	//	game_action = GameAction::ATTACK;
	//}
	//else if (input == ActionStringLiterals::north)
	//{
	//	game_action = GameAction::NORTH;
	//}
	//else if (input == ActionStringLiterals::south)
	//{
	//	game_action = GameAction::SOUTH;
	//}
	//else if (input == ActionStringLiterals::east)
	//{
	//	game_action = GameAction::EAST;
	//}
	//else if (input == ActionStringLiterals::west)
	//{
	//	game_action = GameAction::WEST;
	//}
	//else if (input == ActionStringLiterals::inventory)
	//{
	//	game_action = GameAction::PRINT_INVENTORY;
	//}
	//else if (input == ActionStringLiterals::help)
	//{
	//	game_action = GameAction::PRINT_HELP;
	//}
	//else
	//{
	//	game_action = GameAction::INVALID;
	//}

	const auto& term = actions.find(input);
	if (term != actions.end())
	{
		game_action = term->second;
	}
	else
	{
		game_action = GameAction::INVALID;
	}

}
