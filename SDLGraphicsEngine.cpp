#include "SDLGraphicsEngine.h"

GraphicsEngine::~GraphicsEngine()
{
	
}

// Utility Functions

// SDL_RGB - combine separate RGB (0-255 each) values into single value for use with SDL
unsigned int SDL_RGB(unsigned int R, unsigned int G, unsigned int B)
{
	unsigned int color = R;
	color = (color << 8) | G;
	color = (color << 8) | B;

	return color;
}


// Graphics Engine Members

// Constructor - pass width and height in pixels of desired drawing window
// Initializes drawing surface to 0, or black.
GraphicsEngine::GraphicsEngine(int width, int height)
{
	int pixel, yofs, ofs;
	w = width;
	h = height;

	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);

	// Attempt to create a w x h window with 32bit pixels.
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

	// If we fail, return error.
	if ( screen == NULL ) 
	{
		fprintf(stderr, "Unable to set %d x %d video: %s\n", width, height, SDL_GetError());
		exit(1);
	}

	// Initialize Screen Buffer (local screen copy)
	localbuf = new unsigned int[w*h];

	for(pixel=0; pixel<w*h; pixel++)
		localbuf[pixel] = 0;

}

// Put Pixel - updates drawing surface at location p with combined RGB color
void GraphicsEngine::PutPixel(SDLPoint p, int color)
{
	//If pixel in window bounds
	if(p.x >= 0 && p.x < w && p.y >= 0 && p.y < h)
		localbuf[p.y*w+p.x] = color;
}

void GraphicsEngine::UpdateScreen()
{
	// Declare a couple of variables
	int x, y; // Pixel Location
	int yofs; // Y-offset used for compensating for screen pitch.
	int ofs; // Screen buffer pixel index
	int lofs; // Local Buffer pixel index

	// Draw to screen
	yofs = 0;
	lofs = 0;
	for (y = 0; y < h; y++)
	{
		for (x = 0, ofs = yofs; x < w; x++, ofs++, lofs++)
		{
			((unsigned int*)screen->pixels)[ofs] = localbuf[lofs];
		}
		yofs += screen->pitch / 4;
	}
}

void GraphicsEngine::Render()
{
	// Lock surface if needed
	if (SDL_MUSTLOCK(screen)) 
		if (SDL_LockSurface(screen) < 0) 
			return;

	UpdateScreen();

	// Unlock if needed
	if (SDL_MUSTLOCK(screen)) 
		SDL_UnlockSurface(screen);

	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, w, h);    
}

