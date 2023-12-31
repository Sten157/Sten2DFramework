#pragma once
#include "../Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class KeyboardController : public Component 
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	int movespeed = 2;

	void Init() override 
	{
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
	}

	void Update() override 
	{
		if (Game::event.type == SDL_KEYDOWN) 
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1 * movespeed;
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1 * movespeed;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1 * movespeed;
				sprite->spriteFlipFlag = SDL_FLIP_HORIZONTAL;
				sprite->Play("Walk");
				break;
			case SDLK_d:
				transform->velocity.x = 1 * movespeed;
				sprite->spriteFlipFlag = SDL_FLIP_NONE;
				sprite->Play("Walk");
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) 
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_F11:
				Game::isFullScreen = !Game::isFullScreen;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;

			default:
				break;
			}
		}

		if (transform->velocity.x == 0 && transform->velocity.y == 0) 
		{
			sprite->Play("Idle");
		}
	}
};