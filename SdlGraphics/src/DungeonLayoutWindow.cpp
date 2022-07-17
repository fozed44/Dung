#pragma once

#include "DungeonLayoutWindow.h"
#include "DungeonWindow.h"
#include "TextOverlayWindow.h"
#include "Exception.h"
#include "TextSheet.h"
#include "SDLGraphics.h"

using namespace mp::gfx;

DungeonLayoutWindow::DungeonLayoutWindow() 
	: Window(
		SDLGraphics::Instance()->GetWidth(),
		SDLGraphics::Instance()->GetHeight()
	) {}

DungeonLayoutWindow::~DungeonLayoutWindow() {}


void DungeonLayoutWindow::SetOverlayTextSheet(const TextSheetHandle& textSheet) {
	_pOverlayWindow->SetTextSheet(textSheet);
}

void DungeonLayoutWindow::SetDungeonTextSheet(const TextSheetHandle& textSheet) {
	_pDungeonWindow->SetTextSheet(textSheet);
}

void DungeonLayoutWindow::Render(const IScene* pScene) {
	SDL_RenderClear(SDLGraphics::Instance()->GetRenderer());
	_pDungeonWindow->Render(pScene);
	_pOverlayWindow->Render(pScene);
	SDL_RenderPresent(SDLGraphics::Instance()->GetRenderer());
}
