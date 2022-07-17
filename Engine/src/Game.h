#pragma once

#include "mpInterfaces.h"
#include "StateHandler.h"
#include <map>
#include <memory>

namespace mp {

	class Player;

	class Game {
	private:
		std::map<GAME_STATE, std::unique_ptr<IStateHandler>> _stateHandlers;
		std::map<SCENE_TYPE, std::unique_ptr<IScene>>        _scenes;

		IRenderable*                                         _pRenderer;

		IStateHandler*                                       _pCurrentStateHandler;
		IScene*                                              _pCurrentScene;

		std::unique_ptr<Player>                              _pPlayer;

		void Initialize();
		void ShutDown();
	public:
		Game(Game&)  = delete;
		Game(Game&&) = delete;

		Game(IRenderable* pRenderable) : _pRenderer{ pRenderable } {}
		~Game() {};


		void Run();

	};
}
