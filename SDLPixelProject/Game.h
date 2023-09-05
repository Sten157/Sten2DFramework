#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class CollisionComponent;

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

	static void AddTile(int srcX, int srcY, int xPos, int yPos);
	static SDL_Renderer* pRenderer;
	static SDL_Event event;
	static std::vector<CollisionComponent*> colliders;
	static bool isRunning;

private:

	int counter = 0;
	SDL_Window* pWindow;

};

