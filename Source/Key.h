#pragma once
#include "Item.h"


class Key : public Item
{
public:
	Key() = default;
	virtual ~Key() = default;

	std::string getDescription() const override;
	std::string getRenderString() const override;

protected:
};