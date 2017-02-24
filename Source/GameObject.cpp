#include "GameObject.h"
#include <string>
#include <Engine/Renderer.h>



std::string GameObject::getHealthAsString() const
{
	return std::string("100%");
}

std::string GameObject::getDescription() const
{
	return std::string("A Key!");
}
