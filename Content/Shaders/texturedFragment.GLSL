#version 400

in vec4 wNormal;
in vec4 wPosition;
in vec4 wLightPos;

in vec2 wTexCoord;

out vec4 FragColor;

uniform sampler2D texSampler;
uniform vec3 cameraPos;

void main()
{
    vec3 color = texture(texSampler, wTexCoord).xyz;
    // vec3 color = vec3(1.0, 1.0, 1.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 wNormalF = normalize(wNormal).xyz;

    float diffStrength = 0.6;
    float specularStrength = 0.8;
    float ambientStrength = 0.1;

    vec3 lightDir = normalize(wLightPos.xyz - wPosition.xyz);
    vec3 viewDir = normalize(wPosition.xyz - cameraPos);
    vec3 reflectDir = reflect(lightDir, wNormalF);

    float diff = clamp( dot(wNormalF, lightDir), 0.0, 1.0 );
    float spec = pow(
        clamp(dot(viewDir, reflectDir), 0.0, 1.0) * ceil(diff), 
        32);

    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = diffStrength * diff * lightColor;
    vec3 specular = specularStrength * spec * lightColor;

    FragColor = vec4(color * (ambient + diffuse + specular), 1.0);
}