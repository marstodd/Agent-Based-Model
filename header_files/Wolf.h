#pragma once
#include "RNG.h"
#include "Animal.h"

class Environment1;

class Wolf : public Animal
{
private:
	RNG random;
	Environment1* world;
	void Move();
public:
	void Act();
	void Die();
	Wolf(Environment1 *environment, int x, int y);
	~Wolf(void);
};

