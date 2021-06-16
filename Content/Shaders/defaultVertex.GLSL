#version 400

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec4 Position;
out vec3 Normal;

uniform mat4 viewProjection;
uniform mat4 model;

void main()
{
    gl_Position = viewProjection * model * vec4(aPos, 1.0);

    Position = model * vec4(aPos, 1.0);
    Normal = aNormal;
}