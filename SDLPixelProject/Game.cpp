#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::pRenderer = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<CollisionComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

auto& tile0(manager.AddEntity());
auto& tile1(manager.AddEntity());
auto& tile2(manager.AddEntity());

Game::Game()
{

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


	map = new Map();
	
	tile0.AddComponent<TileComponent>(200, 200, 16, 16, 0);
	tile1.AddComponent<TileComponent>(250, 250, 16, 16, 1);
	tile2.AddComponent<TileComponent>(150, 150, 16, 16, 2);
	tile2.AddComponent<CollisionComponent>("wall");

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("assets/player.png");
	player.AddComponent<KeyboardController>();
	player.AddComponent<CollisionComponent>("player");

	wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("assets/wall.png");
	wall.AddComponent<CollisionComponent>("wall");
}

void Game::EventHandler()
{
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
	manager.Refresh();
	manager.Update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.GetComponent<CollisionComponent>(), *cc);
		//if (Collision::AABB(player.GetComponent<CollisionComponent>(), *cc)) 
		//{
		//	player.GetComponent<TransformComponent>().velocity * -1;
		//}
	}
}

void Game::Render()
{
	SDL_RenderClear(pRenderer);

	//map->DrawMap();
	manager.Draw();

	SDL_RenderPresent(pRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	std::cout << "Game Quit!" << std::endl;
}
