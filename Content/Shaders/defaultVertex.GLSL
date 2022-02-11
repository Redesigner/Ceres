#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

out vec4 wNormal;
out vec4 wPosition;
out vec3 wColor;
out vec4 wLightPos;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec3 lightPos;


void main()
{
    wPosition = model * vec4(position, 1.0);
    gl_Position = viewProjection * wPosition;
    wColor = color;
    wNormal = (model * vec4(normal, 0.0));
    wLightPos = vec4(lightPos, 1.0);
}