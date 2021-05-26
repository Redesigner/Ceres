#version 400
layout (location = 0)

in vec3 aPos;
out vec4 vertexColor;

uniform mat4 projection;

void main()
{
    vec4 pos = vec4(aPos, 1.0);
    gl_Position = projection * pos;
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}