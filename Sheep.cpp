#include "Environment1.h"
#include "Sheep.h"
#include <iostream>



Sheep::Sheep(Environment1* world, int x, int y)
{
	this->world = world;
	this->x = x;
	this->y = y;
	this->direction = (Direction)random.next(4 /*number of cardinal directions*/);
	this->energyThreshold = world->energyThreshold;
	this->energy = this->energyThreshold / 2;
	this->steps = 0;
	this->stepsThreshold = random.next(20,250);
	
}

void Sheep::Move()
{
	switch(this->direction)
	{
	case Direction::NORTH:
		y -= 1;
		break;
	case Direction::EAST:
		x += 1;
		break;
	case Direction::SOUTH:
		y += 1;
		break;
	case Direction::WEST:
		x -= 1;
		break;
	}


	if(x < 1) x = world->width - 2;
	if(y < 1) y = world->height - 2;
	if(x > world->width - 1) x = 1;
	if(y > world->height - 1) y = 1;

	this->steps++;
	if(this->steps % world->stepsPerEnergyLoss == 0)
	{
		this->energy -= world->energyLoss;
	}
	if(this->steps > this->stepsThreshold)
	{
		this->stepsThreshold = random.next(20,250);
		this->direction = (Direction)random.next(4);
		this->steps = 0;
	}
}

void Sheep::Die()
{

}

void Sheep::Act()
{
	this->Move();

	//if there is grass, eat up!
	if(world->GetWorldState(this->x,this->y) == STATE_GRASS)
	{
		this->energy += this->world->energyGainedFromGrass;
		this->world->DeleteGrass(this->x,this->y);
		this->world->totalGrassEaten++;
	}
	
	//sheep is dead
	if(this->energy <= 0)
	{
		this->world->DeleteSheep(this->x,this->y);
	}

	//make a new sheep
	if(this->energy >= this->energyThreshold)
	{
		this->energy = (int)this->energyThreshold / 2;
		this->world->SpawnSheep();
		this->world->totalSheepCreated++;
	}

}


Sheep::~Sheep(void)
{
}
