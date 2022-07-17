#include "DungeonScene.h"
#include "Exception.h"
#include "Map.h"
#include "Player.h"

using namespace mp;

void DungeonScene::Load(const std::string& filename) {
	
	auto pCells = static_cast<MapCell*>(malloc(sizeof(MapCell) * 100 * 100));
	ThrowWhenNull<MpGraphicsInitException>(pCells, "Memory allocation failure!");
	memset(pCells, 0, sizeof(MapCell) * 100 * 100);

	for (int x = 0; x < (100 * 100); x++) {
		pCells[x].ascii = ' ' + x % 10;
	}

	auto pMapSurface = new MapSurface(
		SDL_Rect{ 0, 0, 100, 100 },
		std::unique_ptr<MapCell>(pCells)
	);

	auto pEmptySpace = new MapCell{
		' ',
		0,
		0,
		0,
		{
			0xFF,
			0xFF,
			0xFF,
			0xFF
		}
	};

	_pEmptySpace = std::unique_ptr<MapCell>(pEmptySpace);

	_pMapSurface = std::unique_ptr<MapSurface>(pMapSurface);

	_pPlayer->SetLocation({20, 20});
}
