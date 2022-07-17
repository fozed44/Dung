#pragma once
#include <cstdint>
#include <SDL_rect.h>
#include <memory>

namespace mp {

/// <summary>
///	A cell containing information for one single cell
///	of a map.
/// </summary>
struct MapCell {
	uint8_t   ascii;
	uint8_t   flags;
	uint8_t   flags2;
	uint8_t   flags3;
	SDL_Color color;
};

/// <summary>
/// In memory rectangle of cells.
/// </summary>
class MapSurface {
	/// <summary>
	/// The rectangle of the surface in filespace.
	/// Filespace is has 0,0 as the first cell in the
	/// .dng file. 
	/// 
	/// Note that this means that _fileRect.x,_fileRect.y 
	/// is usually not going to be 0, 0
	/// </summary>
	SDL_Rect                   _fileRect;

	/// <summary>
	/// The actual cells in the surface. One cell for
	/// for each location in the rect, so we have 
	/// _fileRect.x * _fileRect.y cells here.
	/// </summary>
	std::unique_ptr<MapCell> _pCells;
public:
	MapSurface(
		const SDL_Rect &rect,
		std::unique_ptr<MapCell> cells
	) : _fileRect { rect },
		_pCells { std::move(cells) } {}

	virtual ~MapSurface() {}

	const MapCell*  const GetCells()    const { return _pCells.get(); }
	const SDL_Rect&       GetFileRect() const { return _fileRect; }

	/// <summary>
	/// Transform a point in file space to a rect in map surface space.
	/// </summary>
	SDL_Point FileSpaceToMapSurfaceSpace(const SDL_Point& point) const {
		return SDL_Point{
			point.x - _fileRect.x,
			point.y - _fileRect.y
		};
	}

	/// <summary
	/// Transform a rect in file space to a rect in map surface space.
	/// </summary>
	SDL_Rect FileSpaceToMapSurfaceSpace(const SDL_Rect& rect) const {
		return SDL_Rect{
			rect.x - _fileRect.x,
			rect.y - _fileRect.y,
			rect.w,
			rect.h
		};
	}

	/// <summary
	/// Transform a point in map surface space to a rect in file space.
	/// </summary>
	SDL_Point MapSurfaceSpaceToFileSpace(const SDL_Point& point) const {
		return SDL_Point{
			point.x + _fileRect.x,
			point.y + _fileRect.y
		};
	}

	/// <summary
	/// Transform a rect in map surface space to a rect in file space.
	/// </summary>
	SDL_Rect MapSurfaceSpaceToFileSpace(const SDL_Rect& rect) const {
		return SDL_Rect{
			rect.x + _fileRect.x,
			rect.y + _fileRect.y,
			rect.w,
			rect.h
		};
	}
};
}
