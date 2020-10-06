// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char * args[])
{
	Uint32 frameStart, frameTime = 0;
	UINT32 frames = 0;


	// show console
	AllocConsole();
	freopen("CON", "w", stdout);


	TheGame::Instance()->init("SDLEngine 0.25", 100, 100, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, false);

	while (TheGame::Instance()->isRunning())
	{
		frameStart = SDL_GetTicks();

		TheGame::Instance()->handleEvents(frameTime*0.001f);
		TheGame::Instance()->update(frameTime*0.001f);
		TheGame::Instance()->render();

		frames++;
		TheGame::Instance()->setFrames(frames);
		frameTime = SDL_GetTicks() - frameStart;
	}

	TheGame::Instance()->clean();
	return 0;
}

