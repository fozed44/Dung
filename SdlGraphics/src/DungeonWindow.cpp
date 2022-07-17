#include "DungeonWindow.h"
#include "TextSheet.h"
#include "Player.h"
#include "Map.h"
#include "DungeonScene.h"
#include "SDLGraphics.h"

using namespace mp::gfx;

void DungeonWindow::Render(const IScene* pScene) {

	auto pDungeonScene = reinterpret_cast<const DungeonScene*>(pScene);

	// These values will be set as long as SetRenderRect
	// has been called.
	int maxViewPortWidthInChars  = GetMaxViewPortWidthInChars();
	int maxViewPortHeightInChars = GetMaxViewPortHeightInChars();

	SDL_assert(maxViewPortWidthInChars);
	SDL_assert(GetMaxViewPortHeightInChars());

	// Get the player location in map space.
	auto mapSurfaceSpacePlayerLocation =
		pDungeonScene->GetSurface().FileSpaceToMapSurfaceSpace(
			pDungeonScene->GetPlayer().GetLocation()
		);	


	// calculate the view port in map space. Notice that
	// we are not going to be doing any clipping. Any coordinates
	// that are outside of the view space will be rendered with
	// the 'empty char' value in the current scene.
	SDL_Rect viewPort{
		mapSurfaceSpacePlayerLocation.x - maxViewPortWidthInChars  / 2,
		mapSurfaceSpacePlayerLocation.y - maxViewPortHeightInChars / 2,
		maxViewPortWidthInChars,
		maxViewPortHeightInChars 
	};

	MapCell const* const _pCells
		= pDungeonScene->GetSurface().GetCells();

	const SDL_Rect& pFileSpaceRect
		= pDungeonScene->GetSurface().GetFileRect();

	for (int y = 0; y < viewPort.h; y++) {

	    int mapSurfaceRenderLocationY = viewPort.y + y;

		for (int x = 0; x < viewPort.w; x++) {
			// The cell, in mapSurfaceSpace that we are rendering
			// during this iteration of the loop.
			int mapSurfaceRenderLocationX = viewPort.x + x;

			
			// If the cell we are currently rendering is outside of
			// pFileSpaceRect, render pDungeonScene->EmptySpace 
			if (mapSurfaceRenderLocationX < 0
			 || mapSurfaceRenderLocationY < 0
			 || mapSurfaceRenderLocationX >= pFileSpaceRect.w
			 || mapSurfaceRenderLocationY >= pFileSpaceRect.h) {
				_pTextSheet->RenderChar(
					pDungeonScene->GetEmptySpace().ascii,
					SDL_Point {
						x * _pTextSheet->GetCharacterWidth(),
						y * _pTextSheet->GetCharacterHeight()
					}
				);
				continue;
			}

			_pTextSheet->RenderChar(
				pDungeonScene->GetSurface().GetCells()
				[
					(viewPort.y + y) * pFileSpaceRect.w
				  + (viewPort.x + x)
				].ascii,
				SDL_Point {
					x * _pTextSheet->GetCharacterWidth(),
					y * _pTextSheet->GetCharacterHeight()
				}
			);
		}
	}
}
