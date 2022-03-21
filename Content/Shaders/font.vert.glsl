#version 400

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 wTexCoord;

uniform mat3 transform;

void main()
{
	vec2 screenPos = (transform * vec3(position, 1.0)).xy;
	float depth = -1.0;
	gl_Position = vec4(screenPos, depth, 1.0);
	wTexCoord = texCoord;
}