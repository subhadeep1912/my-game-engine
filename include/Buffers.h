#pragma once

#include "Graphics.hpp"

class Buffers
{
private:
    GLuint c_VBO;
    GLuint c_EBO;
    
    float* c_vertices;
    int c_vert;
    size_t c_size;
    int c_numEle;
    int c_layout;
    int* c_indices;
    size_t c_isize;
    int c_inumEle;

public:
    Buffers(float*, int, size_t, int, int, size_t, int, int*);
    ~Buffers();
    void Bind();
    void UnBind();
};