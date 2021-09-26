#include "GameState.h"

// =============================================================================
// GameState
// =============================================================================


// =============================================================================
// GameStateManager
// =============================================================================
void GameStateManager::SetActiveGameState(GameState* gameStatePtr) {
    if(s_GameStatePtr != nullptr) {
        auto* tempPtr = s_GameStatePtr;
        s_GameStatePtr = nullptr;

        tempPtr->OnDestroy();
    }

    gameStatePtr->OnCreate();
    s_GameStatePtr = gameStatePtr;
}

void GameStateManager::OnUpdate(float deltaTime) {
    if(s_GameStatePtr != nullptr)
        s_GameStatePtr->OnUpdate(deltaTime);
}

void GameStateManager::OnDestroy() {
    auto* tempPtr = s_GameStatePtr;
    s_GameStatePtr = nullptr;

    if(tempPtr != nullptr)
        tempPtr->OnDestroy();
}