#pragma once
//#include "Environment1.h"
enum Direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

class Animal
{
protected:
	//static int globalEnergyThreshold;
	int x;
	int y;
	int energy; //0 = death, energyThreshold = reproduce
	int energyThreshold; //reproduce when energy reaches or surpasses this number
	int health; //0 = death
	//double attackSpeed;
	//int attackDamage;
	//Direction direction;
	int steps;
	int stepsThreshold; //the amount of steps taken before a new direction is chosen
public:
	//static int globalEnergyThreshold;
	//static int energyGainedFromGrass;
	//static int energyGainedFromSheep;
	int GetX(){return x;}
	int GetY(){return y;}
	Direction direction;
	Animal(void);
	virtual ~Animal(void);
};

