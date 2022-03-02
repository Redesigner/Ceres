#version 400

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 lightspace;

void main()
{
    gl_Position = lightspace * model * vec4(position, 1.0);
}