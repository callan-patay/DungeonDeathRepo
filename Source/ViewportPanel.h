#pragma once
#include "Panel.h"
#include "Actor.h"
#include <memory>


class Actor;
namespace ASGE
{
	class Renderer;
}

class ViewportPanel: public UIPanel
{

public:
	void render(std::shared_ptr<ASGE::Renderer> renderer) override;
	void ViewportPanel::setObject(Actor* obj);

private:
	//Actor* object = nullptr;
	Actor* object = nullptr;
};