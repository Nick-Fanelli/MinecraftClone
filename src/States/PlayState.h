#pragma once

#include "GameState.h"

class PlayState : public GameState {

public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;

};