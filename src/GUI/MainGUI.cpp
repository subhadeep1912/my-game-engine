#include "MainGUI.h"

MainGUI::MainGUI(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

MainGUI::~MainGUI()
{

}

void MainGUI::RenderInit()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MainGUI::MakeWindow(const char* winName, float varName)
{
    
    bool clsbtn = true;
    ImGui::Begin(winName, &clsbtn);
    ImGui::Button("Hello!");
    ImGui::SliderFloat("rotation", &varName, 0, 2 * M_PI);
    ImGui::End();
}

void MainGUI::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

