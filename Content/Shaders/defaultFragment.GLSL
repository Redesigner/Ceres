#version 400

in vec3 fNormal;
in vec4 fPosition;
in vec4 fLightPos;

out vec4 FragColor;

void main()
{
    vec3 viewPos = vec3(0.0, 0.0, 0.0);
    vec3 color = vec3(0.0, 0.0, 1.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    float diffStrength = 0.6;
    float specularStrength = 0.2;
    float ambientStrength = 0.2;

    vec3 lightDir = normalize(fLightPos.xyz - fPosition.xyz);
    vec3 viewDir = normalize(viewPos - fPosition.xyz);
    vec3 reflectDir = reflect(-lightDir, fNormal);  

    float diff = max(dot(fNormal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = diffStrength * diff * lightColor;
    vec3 specular = specularStrength * spec * lightColor;

    // FragColor = vec4(color * (ambient + diffuse + specular), 1.0);
    FragColor = vec4(diff, spec, 0.0, 1.0);
}