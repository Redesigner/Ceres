#version 400

in vec4 wNormal;
in vec4 wPosition;
in vec3 wColor;
in vec4 wLightPos;

out vec4 FragColor;

uniform samplerCube lightmap;
uniform vec3 cameraPos;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 wNormalF = normalize(wNormal).xyz;

    float diffStrength = 0.6;
    float specularStrength = 0.8;
    float ambientStrength = 0.3;

    vec3 lightDir = normalize(wLightPos.xyz - wPosition.xyz);
    vec3 viewDir = normalize(wPosition.xyz - cameraPos);
    vec3 reflectDir = reflect(lightDir, wNormalF);

    float diff = clamp( dot(wNormalF, lightDir), 0.0, 1.0 );
    float spec = pow(
        clamp(dot(viewDir, reflectDir), 0.0, 1.0) * ceil(diff), 
        32);

    vec3 ambient = ambientStrength * texture(lightmap, wNormalF).xyz;
    vec3 diffuse = diffStrength * diff * lightColor;
    vec3 specular = specularStrength * spec * lightColor;

    FragColor = vec4(wColor * (ambient + diffuse + specular), 1.0);
}