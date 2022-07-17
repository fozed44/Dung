#pragma once

#include <string>
#include <SDL_Rect.h>


namespace mp {

	enum class SCENE_TYPE {
		INTRO_SCREEN,
		DUNGEON,
		NUM_SCENES
	};

	/// <summary>
	/// A string along with a location. This represents a string
	/// to be rendered on the screen as an overlay. The MpScene
	/// object contains a vector of these objects that the renderer
	/// is responsible for displaying on the screen.
	/// </summary>
	struct StringOverlay {
		SDL_Point   _location;
		std::string _s;
	};

	/// <summary>
	/// Interface for scene data implementations. 
	/// </summary>
	class IScene {
	public:
		virtual ~IScene() = 0 {}
		virtual SCENE_TYPE GetSceneType() const noexcept = 0;
	};
};