#pragma once

#include "StateHandler.h"

namespace mp {

	class DungeonScene;
	class Player;
	class IScene;

	class DungeonStateHandler : public IStateHandler {
	private:
		static constexpr GAME_STATE HANDLED_STATE = GAME_STATE::DUNGEON;

		// Movement
		void CommandMoveUp   (DungeonScene* pScene) const;
		void CommandMoveRight(DungeonScene* pScene) const;
		void CommandMoveDown (DungeonScene* pScene) const;
		void CommandMoveLeft (DungeonScene* pScene) const;

		void CommandMoveUL(DungeonScene* pScene) const;
		void CommandMoveUR(DungeonScene* pScene) const;
		void CommandMoveLR(DungeonScene* pScene) const;
		void CommandMoveLL(DungeonScene* pScene) const;

	public:
		DungeonStateHandler() {}
		virtual ~DungeonStateHandler() {}

		// Inherited via IStateHandler
		virtual void EnteringState() override;
		virtual GAME_STATE HandleGameLoop(const SDL_Event*, IScene*) override;
		virtual GAME_STATE GetHandledState() const noexcept override { return HANDLED_STATE; }
	};
}
