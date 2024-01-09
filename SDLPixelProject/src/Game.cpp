#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;

SDL_Renderer* Game::pRenderer = nullptr;

Manager manager;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,1300,1400 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
bool Game::isFullScreen = false;

auto& player(manager.AddEntity());

// Labels currently cause memory leaks of ~3 MB/s
// Need to redo UILabel class

//auto& playerPosLabel(manager.AddEntity());
//auto& cameraLabel(manager.AddEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;

	if (isFullScreen == true)
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
	
	if (TTF_Init() == -1) 
	{
		std::cout << "Error : SDL_TTF failed to init" << std::endl;
	}

	assets->AddTexture("terrain", "assets/game_ss.png");
	assets->AddTexture("player", "assets/player_anim.png");
	assets->AddTexture("projectile", "assets/projectile_ss.png");

	assets->AddFont("gameFont", "assets/font.ttf", 16);

	map = new Map("terrain", 2, 32);

	map->LoadMap("assets/map.map", 33, 33, 64);

	player.AddComponent<TransformComponent>(2);
	player.GetComponent<TransformComponent>().height = 16;
	player.GetComponent<TransformComponent>().width = 16;
	player.AddComponent<SpriteComponent>("player", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<CollisionComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color color = { 255, 255, 255 };
	//font size is 15 pixels
	//playerPosLabel.AddComponent<UILabel>(10, 10, "Test String", "gameFont", color);
	//cameraLabel.AddComponent<UILabel>(10, 25, "Test String", "gameFont", color);

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(500, 600), Vector2D(-1, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(1, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(300, 600), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(300, 500), Vector2D(0, -2), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	if (isFullScreen == true) 
	{
		SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_BORDERLESS);
	}

	SDL_Rect playerCol = player.GetComponent<CollisionComponent>().collider;
	Vector2D playerPos = player.GetComponent<TransformComponent>().position;

	//std::stringstream sStream;
	//std::stringstream sStream1;
	//sStream << "Player position: " << playerPos;
	//playerPosLabel.GetComponent<UILabel>().SetLabelText(sStream.str(), "gameFont");
	
	//sStream1 << "Camera X: " << camera.x << "Camera Y: " << camera.y;
	//cameraLabel.GetComponent<UILabel>().SetLabelText(sStream1.str(), "gameFont");

	manager.Refresh();
	manager.Update();

	for (auto& c : colliders) 
	{
		SDL_Rect cCol = c->GetComponent<CollisionComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) 
		{
			player.GetComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles) 
	{
		if (Collision::AABB(playerCol, p->GetComponent<CollisionComponent>().collider)) 
		{
			std::cout << "collided with player" << std::endl;
			p->Destroy();
		}
	}
	// set camera position to middle of screen
	int h, w;
	SDL_GetRendererOutputSize(pRenderer, &w, &h);
	camera.x = playerPos.x - w / 2;
	camera.y = playerPos.y - h / 2;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

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

	for (auto& p : projectiles)
	{
		p->Draw();
	}

	//Render Colliders
	//for (auto& c : colliders)
	//{
	//	c->Draw();
	//}

	//playerPosLabel.Draw();
	//cameraLabel.Draw();

	SDL_RenderPresent(pRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	std::cout << "Game Quit!" << std::endl;
}