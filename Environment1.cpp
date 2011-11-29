#include "Environment1.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Environment1::Environment1(void)
{

	totalSheepDead = 0;
	sheepKilledByWolves = 0;
	totalWolvesDead = 0;
	totalGrassEaten = 0;
	totalWolvesCreated = 0;
	totalSheepCreated = 0;
	totalSheepEaten = 0;

	this->display = new SDLDisplay();
	this->width = BOXES_IN_GRID_X;
	this->height = BOXES_IN_GRID_Y;
	//initialize world to be empty
	for(int x = 0; x < this->width; x++)
	{
		for(int y = 0; y < this->height; y++)
		{
			this->world[x][y] = STATE_EMPTY;
		}
	}
	this->SeedWorld();
}

void Environment1::SeedWorld()
{
	int initGrassCount;
	int initSheepCount;
	int initWolfCount;
	cout << "Gathering user input to seed World." << endl;
	
	do
	{
		cin.clear();
		cin.sync();
		cout << "Number of updates between grass spawn (1 = none, 2 = every other update): ";
		cin >> this->updatesPerGrassSpawn;
	}while(cin.fail() || this->updatesPerGrassSpawn < 0);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Number of grass to spawn each time: ";
		cin >> this->numberOfGrassToSpawn;
	}while(cin.fail() || this->numberOfGrassToSpawn < 1);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Energy threshold: ";
		cin >> this->energyThreshold;
	}while(cin.fail() || this->energyThreshold < 0);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Energy gained from eating grass: ";
		cin >> this->energyGainedFromGrass;
	}while(cin.fail() || this->energyGainedFromGrass < 0);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Energy gained from eating sheep: ";
		cin >> this->energyGainedFromSheep;
	}while(cin.fail() || this->energyGainedFromSheep < 0);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Amount of steps taken to lose energy: ";
		cin >> this->stepsPerEnergyLoss;
	}while(cin.fail() || this->stepsPerEnergyLoss < 0);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Energy lost for each set of steps: ";
		cin >> this->energyLoss;
	}while(cin.fail() || this->energyLoss < 0);

	do
	{
		cin.clear();
		cin.sync();
		cout << "Initial amount of grass: ";
		cin >> initGrassCount;
	}while(cin.fail() || initGrassCount < 0 || initGrassCount > width * height /*not more grass than there is world*/);

	this->SetInitialState(initGrassCount,STATE_GRASS);
	this->Render();

	do
	{
		cin.clear();
		cin.sync();
		cout << "Initial amount of sheep: ";
		cin >> initSheepCount;
	}while(cin.fail() || initSheepCount < 0 || initSheepCount > width * height - initGrassCount /*not more sheep than there is world*/);

	this->SetInitialState(initSheepCount,STATE_SHEEP);
	this->Render();

	do
	{
		cin.clear();
		cin.sync();
		cout << "Initial amount of wolves: ";
		cin >> initWolfCount;
	}while(cin.fail() || initWolfCount < 0 || initSheepCount > width * height - initGrassCount - initSheepCount /*not more sheep than there is world*/);

	this->SetInitialState(initWolfCount,STATE_WOLF);
	this->Render();
}

void Environment1::Update()
{
	for(int x = 0; x < this->width; x++)
	{
		for(int y = 0; y < this->height; y++)
		{
			//erase the board
			world[x][y] = STATE_EMPTY;
		}
	}

	//print grass
	for(int i = 0; i < grasses.size(); i++)
	{
		world[grasses[i].x][grasses[i].y] = STATE_GRASS;
	}

	//print new sheep
	for(int i = 0; i < sheep.size(); i++)
	{
		int x, y;
		x = sheep[i]->GetX();
		y = sheep[i]->GetY();
		world[x][y] = STATE_SHEEP;
	}

	//print new wolves
	for(int i = 0; i < wolves.size(); i++)
	{
		int x, y;
		x = wolves[i]->GetX();
		y = wolves[i]->GetY();
		world[x][y] = STATE_WOLF;
	}


}

void Environment1::Render()
{
	for(int x = 0; x < this->width; x++)
	{
		for(int y = 0; y < this->height; y++)
		{
			this->display->ChangeBoxState(x,y,world[x][y]);
		}
	}
	this->display->Render();
}

void Environment1::SetInitialState(int numToSpawn, int whichState)
{
	for(int stateSpawned = 0; stateSpawned < numToSpawn; stateSpawned++)
	{
		int x = random.next(2,width-2);
		int y = random.next(2,height-2);
		if(world[x][y] == STATE_EMPTY)
		{
			world[x][y] = whichState;
			if(whichState == STATE_GRASS)
			{
				grass temp;
				temp.x = x;
				temp.y = y;
				grasses.push_back(temp);
			}
			if(whichState == STATE_SHEEP)
			{
				sheep.push_back(new Sheep(this,x,y));
			}
			if(whichState == STATE_WOLF)
			{
				wolves.push_back(new Wolf(this,x,y));
			}
		}
		else
		{
			//square not vacant, simply decrement grassSpawned and it will find another square
			stateSpawned--;
		}
	}
}

