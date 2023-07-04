#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);
	xPos = x;
	yPos = y;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	xPos++;
	yPos++;

	src.h = 16;
	src.w = 16;
	src.x = 0;
	src.y = 0;

	dest.x = xPos;
	dest.y = yPos;
	dest.h = src.h * 4;
	dest.w = src.w * 4;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::pRenderer, objTexture, &src, &dest);
}
