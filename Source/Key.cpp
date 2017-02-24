#include "Key.h"

std::string Key::getDescription() const
{
	return std::string("A Key!");
}

std::string Key::getRenderString() const
{
	return std::string("0------>");
}
