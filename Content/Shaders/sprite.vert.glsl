#version 400

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 wTexCoord;

uniform mat3 transform;

void main()
{
	gl_Position = vec4(transform * vec3(position, -1.0), 1.0);
	wTexCoord = texCoord;
}