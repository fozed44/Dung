#pragma once

#include "Scene.h"
#include <vector>
#include <memory>
#include <SDL_Rect.h>
#include "Map.h"

namespace mp {

	class  Player;

	/// <summary>
	/// Contains the elements that will drawn to the screen during
	/// a call to render. Can be rendered by the DungeonRenderer
	///
	/// NOTES:
	/// </summary>
	class DungeonScene : public IScene {
	private:
		static constexpr SCENE_TYPE THIS_SCENE_TYPE = SCENE_TYPE::DUNGEON;

		/// <summary>
		/// Overlays are strings that the renderer should
		/// render to the screen. Overlays can be rendered
		/// anywhere, the locations in the overlay objects
		/// are relative to the upper left corner of the 
		/// window.
		/// </summary>
		std::vector<StringOverlay>   _stringOverlays;

		/// <summary>
		/// The map surface contains all of the data for the current
		/// map that is currently in memory.
		/// </summary>
		std::unique_ptr<MapSurface>  _pMapSurface;

		/// <summary>
		/// The player. The player is not owned by a dungeon scene, however
		/// a player is required in order to render a dungeon scene
		/// </summary>
		Player*                      _pPlayer;

		/// <summary>
		/// The character information that should be used by the
		/// renderer when rendering cells outside of the map.
		/// </summary>
		std::unique_ptr<MapCell>    _pEmptySpace;
	public:
		DungeonScene(Player* pPlayer) : _pPlayer{ pPlayer } {}
		virtual ~DungeonScene() {}

		// IScene Overrides
		virtual SCENE_TYPE GetSceneType() const noexcept override { return THIS_SCENE_TYPE; }

		/** Constant methods */
		const std::vector<StringOverlay>& GetOverlays() const noexcept { return _stringOverlays; }
		const MapSurface& GetSurface() const noexcept { return *_pMapSurface.get(); }
		const Player& GetPlayer() const noexcept { return *_pPlayer; }
		const MapCell& GetEmptySpace() const noexcept { return *_pEmptySpace.get(); }

		std::vector<StringOverlay>& GetOverlays() noexcept { return _stringOverlays; }
		Player& GetPlayer() noexcept { return *_pPlayer; }

		void Load(const std::string&);
	};
};
