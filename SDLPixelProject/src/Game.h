#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class AssetManager;
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

	static SDL_Renderer* pRenderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:

	int counter = 0;
	SDL_Window* pWindow;

};

