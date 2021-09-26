#pragma once

class GameState {

public:
    virtual void OnCreate() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnDestroy() {}

};

class Display;

class GameStateManager {

public:

    static void SetActiveGameState(GameState* gameStatePtr);

private:

    static void OnUpdate(float deltaTime);
    static void OnDestroy();

private:
    static inline GameState* s_GameStatePtr = nullptr;

    friend class Display;

};