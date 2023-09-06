#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component 
{
public: 
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
	{}
	~ProjectileComponent(){}

	void Init() override 
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void Update() override
	{
		distance += speed;

		if (distance > range) 
		{
			std::cout << "Out of range" << std::endl;
			entity->Destroy();
		}
		else if 
			 (
			 transform->position.x > Game::camera.x + Game::camera.w || 
			 transform->position.x < Game::camera.x || 
			 transform->position.y > Game::camera.y + Game::camera.h ||
			 transform->position.y < Game::camera.y
			 )
			 {
				std::cout << "Out of bounds" << std::endl;
			 	entity->Destroy();
			 }
	}

private:
	TransformComponent* transform;
	int range;
	int speed;
	int distance;
	Vector2D velocity;
};