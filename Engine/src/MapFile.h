#pragma once

#include <string>
#include <memory>
#include "map.h"

namespace mp {

	/// <summary>
	/// A file containing map data.
	/// </summary>
	class MapFile {
		std::string _filename;
	public:
		MapFile(std::string filename) : _filename(filename) {};
		virtual ~MapFile() {};

		std::unique_ptr<MapSurface> loadMapSurface(MapSurface);

		// Read the width or height of the map.
		int GetWidth()  { return _width; }
		int GetHeight() { return _height; }

	private:
		int _width;
		int _height;
	};
}
