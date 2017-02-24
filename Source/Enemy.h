#pragma once
#include <memory>
#include "Actor.h"
class EnemyType;
class Player;
class Enemy : public Actor
{
public:
	friend class EnemyType;
	~Enemy() = default;
	int getHealth() const;
	virtual std::string getHealthAsString() const override;
	virtual std::string getRenderString() const override;
	virtual std::string getDescription() const override;
	virtual std::string getDeathString() const override;
	virtual std::string getAttackString() const;
private:
	Enemy(EnemyType&);
	EnemyType& type;
};