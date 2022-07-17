#include "DungeonStateHandler.h"
#include "Player.h"
#include "DungeonScene.h"

using namespace mp;

void DungeonStateHandler::EnteringState() {
}

void DungeonStateHandler::CommandMoveUp(DungeonScene* pScene) const {
    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x,
        currentLocation.y - 1
    });
}

void DungeonStateHandler::CommandMoveDown(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x,
        currentLocation.y + 1
    });
}

void DungeonStateHandler::CommandMoveLeft(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x - 1,
        currentLocation.y
    });
}

void DungeonStateHandler::CommandMoveRight(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x + 1,
        currentLocation.y 
    });
}

void DungeonStateHandler::CommandMoveUL(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x - 1,
        currentLocation.y + 1
    });
}

void DungeonStateHandler::CommandMoveUR(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x + 1,
        currentLocation.y - 1
    });
}
void DungeonStateHandler::CommandMoveLR(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x + 1,
        currentLocation.y + 1
    });
}

void DungeonStateHandler::CommandMoveLL(DungeonScene* pScene) const {

    auto currentLocation = pScene->GetPlayer().GetLocation();

    pScene->GetPlayer().SetLocation({
        currentLocation.x - 1,
        currentLocation.y + 1
    });
}

GAME_STATE DungeonStateHandler::HandleGameLoop(
    const SDL_Event* pEvent,
    IScene*          pScene
) {
    // If pEvent is nullptr, we aren't going to do anything, so
    // we are going to return the state handled by this state
    // handler so that the game engine knows that we are going
    // to remain in this state.
    if (!pEvent)
        return HANDLED_STATE;

    switch (pEvent->type) {
    case SDL_KEYDOWN:
        switch ((reinterpret_cast<const SDL_KeyboardEvent*>(pEvent))->keysym.sym) {
        case SDLK_LEFT:
        case SDLK_KP_4:
        case SDLK_h:
            CommandMoveLeft(reinterpret_cast<DungeonScene*>(pScene));
            return HANDLED_STATE;


        case SDLK_UP:
        case SDLK_KP_8:
        case SDLK_k:
            CommandMoveUp(reinterpret_cast<DungeonScene*>(pScene));
            return HANDLED_STATE;

        case SDLK_RIGHT:
        case SDLK_KP_6:
        case SDLK_SEMICOLON:
            CommandMoveRight(reinterpret_cast<DungeonScene*>(pScene));
            return HANDLED_STATE;

        case SDLK_DOWN:
        case SDLK_KP_2:
        case SDLK_j:
            CommandMoveDown(reinterpret_cast<DungeonScene*>(pScene));
            return HANDLED_STATE;

        }
        break;
    }
    // Do not change the state.
    return HANDLED_STATE;
}
