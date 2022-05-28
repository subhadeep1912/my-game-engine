#include "Buffers.h"

Buffers::Buffers(float* vertices, int vert, size_t sizeElement, int numEle, int layout):c_vertices(vertices), c_vert(vert), c_size(sizeElement), c_numEle(numEle), c_layout(layout)
{
    // std::cout<<"Bruh"<<std::endl; 
    glGenBuffers(1, &c_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, c_VBO);
    // std::cout<<"Bruh1"<<std::endl; 
    // std::cout<<vertices<<std::endl;
    // std::cout<<&c_VBO<<std::endl;

    glBufferData(GL_ARRAY_BUFFER, c_size*c_numEle,c_vertices, GL_STATIC_DRAW);
    // std::cout<<8*c_numEle<<std::endl;
    

    glEnableVertexAttribArray(c_layout);
    glVertexAttribPointer(0, vert, GL_FLOAT, GL_FALSE, vert*sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // std::cout<<c_vert*sizeof(float)<<std::endl;
    
}

Buffers::~Buffers()
{

}


void Buffers::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, c_VBO);
}

void Buffers::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}