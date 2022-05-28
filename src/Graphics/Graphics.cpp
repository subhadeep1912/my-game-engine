#include "Graphics.hpp"
 
GraphicsPipe::GraphicsPipe()
{
    ;
}

GraphicsPipe::~GraphicsPipe()
{
    ;
}


// void GraphicsPipe::MakeBuffer(GLuint VBO, float* vertices, int vert)
// {
//     // GLuint VBO;
//     glGenBuffers(1, &VBO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, vert, GL_FLOAT, GL_FALSE, vert*sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);

// }
 