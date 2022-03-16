#version 400

in vec2 wTexCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	vec4 fontColor = vec4(0.0, 0.0, 0.0, 1.0);
	FragColor = texture(tex, wTexCoord).x * fontColor;
}