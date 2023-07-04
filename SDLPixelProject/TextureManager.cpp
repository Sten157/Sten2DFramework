#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::pRenderer, texture, &src, &dest);
}
