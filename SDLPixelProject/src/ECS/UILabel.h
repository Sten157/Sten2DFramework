#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "EntityComponentSystem.h"
#include "../Game.h"
#include "../AssetManager.h"

class UILabel : public Component 
{
public:
	UILabel(int xPos, int yPos, std::string text, std::string font, SDL_Color& color) :
		labelText(text), labelFont(font), textColor(color)
	{
		position.x	= xPos;
		position.y	= yPos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel()	{}

	void SetLabelText(std::string text, std::string font)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::pRenderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void Draw() override 
	{
		SDL_RenderCopy(Game::pRenderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect		position;
	std::string		labelText;
	std::string		labelFont;
	SDL_Color		textColor;
	SDL_Texture*	labelTexture;
};