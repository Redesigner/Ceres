#version 400

in vec3 aPos;
out vec4 vertexColor;

uniform mat4 viewProjection;
uniform mat4 model;

void main()
{
    vec4 pos = vec4(aPos, 1.0);
    gl_Position = viewProjection * model * pos;
    vertexColor = vec4(pos.x + 0.5, 0.5, 0.5, 1.0);
}