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

enum groupLabels : std::size_t 
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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

	Map::LoadMap("assets/map.c", 32, 32);

	player.AddComponent<TransformComponent>(2);
	player.GetComponent<TransformComponent>().height = 16;
	player.GetComponent<TransformComponent>().width = 16;
	player.AddComponent<SpriteComponent>("assets/player_anim.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<CollisionComponent>("player");
	player.addGroup(groupPlayers);

	//wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	//wall.AddComponent<SpriteComponent>("assets/wall.png");
	//wall.AddComponent<CollisionComponent>("wall");
	//wall.addGroup(groupMap);
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
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::Render()
{
	SDL_RenderClear(pRenderer);

	for (auto& t : tiles)
	{
		t->Draw();
	}

	for (auto& p : players)
	{
		p->Draw();
	}

	for (auto& e : enemies)
	{
		e->Draw();
	}

	SDL_RenderPresent(pRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	std::cout << "Game Quit!" << std::endl;
}

void Game::AddTile(int id, int x, int y) 
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}