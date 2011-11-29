#pragma once
#include <vector>
#include "Animal.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Animal.h"
#include "SDLDisplay.h"
#include "RNG.h"
using std::vector;

struct grass
{
	int x;
	int y;
};


class Environment1
{
private:
	RNG random;
	int world[BOXES_IN_GRID_X][BOXES_IN_GRID_Y];
	SDLDisplay* display;
	vector<grass> grasses;
	vector<Sheep*> sheep;
	vector<Wolf*> wolves;
	//
	void SeedWorld(); //gets input from the user and initializes world accordingly
	void Render();
	void Update();
	void SetInitialState(int numToSpawn, int whichState);
	void SpawnGrass();
	void DisplayStats();

	int numberOfGrassToSpawn;
	int updatesPerGrassSpawn; //how many times the world updates between grass spawns
	//data that should be in animal, but couldn't get it to work
public:
	void Start();
	void SpawnSheep();
	void SpawnWolf();
	void DeleteWolf(int x, int y);
	void DeleteGrass(int x, int y);
	void DeleteSheep(int x, int y);
	int GetWorldState(int x, int y){return this->world[x][y];}
	int width; //world width
	int height; //world height
	int energyThreshold;
	int energyGainedFromGrass;
	int energyGainedFromSheep;
	int stepsPerEnergyLoss;
	int energyLoss; //energy lost from stepsPerEnergyLoss

	//statistics
	int totalSheepDead;
	int sheepKilledByWolves;
	int totalWolvesDead;
	int totalSheepEaten;
	int totalGrassEaten;
	int totalWolvesCreated;
	int totalSheepCreated;

	Environment1(void);
	~Environment1(void);
};

