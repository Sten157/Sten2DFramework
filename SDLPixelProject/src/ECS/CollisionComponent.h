#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class CollisionComponent : public Component 
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcR, destR;

	TransformComponent* pTransform;

	CollisionComponent(std::string t) 
	{
		tag = t;
	}

	CollisionComponent(std::string t, int xpos, int ypos, int size) 
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void Init() override
	{
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		pTransform = &entity->GetComponent<TransformComponent>();

		texture = TextureManager::LoadTexture("assets/coltex.png");
		srcR	= { 0,0,32,32 };
		destR	= { collider.x,collider.y,collider.w,collider.h };
	}

	void Update() override 
	{
		if (tag != "terrain") 
		{
			collider.x = static_cast<int>(pTransform->position.x);
			collider.y = static_cast<int>(pTransform->position.y);
			collider.w = pTransform->width * pTransform->scale;
			collider.h = pTransform->height * pTransform->scale;
		}
		destR.x		= collider.x - Game::camera.x;
		destR.y		= collider.y - Game::camera.y;
	}

	void Draw() override 
	{
		TextureManager::Draw(texture, srcR, destR, SDL_FLIP_NONE);
	}
};