#include "SDLDisplay.h"

SDLDisplay::SDLDisplay(void)
{
	this->displaySizeX = DISPLAY_SIZE_X;
	this->displaySizeY = DISPLAY_SIZE_Y;
	this->display = new GraphicsEngine(this->displaySizeX, this->displaySizeY);
	this->boxSizeX = DISPLAY_SIZE_X / BOXES_IN_GRID_X;
	this->boxSizeY = DISPLAY_SIZE_Y / BOXES_IN_GRID_Y;

	this->colors[STATE_EMPTY] = STATE_EMPTY_COLOR;
	this->colors[STATE_GRASS] = STATE_GRASS_COLOR;
	this->colors[STATE_SHEEP] = STATE_SHEEP_COLOR;
	this->colors[STATE_WOLF]  = STATE_WOLF_COLOR;

	//initializes grid to the default state of 0
	for(int x = 0; x < BOXES_IN_GRID_X; x++)
	{
		for(int y = 0; y < BOXES_IN_GRID_Y; y++)
		{
			grid[x][y] = STATE_EMPTY;
			this->ChangeBoxState(x,y,STATE_EMPTY);
		}
	}

	SDLPoint p;

	p.x = 0;
	p.y = 0;

	//sets the color of the display to STATE_OFF_COLOR
	//for(int x = 0; x < DISPLAY_SIZE_X; x++)
	//{
	//	p.x = x;
	//	for(int y = 0; y < DISPLAY_SIZE_Y; y++)
	//	{
	//		p.y = y;
	//		this->display->PutPixel(p,this->colors[this->GetBoxState(x,y)]);
	//	}
	//}

	this->Render();
}

int SDLDisplay::GetBoxState(int x, int y)
{
	return this->grid[x][y];
}

void SDLDisplay::ChangeBoxState(int x, int y, int newState)
{
	//the amount of shifting required to reach the desired box
	int shiftX = x * this->boxSizeX;
	int shiftY = y * this->boxSizeY;
	SDLPoint p;

	grid[x][y] = newState;
	//update the display to show the new color
	for(int iteratorX = 0; iteratorX < boxSizeX; iteratorX++)
	{
		p.x = (shiftX + iteratorX);
		for(int iteratorY = 0; iteratorY < boxSizeY; iteratorY++)
		{
			p.y = (shiftY + iteratorY);
			this->display->PutPixel(p,this->colors[newState]);
		}
	}
	
}

void SDLDisplay::Render()
{
	this->display->Render();
}

SDLDisplay::~SDLDisplay(void)
{
	delete this->display;
}
