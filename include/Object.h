#pragma once
#include "Buffers.h"
#include "Shaders.h"
#include "Physics.h"

class Object
{
private:
    Buffers b();
    Shader s();
    Physics p();           
public:
    Object();
    ~Object();
};   