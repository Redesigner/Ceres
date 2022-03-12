#version 400

in vec2 wTexCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, wTexCoord);
}