#pragma once
#include <vector>
#include <memory>
class Item;

class Inventory
{
public:
	~Inventory() = default;
	Inventory() = default;
	void addItem(std::unique_ptr<Item>&& obj);
	std::string getRenderString();

private:
	std::vector<std::unique_ptr<Item>> objects;
	std::string items;
};