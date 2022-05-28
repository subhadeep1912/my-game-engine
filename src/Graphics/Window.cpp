#include "Window.h"

Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

GLFWwindow* Window::GiveWindow()
{

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bruh", NULL, NULL);
    if (window == NULL)
    {
        std::cerr<<"Couldnt create Window"<<std::endl;
        glfwTerminate();

    }
    return window;
}