#pragma once
#include "Graphics.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cmath>

class MainGUI
{
public:
    MainGUI(GLFWwindow*);
    ~MainGUI();
    void RenderInit();
    void MakeWindow(const char*, float);
    void Render();
};