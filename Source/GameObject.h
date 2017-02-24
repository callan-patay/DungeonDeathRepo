#pragma once
#include <string>
class GameObject
{
public:

	virtual ~GameObject() = default;
	virtual std::string getRenderString() const = 0;
	virtual std::string getHealthAsString() const;
	virtual std::string getDescription() const;


protected:
	GameObject() = default;
};