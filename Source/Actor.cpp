#include "Actor.h"
#include "Die.h"

int Actor::getHealth() const
{
	return health;
}

int Actor::getArmour() const
{
	return armour_rating;
}

int Actor::getAttack() const
{
	return attack_rating;
}

bool Actor::isAlive() const
{
	if (health < 0)
	{
		return false;
	}

	return true;
}

std::string Actor::getHealthAsString() const
{
	return std::string("100%");
}

std::string Actor::getDeathString() const
{
	return std::string("ded");
}

int Actor::attack(Actor * obj) const
{
	Die die(attack_rating);
	auto dmg = die.rollDie();
	obj->defend(dmg);
	return dmg;
}

int Actor::defend(int dmg)
{
	dmg -= armour_rating;
	health -= dmg;
	return dmg;
}
