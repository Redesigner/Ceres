#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

out vec4 wNormal;
out vec3 wPosition;
out vec3 wColor;
out vec4 wLightPos;
out vec4 lFragPos;

uniform mat4 model;
uniform mat4 viewProjection;
uniform mat4 lightSpace;
uniform vec3 lightPos;


void main()
{
    wPosition = (model * vec4(position, 1.0)).xyz;
    gl_Position = viewProjection * vec4(wPosition, 1.0);
    wColor = color;
    wNormal = (model * vec4(normal, 0.0));
    wLightPos = vec4(lightPos, 1.0);
    lFragPos = lightSpace * vec4(wPosition, 1.0);
}