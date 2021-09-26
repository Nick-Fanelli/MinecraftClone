#pragma once

#include "pch.h"

class Display {

public:
    static void CreateDisplay();
    static void StartGameLoop();

private:
    static inline GLFWwindow* s_WindowPtr = nullptr;

};