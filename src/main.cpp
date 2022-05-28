#include "Graphics.hpp"
#include "Shaders.h"
#include "Window.h"
#include <cmath>
#include "glm/vec2.hpp"
#include "MainGUI.h"



const char* vertexShaderSource = "src/Graphics/shaders/temp_1.glsl";
const char* fragShaderSource = "src/Graphics/shaders/temp_1_frag.glsl";
const char* fragShaderSource1 = "src/Graphics/shaders/temp_2.glsl";
const char* fragShaderSource2 = "src/Graphics/shaders/try_1.glsl";

float vertices1[] = {
    -0.5f, 0.5f,0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,

    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,

    -0.5f, 0.5f,1.0f,
    0.5f, -0.5f, 1.0f,
    -0.5f, -0.5f, 1.0f,

    -0.5f, 0.5f, 1.0f,
    0.5f, 0.5f, 1.0f,
    0.5f, -0.5f, 1.0f,

    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 1.0f,

    0.5f, 0.5f, 1.0f,
    0.5f, -0.5f, 1.0f,
    0.5f, 0.5f, 0.0f,

    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 1.0f,

    -0.5f, 0.5f, 1.0f,
    -0.5f, -0.5f, 1.0f,
    -0.5f, 0.5f, 0.0f,

    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 1.0f,

    -0.5f, 0.5f, 1.0f,
    0.5f, 0.5f, 1.0f,
    0.5f, 0.5f, 0.0f,

    -0.5f,-0.5f, 0.0f,
    0.5f,-0.5f, 0.0f,
    -0.5f, -0.5f, 1.0f,

    -0.5f, -0.5f, 1.0f,
    0.5f, -0.5f, 1.0f,
    0.5f, -0.5f, 0.0f,
};


void framebuff_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(width/4, height/4 ,width/2, height/2);
}

void processInputs(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Window* winObj = new Window();
    GLFWwindow* window = winObj->GiveWindow();

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr<<"Glad Didnt load"<<std::endl;
        return -2;
    }

    glViewport(WIDTH/4, HEIGHT/4 ,WIDTH/2, HEIGHT/2);
    
     
    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);

    Shader *s1 = new Shader(vertexShaderSource, fragShaderSource);
    unsigned int shaderPro1 = s1->MakeProgram();
    delete s1;  
     
    Shader *s2 = new Shader(vertexShaderSource, fragShaderSource1);
    unsigned int shaderPro2 = s2->MakeProgram();

    GLuint VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    Buffers b1(vertices1, 3, sizeof(float), 108, 0);
    Buffers b2(vertices1, 3, sizeof(float), 108, 1);
    glBindVertexArray(0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    while(!glfwWindowShouldClose(window))
    {
        processInputs(window);
        static float count = -60;
        static float count_d = -60;
        glClearColor(0.3f, 0.4f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shaderPro2);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 model_alt = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(count), glm::vec3(1.0f, 0.0f, 0.0f));
        model_alt = glm::rotate(model_alt, glm::radians(count_d), glm::vec3(0.0f, 1.0f, 0.0f));
        model = model * model_alt;
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        s2->ModUniform4fv(shaderPro2, "model", model);
        s2->ModUniform4fv(shaderPro2, "view", view);
        s2->ModUniform4fv(shaderPro2, "projection", projection);
        s2->ModUniform1f(shaderPro2, "u_time", (float)glfwGetTime());
        glBindVertexArray(VAO2);
    
        glDrawArrays(GL_TRIANGLES, 0, 66);

        if (glfwGetKey(window, GLFW_KEY_W))
            count += 0.9;
        if (glfwGetKey(window, GLFW_KEY_S))
            count -= 0.9;
        if (glfwGetKey(window, GLFW_KEY_D))
            count_d -= 0.9;
        if (glfwGetKey(window, GLFW_KEY_A))
            count_d += 0.9;

        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    delete s2;
    glfwTerminate();
    return 0;
}