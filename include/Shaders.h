#pragma once
#include "Graphics.hpp"
#include <fstream>
#include <iostream>

class Shader
{
private:

    unsigned int vertexShader;
    unsigned int fragShader;
    unsigned int shaderPro;

public:
    Shader(const char* vertShadeSrc, const char* fragShadeSrc);
    ~Shader();
    unsigned int MakeProgram();
    void ModUniform1f(GLuint, const char*, float);
    void ModUniform4f(GLuint, const char*, float, float, float, float);
    void ModUniform4fv(GLuint, const char*, glm::mat4);
};

