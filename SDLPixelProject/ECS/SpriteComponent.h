#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
public:

	int animationIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlipFlag = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(const char* filepath)
	{

		SetTexture(filepath);
	}
	SpriteComponent(const char* filepath, bool isAnimated) 
	{
		animated = isAnimated;

		Animation idle = Animation(0, 4, 150);
		Animation walk = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		SetTexture(filepath);
	}

	~SpriteComponent() 
	{
		SDL_DestroyTexture(pTexture);
	}

	void SetTexture(const char* filepath) 
	{
		pTexture = TextureManager::LoadTexture(filepath);
	}

	void Init() override 
	{
		pTransform = &entity->GetComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = pTransform->width;
		srcRect.h = pTransform->height;
	}

	void Update() override
	{
		if (animated) 
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animationIndex * pTransform->height;

		destRect.x = static_cast<int>(pTransform->position.x);
		destRect.y = static_cast<int>(pTransform->position.y);
		destRect.w = pTransform->width * pTransform->scale;
		destRect.h = pTransform->height * pTransform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(pTexture, srcRect, destRect, spriteFlipFlag);
	}

	void Play(const char* animName) 
	{
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		animationIndex = animations[animName].index;
	}

private:
	TransformComponent*	pTransform;
	SDL_Texture*		pTexture;
	SDL_Rect	srcRect, destRect;

	bool animated = false;
	int frames = 0;
	
	//animation delay in MS
	int speed = 100;
};