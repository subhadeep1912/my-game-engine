#include "Renderer.h"

Renderer::Renderer(float* vertices, int vert):r_vertices(vertices), r_vert(vert)
{
//     glGenVertexArrays(1, &r_VAO);
//     Buffers r_vb(r_vertices, vert, sizeof(float), 6, 0);
//     glBindVertexArray(r_VAO);
//     // std::cout<<&VAO1<<std::endl;
//     r_vb.Bind();
//     glBindVertexArray(0);
}

Renderer::~Renderer()
{

}

void Renderer::Draw(GLuint shaderPro)
{
    // glUseProgram(shaderPro);
    // glBindVertexArray(r_VAO);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
}