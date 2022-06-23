#pragma once

#include "SDL.h"

class Clear
{
public:
	Clear();
	~Clear();

	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
};
