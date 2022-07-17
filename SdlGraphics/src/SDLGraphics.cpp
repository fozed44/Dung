#pragma once

#include "SDLGraphics.h"
#include "Exception.h"

using namespace mp::gfx;

/// <summary>
/// Set the instance point to null, just to make sure it is pointing
/// there in case someone calls Instance() before calling InitializeInstace
/// </summary>
SDLGraphics* SDLGraphics::_instance = nullptr;

SDLGraphics::SDLGraphics(int width, int height)
	: 
	_pWindow   { nullptr },
	_pRenderer { nullptr },
	_width     { width   },
	_height    { height  }
{
	SDL_Log("Init SDL library.");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		Throw<MpGraphicsInitException>("SDL could not initialize! SDL_Error: _se");

	SDL_Log("Init SDL window.");
	_pWindow = ThrowWhenNull<MpGraphicsInitException>(
		SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_width,
			_height,
			SDL_WINDOW_SHOWN
		),
		"Window could not be created! SDL Error: \n _se"
	);

	SDL_Log("Init SDL renderer.");
	_pRenderer = ThrowWhenNull<MpGraphicsInitException>(
		SDL_CreateRenderer(
			_pWindow,
			-1,
			SDL_RENDERER_ACCELERATED
		),
		"Renderer could not be created! SDL Error: \n _se"
	);
}

SDLGraphics::~SDLGraphics() {
	if (_pWindow)
		SDL_DestroyWindow(_pWindow);

	if (_pRenderer)
		SDL_DestroyRenderer(_pRenderer);

	SDL_Quit();
}

SDLGraphics* SDLGraphics::InitializeInstance(int width, int height) {

	// This method should only be called if _instance == nullptr.
	// If the caller is trying to re-create the graphics wrapper,
	// he should be calling DestroyInstance first.
	SDL_assert(_instance == nullptr);

	SDL_Log("Initializing new SDLGraphics.");

	_instance = new SDLGraphics(width, height);

	return _instance;
}

void SDLGraphics::DestroyInstance() {
	
	// This method should only be called when the caller has first called
	// InitializeInstance()
	SDL_assert(_instance != nullptr);

	SDL_Log("Destroying SDLGraphics.");

	delete _instance;

	_instance = nullptr;
}

TextSheetHandle SDLGraphics::LoadTextSheet(
	const std::string& filename,
	int                fontSize,
	int                characterWidth,
	int                characterHeight,
	uint8_t			   r,
	uint8_t			   g,
	uint8_t			   b 
) {
	return std::make_shared<TextSheet>(
		filename,
		fontSize,
		characterWidth,
		characterHeight,
		r,
		g,
		b
	);
}
