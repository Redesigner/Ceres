#version 400

in vec3 wNormal;
in vec4 wPosition;
in vec3 wColor;
in vec4 wLightPos;

out vec4 FragColor;

uniform vec3 cameraPos;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    float diffStrength = 0.6;
    float specularStrength = 0.8;
    float ambientStrength = 0.2;

    vec3 lightDir = normalize(wLightPos.xyz - wPosition.xyz);
    vec3 viewDir = normalize(wPosition.xyz - cameraPos);
    vec3 reflectDir = reflect(lightDir, wNormal);

    float diff = max( (dot(wNormal, lightDir) ), 0.0);
    float spec = pow(
        clamp(dot(viewDir, reflectDir), 0.0, 1.0) * ceil(diff), 
        16);

    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = diffStrength * diff * lightColor;
    vec3 specular = specularStrength * spec * lightColor;

    FragColor = vec4(wColor * (ambient + diffuse + specular), 1.0);
}