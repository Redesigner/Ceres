#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 wNormal;
out vec4 wPosition;
out vec4 wLightPos;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec3 lightPos;


void main()
{
    wPosition = model * vec4(position, 1.0);

    gl_Position = viewProjection * wPosition;

    wNormal = normalize((model * vec4(normal, 0.0))).xyz;
    wLightPos = vec4(lightPos, 1.0);
}