void Environment1::SpawnGrass()
{
	for(int i = 0; i < this->numberOfGrassToSpawn; i++)
	{
		int x = random.next(2, width - 2);
		int y = random.next(2, height-2);
		if(world[x][y] == STATE_EMPTY)
		{
			world[x][y] = STATE_GRASS;
			
			grass temp;
			temp.x = x;
			temp.y = y;
			grasses.push_back(temp);
			
		}
		else
		{
			//square not vacant, simply decrement grassSpawned and it will find another square
			i--;
		}
	}
}

void Environment1::SpawnSheep()
{
	bool sheepSpawned = false;
	while(sheepSpawned == false) //loop until sheep is spawned
	{
		int x = random.next(2, width - 2);
		int y = random.next(2,height-2);
		if(world[x][y] == STATE_EMPTY)
		{
			world[x][y] = STATE_SHEEP;
			sheep.push_back(new Sheep(this,x,y));
			sheepSpawned = true;
			this->totalSheepCreated++;
		}	
	}
}

void Environment1::SpawnWolf()
{
	bool wolfSpawned = false;
	while(wolfSpawned == false) //loop until sheep is spawned
	{
		int x = random.next(2, width - 2);
		int y = random.next(2,height-2);
		if(world[x][y] == STATE_EMPTY)
		{
			world[x][y] = STATE_WOLF;
			wolves.push_back(new Wolf(this,x,y));
			wolfSpawned = true;
			this->totalWolvesCreated++;
		}	
	}
}

void Environment1::DisplayStats()
{
	cout << "---Current Statistics---" << endl;
	cout << "-Sheep-"
		<< "\nTotal grass eaten: " << this->totalGrassEaten
		<< "\nTotal sheep created: " << this->totalSheepCreated
		<< "\nTotal sheep dead: " << this->totalSheepDead
		<< "\n-Wolves-"
		<< "\nTotal sheep killed: " << this->totalSheepEaten
		<< "\nTotal wolves created: " << this->totalWolvesCreated
		<< "\nTotal wolves dead: " << this->totalWolvesDead << endl;
}

void Environment1::Start()
{
	int grassTrack = 0; //keeps track of when to spawn grass
	int statDisplay = 0; //display stats every 20 steps
	cout << "Starting in two seconds..." << endl;
	SDL_Delay(2000);
	while(1)
	{
		grassTrack ++;
		statDisplay++;
		for(int i = 0; i < sheep.size(); i++)
		{
			sheep[i]->Act();
			//cout << i << " - (" << sheep[i]->GetX() << ", " << sheep[i]->GetY() << ")" << "dir = " << sheep[i]->direction << endl;
		}
		this->Update();
		for(int i = 0; i < wolves.size(); i++)
		{
			wolves[i]->Act();
		}
		if(grassTrack >= this->updatesPerGrassSpawn)
		{
			this->SpawnGrass();
			grassTrack = 0;
		}
		if(statDisplay >= 20)
		{
			system("CLS");
			this->DisplayStats();
			statDisplay = 0;
		}
		this->Update();
		this->Render();
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
					break;
				case SDL_KEYUP:
					// If escape is pressed, return 
					if (event.key.keysym.sym == SDLK_ESCAPE)
						return;
					break;
				case SDL_QUIT:
					return;
			}
		}
	}
}

void Environment1::DeleteGrass(int x, int y)
{
	//find the grass being eaten
	for(int i = 0; i < grasses.size(); i++)
	{
		if(grasses[i].x == x && grasses[i].y == y)
		{
			grasses.erase(grasses.begin() + i);
		}
	}
}

void Environment1::DeleteSheep(int x, int y)
{
	//find the sheep that is dying or being eaten
	//cout << "Entered Coords: " << x << ", " << y << endl;
	for(int i = 0; i < sheep.size(); i++)
	{
		//cout << "Entered Coords: " << x << ", " << y << endl;
		//cout << "This sheep is at (" << sheep[i]->GetX() << ", " << sheep[i]->GetY() << ")" << endl;
		if(sheep[i]->GetX() == x && sheep[i]->GetY() == y)
		{
			sheep.erase(sheep.begin() + i);
			this->totalSheepDead++;
		}
	}
	//SDL_Delay(5000);
}

void Environment1::DeleteWolf(int x, int y)
{
	//find the sheep that is dying or being eaten
	for(int i = 0; i < wolves.size(); i++)
	{
		if(wolves[i]->GetX() == x && wolves[i]->GetY() == y)
		{
			wolves.erase(wolves.begin() + i);
			this->totalWolvesDead++;
		}
	}
}


Environment1::~Environment1(void)
{
}
