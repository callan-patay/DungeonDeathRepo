#include "ViewportPanel.h"
#include <Engine/Renderer.h>
#include <string>

void ViewportPanel::setObject(Actor * obj)
{
	object = obj;
}


void ViewportPanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	UIPanel::render(renderer);
	if (object)
	{
		auto obj_x = getPosX() + 20;
		auto obj_y = getPosY() + 2;
		auto str = object->getRenderString();
		str.append(object->getHealthAsString());
		str.append("\n\n");
		str.append(object->getDescription());
		renderer->renderText(str.c_str(), obj_x, obj_y,
			ASGE::COLOURS::TOMATO);
	}

}


