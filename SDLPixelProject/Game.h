#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Game
{
public: 

	Game();
	~Game();
	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	void EventHandler();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };

	static SDL_Renderer* pRenderer;

private:

	int counter = 0;
	bool isRunning;
	SDL_Window* pWindow;

};

