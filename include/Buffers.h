#pragma once

#include "Graphics.hpp"

class Buffers
{
private:
    GLuint c_VBO;
    
    float* c_vertices;
    int c_vert;
    size_t c_size;
    int c_numEle;
    int c_layout;

public:
    Buffers(float*, int, size_t, int, int);
    ~Buffers();
    void Bind();
    void UnBind();
};