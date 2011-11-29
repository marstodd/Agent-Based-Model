#pragma once
#include "RNG.h"
#include "Animal.h"

class Environment1;

class Sheep : public Animal
{
private:
	RNG random;
	Environment1* world;
	void Move();
public:
	void Act();
	void Die();
	Sheep(Environment1 *environment, int x, int y);
	~Sheep(void);
};

