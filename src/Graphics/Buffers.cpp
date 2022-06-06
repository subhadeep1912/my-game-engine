#include "Buffers.h"

Buffers::Buffers(float* vertices, int vert, size_t sizeElement, int numEle, int layout, size_t size_ielement, int num_iele, int* indices):c_vertices(vertices), c_vert(vert), c_size(sizeElement), c_numEle(numEle), c_layout(layout), c_isize(size_ielement), c_inumEle(num_iele), c_indices(indices)
{
    // std::cout<<"Bruh"<<std::endl; 
    glGenBuffers(1, &c_VBO);
    glGenBuffers(1, &c_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, c_VBO);
    glBufferData(GL_ARRAY_BUFFER, c_size*c_numEle,c_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, c_isize*c_inumEle, c_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, vert, GL_FLOAT, GL_FALSE, vert*sizeof(float), (void*)0);
    glEnableVertexAttribArray(c_layout);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
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