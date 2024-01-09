#include "SDL.h"
#include "Game.h"

Game* pGame = nullptr;

int main(int argc, char* argv[]) 
{
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	pGame = new Game();

	pGame->Init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 450, false);

	while (pGame->Running())
	{
		frameStart = SDL_GetTicks();

		pGame->EventHandler();
		pGame->Update();
		pGame->Render();

		frameTime = SDL_GetTicks() - frameStart;

		// limit framerate
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	pGame->Clean();

	return 0;
}