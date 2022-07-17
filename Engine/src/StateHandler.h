#pragma once
#include <SDL_events.h>

namespace mp {

	class IScene;

	/// <summary>
	/// Enumerates the possible game states. Each state will have
	/// its own StateHandler sub-class.
	/// </summary>
	enum class GAME_STATE {
		INTRO_SCREEN,
		DUNGEON,
		CLOSE,
		NUM_GAME_STATES
	};

	class IStateHandler {
	public:
		virtual ~IStateHandler() = 0 {}

		/// <summary>
		/// Return the GAME_STATE that this state handler handles.
		/// </summary>
		virtual GAME_STATE GetHandledState() const noexcept = 0;

		/// <summary>
		/// Called by the Game class just before when the state has changed,
		/// before the first call to HandleGameLoop for the first time
		/// after the state change.
		/// </summary>
		virtual void EnteringState() = 0;

		/// <summary>
		/// On each iteration through the game loop the Game class
		/// will call HandleGameLoop for exactly one StateHandler
		/// sub-class... Which ever subclass matches the current game
		/// state.
		/// </summary>
		/// <param name="pEvent">
		///	The SDL_Event. This pointer may be null.
		/// </param>
		/// <returns>
		/// The Next game state. The StateHandler sub-class is
		/// responsible for determining if the state is going to
		/// change and if so, what it will change to. The Game class
		/// is responsible for monitoring this return value in order
		/// to determining which StateHandler will receive the next
		/// HandleGameLoop call.
		/// </returns>
		virtual GAME_STATE HandleGameLoop(const SDL_Event*, IScene*) = 0;
	};

}
