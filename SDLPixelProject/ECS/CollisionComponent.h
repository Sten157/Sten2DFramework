#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class CollisionComponent : public Component 
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* pTransform;

	CollisionComponent(std::string t) 
	{
		tag = t;
	}

	void Init() override
	{
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		pTransform = &entity->GetComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void Update() override 
	{
		collider.x = static_cast<int>(pTransform->position.x);
		collider.y = static_cast<int>(pTransform->position.y);
		collider.w = pTransform->width * pTransform->scale;
		collider.h = pTransform->height * pTransform->scale;
	}
};