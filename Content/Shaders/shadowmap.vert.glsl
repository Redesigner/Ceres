#version 400

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 lightspace;

void main()
{
    vec3 wPosition = (model * vec4(position, 1.0)).xyz;
    gl_Position = lightspace * vec4(wPosition, 1.0);
}