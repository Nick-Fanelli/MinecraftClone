#include <iostream>

#include "Core/Display.h"
#include "States/GameState.h"
#include "States/PlayState.h"

int main() {
    Display::CreateDisplay();

    PlayState playState{};
    GameStateManager::SetActiveGameState(&playState);

    Display::StartGameLoop();

    return 0;
}