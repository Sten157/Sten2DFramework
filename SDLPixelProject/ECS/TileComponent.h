#pragma once
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component 
{
public:
	TransformComponent* pTransform;
	SpriteComponent*	pSprite;

	SDL_Rect tileRect;
	int tileID;
	
	char path[32];

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) 
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			snprintf(path, 32, "assets/water.png");
			break;
		case 1:
			snprintf(path, 32, "assets/wall.png");
			break;
		case 2:
			snprintf(path, 32, "assets/ground.png");
			break;
		case 3:
			snprintf(path, 32, "assets/grass.png");
			break;
		default:
			break;
		}
	}

	void Init() 
	{
		entity->AddComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		pTransform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path);
		pSprite = &entity->GetComponent<SpriteComponent>();
	}
};