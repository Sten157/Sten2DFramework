#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

Map* map;

SDL_Renderer* Game::pRenderer = nullptr;

Manager manager;
auto& newPlayer(manager.AddEntity());

Game::Game()
{
	//https://www.youtube.com/watch?v=jq3Bg7XXjWw&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=10
	// 2:47
}

Game::~Game()
{

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;

	if (fullScreen == true)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		std::cout << "Subsystems Initialized!" << std::endl;

		pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (pWindow) 
		{
			std::cout << "Window Created!" << std::endl;
		}
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
		if (pRenderer) 
		{
			SDL_SetRenderDrawColor(pRenderer, 125, 125, 125, 255);
			std::cout << "Renderer Created!" << std::endl;
		}
		
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new GameObject("assets/player.png", 0, 0);
	enemy = new GameObject("assets/enemy.png", 50, 0);
	map = new Map();
	
	newPlayer.AddComponent<PositionComponent>();
	newPlayer.GetComponent<PositionComponent>().setPos(500,500);
}

void Game::EventHandler()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;

		default:
			break;
	}
}

void Game::Update()
{
	counter++;
	player->Update();
	enemy->Update();
	manager.Update();
	std::cout << " " << newPlayer.GetComponent<PositionComponent>().x() << "," << newPlayer.GetComponent<PositionComponent>().y() << std::endl;
	std::cout << counter << "\r";
}

void Game::Render()
{
	SDL_RenderClear(pRenderer);

	map->DrawMap();
	player->Render();
	enemy->Render();

	SDL_RenderPresent(pRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	std::cout << "Game Quit!" << std::endl;
}
