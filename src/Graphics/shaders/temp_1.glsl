#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 PosCol;

out vec4 vertCol;
out vec4 fragCol;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position =projection*view*model*vec4(aPos, 1.0);
   vertCol = vec4(gl_Position);
   // fragCol = vec4(PosCol, 1.0);
}