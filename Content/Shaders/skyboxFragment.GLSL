#version 400

in vec4 wPosition;
in vec3 wTexCoords;

out vec4 FragColor;

uniform samplerCube skyboxSampler;

void main()
{
    FragColor = texture(skyboxSampler, wTexCoords);
}