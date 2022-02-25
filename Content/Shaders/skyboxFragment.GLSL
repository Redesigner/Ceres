#version 400

in vec4 wPosition;
in vec3 wTexCoords;

out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, wTexCoords);
}