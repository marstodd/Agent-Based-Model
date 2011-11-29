#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDLGraphicsEngine.h"


#define STATE_COUNT 4
#define STATE_EMPTY 0
#define STATE_GRASS 1
#define STATE_SHEEP 2
#define STATE_WOLF 3

#define STATE_EMPTY_COLOR SDL_RGB(0,0,0)
#define STATE_GRASS_COLOR SDL_RGB(0,255,0)
#define STATE_SHEEP_COLOR SDL_RGB(255,255,255)
#define STATE_WOLF_COLOR  SDL_RGB(255,0,0)

#define DISPLAY_SIZE_X 500
#define DISPLAY_SIZE_Y 500
#define BOXES_IN_GRID_X 100
#define BOXES_IN_GRID_Y 100

class SDLDisplay
{
private:
	unsigned int colors[STATE_COUNT]; //pass in the state, it returns the color, remember to update constructor when STATE_COUNT is changed
	int grid[BOXES_IN_GRID_X][BOXES_IN_GRID_Y]; //0 = empty, 
	int displaySizeX;
	int displaySizeY;
	int boxSizeX;
	int boxSizeY;
	GraphicsEngine *display;
public:
	void Render();
	int GetBoxState(int x, int y);
	void ChangeBoxState(int x, int y,int newState);
	SDLDisplay(void);
	~SDLDisplay(void);
};

