#include "Graphics.hpp"
#include <cstdlib>
#include "makeShaders.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

// const char *vertexShaderSource = "#version 330 core\n"
// "layout (location=0) in vec3 aPos;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "}\0";

// const char *fragmentShaderSource = "#version 330 core\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
// "}\0";

void framebuff_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Bruh", NULL, NULL);
    if (window == NULL)
    {
        std::cerr<<"Couldnt create Window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr<<"Glad Didnt load"<<std::endl;
        return -2;
    }

    glViewport(0, 0,800, 600);
     
    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
    // int count = 0;
    unsigned int VBO;
    glGenBuffers(1, &VBO);


    // unsigned int vertexShader;
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);
    // int success;
    // char infoLog[512];
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    // }
    // unsigned int fragShader;
    // fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragShader);
    // glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    // }
    // unsigned int shaderPro;
    // shaderPro = glCreateProgram();
    // glAttachShader(shaderPro, vertexShader);
    // glAttachShader(shaderPro, fragShader);


    // glLinkProgram(shaderPro);

     
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragShader);
    Shader *s = new Shader();
    unsigned int shaderPro = s->MakeProgram();
    delete s;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glUseProgram(shaderPro);
    glBindVertexArray(0);

    // glDrawArrays(GL_TRIANGLES, 0, 3);




    while(!glfwWindowShouldClose(window))
    {
        processInputs(window);

        glClearColor(0.3f, 0.4f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderPro);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
        // count++;
    }

    glfwTerminate();
    return 0;
}