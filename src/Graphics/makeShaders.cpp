#include "makeShaders.h"

Shader::Shader()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);
    
}

unsigned int Shader::MakeProgram()
{
    shaderPro = glCreateProgram();
    glAttachShader(shaderPro, vertexShader);
    glAttachShader(shaderPro, fragShader);

    glLinkProgram(shaderPro);
    return shaderPro;
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}