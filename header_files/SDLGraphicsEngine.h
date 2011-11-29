#ifndef SDLGRAPHICS_H
#define SDLGRAPHICS_H

#include "SDL.h"

unsigned int SDL_RGB(unsigned int R, unsigned int G, unsigned int B);

struct SDLPoint
{
	unsigned int x;
	unsigned int y;
};

class GraphicsEngine
{
public:
	GraphicsEngine(int width, int height);
	~GraphicsEngine();
	
	void PutPixel(SDLPoint p, int color);

	void Render();

private:
	void UpdateScreen();
	
	SDL_Surface *screen;
	unsigned int *localbuf;
	
	unsigned int w;
	unsigned int h;
};



#endif