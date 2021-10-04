#include "Display.h"

#include "States/GameState.h"
#include "Render/Camera.h"

void Display::CreateDisplay() {

    if(!glfwInit()) {
        std::cout << "Could not initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    s_WindowPtr = glfwCreateWindow(1600, 900, "Minecraft Clone", nullptr, nullptr);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(s_WindowPtr, Camera::MouseCursorCallback);

    glfwSetInputMode(s_WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Camera::SetAspectRatio(1600.0f / 900.0f);

    if(s_WindowPtr == nullptr) {
        glfwTerminate();
        std::cout << "Could not create the GLFW window!";
        return;
    }

    glfwMakeContextCurrent(s_WindowPtr);

    glfwWindowHint(GLFW_SAMPLES, 4);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwFocusWindow(s_WindowPtr);    
}

void Display::StartGameLoop() {

    float endTime, startTime = (float) glfwGetTime();
    float deltaTime = 0.0f;
    float accumulativeDeltaTime = 0.0f;

    uint32_t frameCount = 0;
    uint32_t currentFps = 0;

    while(!glfwWindowShouldClose(s_WindowPtr)) {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(deltaTime >= 0) {
            GameStateManager::OnUpdate(deltaTime);

            // TODO: Update Input
        }

        glfwSwapBuffers(s_WindowPtr);
        glfwPollEvents();

        endTime = (float) glfwGetTime();
        deltaTime = endTime - startTime;
        startTime = endTime;

        accumulativeDeltaTime += deltaTime;
        if(accumulativeDeltaTime >= 1.0f) {
            currentFps = frameCount;
            frameCount = 0;
            accumulativeDeltaTime = 0.0f;
        }

        frameCount++;
    }

    GameStateManager::OnDestroy();

    glfwDestroyWindow(s_WindowPtr);
    glfwTerminate();

}