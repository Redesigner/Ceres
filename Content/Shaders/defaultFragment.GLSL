#version 400

in vec4 Position;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;

void main()
{
    vec3 color = vec3(0.0, 0.0, 1.0);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightDir = normalize(lightPos - Position.xyz);
    vec3 ambient = 0.2 * lightColor;


    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = color * (ambient + diffuse);

    FragColor = vec4(result, 1.0);
} 