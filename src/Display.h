#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display {

public:
    static void CreateDisplay();
    static void StartGameLoop();

private:
    static inline GLFWwindow* s_WindowPtr = nullptr;

};