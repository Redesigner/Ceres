#version 400

in vec3 wNormal;
in vec4 wPosition;
in vec4 vPosition;
in vec4 wLightPos;

out vec4 FragColor;

void main()
{
    vec3 viewPos = vec3(0.0, 0.0, 0.0);
    vec3 color = vec3(0.0, 0.0, 1.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    float diffStrength = 0.6;
    float specularStrength = 0.2;
    float ambientStrength = 0.2;

    vec3 lightDir = normalize(wLightPos.xyz - wPosition.xyz);
    vec3 viewDir = normalize(viewPos - vPosition.xyz);
    vec3 reflectDir = reflect(lightDir, wNormal);  

    float diff = max(dot(wNormal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = diffStrength * diff * lightColor;
    vec3 specular = specularStrength * spec * lightColor;

    FragColor = vec4(color * (ambient + diffuse + specular), 1.0);
}