/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "TextSheet.h"
#include "Window.h"
#include "DungeonWindow.h"
#include "Exception.h"
#include "Timers.h"
#include "DungeonLayoutWindow.h"
#include "Map.h"
#include "Player.h"
#include <math.h>
#include "Game.h"
#include "SDLGraphics.h"
#include "TextWindow.h"
#include "TextOverlayWindow.h"

using namespace mp;

//Screen dimension constants
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 800;

using namespace mp::gfx;

int main(int argc, char* args[]) {
	AveragingMsTimer timer(100);
	SDLGraphics::InitializeInstance(SCREEN_WIDTH, SCREEN_HEIGHT);

	auto pLayoutWindow = std::make_shared<DungeonLayoutWindow>();

	auto pGame = std::make_shared<Game>((IRenderable *)pLayoutWindow.get());

	auto dngWindow = std::make_shared<DungeonWindow>(400, 400);
	auto ovrWindow = std::make_shared<TextOverlayWindow>(400, 100);
	
	Window::AddChild(pLayoutWindow, dngWindow, { 0, 0 });
	Window::AddChild(pLayoutWindow, std::shared_ptr<Window>(ovrWindow.get()), {0, 400});

	pLayoutWindow->SetDungeonWindow(dngWindow);
	pLayoutWindow->SetTextOverlayWindow(ovrWindow);

	auto _pViewPortTextSheet = SDLGraphics::Instance()->LoadTextSheet("c:\\Projects\\fonts\\FSEX302.ttf", 64, 10, 10);
	auto _pOverlayTextSheet  = SDLGraphics::Instance()->LoadTextSheet("c:\\Projects\\fonts\\FSEX302.ttf", 64, 10, 15, 0x00, 0xFF, 0x00);

	pLayoutWindow->SetOverlayTextSheet(_pOverlayTextSheet);
	pLayoutWindow->SetDungeonTextSheet(_pViewPortTextSheet);

	pGame->Run();

	mp::gfx::SDLGraphics::DestroyInstance();

	return 0;
}