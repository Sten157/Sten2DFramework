#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* filepath) 
	{
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
		destRect.x = static_cast<int>(pTransform->position.x);
		destRect.y = static_cast<int>(pTransform->position.y);
		destRect.w = pTransform->width * pTransform->scale;
		destRect.h = pTransform->height * pTransform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(pTexture, srcRect, destRect);
	}
private:
	TransformComponent*	pTransform;
	SDL_Texture*		pTexture;
	SDL_Rect	srcRect, destRect;
};