#version 330 core
in vec4 vertCol;
out vec4 FragColor;
in vec4 fragCol;

uniform float u_time;
uniform vec4 ourColor; // we set this variable in the OpenGL code.


void main()
{
    vec2 st = gl_FragCoord.xy/vec2(800, 600);
    FragColor = vertCol;
}  