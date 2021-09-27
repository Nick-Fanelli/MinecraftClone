#pragma once

#include "pch.h"

class Display {

public:
    static void CreateDisplay();
    static void StartGameLoop();

    static GLFWwindow* GetWindowPtr() { return s_WindowPtr; }

private:
    static inline GLFWwindow* s_WindowPtr = nullptr;

};