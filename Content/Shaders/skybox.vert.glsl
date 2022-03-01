#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texCoords;

out vec4 wPosition;
out vec3 wTexCoords;

uniform mat4 model;
uniform mat4 viewProjection;


void main()
{
    wPosition = vec4(position, 1.0);
    wTexCoords = texCoords;
    gl_Position = viewProjection * wPosition;
}