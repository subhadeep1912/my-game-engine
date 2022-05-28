#pragma once
#include "Buffers.h"

class Renderer
{
private:
    float* r_vertices;
    int r_vert;
    GLuint r_VAO;
public:
    Renderer(float*, int);
    ~Renderer();
    void Draw(GLuint);
};