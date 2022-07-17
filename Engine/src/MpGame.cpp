#include "Game.h"
#include "DungeonScene.h"
#include "DungeonStateHandler.h"
#include "Player.h"

using namespace mp;

void Game::Initialize() {
	_pPlayer = std::make_unique<Player>();

	// Initialize state handlers
	_stateHandlers[GAME_STATE::DUNGEON] = std::move(std::make_unique<DungeonStateHandler>());

	// Initialize Scenes
	_scenes[SCENE_TYPE::DUNGEON] = std::make_unique<DungeonScene>(_pPlayer.get());

	// Set up the initial scene and state handler
	_pCurrentScene        = _scenes[SCENE_TYPE::DUNGEON].get();
	_pCurrentStateHandler = _stateHandlers[GAME_STATE::DUNGEON].get();

	reinterpret_cast<DungeonScene*>(_pCurrentScene)->Load("test");
}

void Game::Run() {

	Initialize();

	SDL_Event e;
	while (true) {

		SDL_PollEvent(&e);

		auto nextState = _pCurrentStateHandler->HandleGameLoop(&e, _pCurrentScene);

		_pRenderer->Render(_pCurrentScene);

		if (nextState == GAME_STATE::CLOSE)
			break;
	}

	ShutDown();
}

void Game::ShutDown() {}
