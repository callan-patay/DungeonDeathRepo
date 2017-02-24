#include "Inventory.h"
#include "Item.h"
void Inventory::addItem(std::unique_ptr<Item>&& obj)
{
	objects.push_back(std::move(obj));
}

std::string Inventory::getRenderString() 
{

	if (objects.size() != 0)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			items += objects[i]->getDescription();
		}
		return items;
	}
	return std::string("No items in inventory!");
}
