#version 400

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 fNormal;
out vec4 fPosition;
out vec4 fLightPos;

uniform mat4 model;
uniform mat4 viewProjection;
uniform mat4 view;
uniform vec3 lightPos;


void main()
{
    fPosition = view * model * vec4(vPosition, 1.0);
    gl_Position = viewProjection * model * vec4(vPosition, 1.0);

    fNormal = vNormal;

    fLightPos = view * vec4(lightPos, 1.0);
}