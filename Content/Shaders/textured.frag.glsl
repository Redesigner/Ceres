#version 400

in vec4 wNormal;
in vec3 wPosition;
in vec4 wLightPos;
in vec4 lFragPos;

in vec2 wTexCoord;

out vec4 FragColor;

uniform samplerCube lightmap;
uniform sampler2D shadowmap;
uniform sampler2D surfaceTexture;
uniform vec3 cameraPos;

float Shadow(vec4 fragPos)
{
    vec3 lightDir = normalize(wLightPos.xyz - wPosition);
    vec3 projCoords = fragPos.xyz / fragPos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowmap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
    float bias = max(0.05 * (1.0 - dot(wNormal.xyz, lightDir)), 0.005);  
    float shadow = currentDepth - bias > closestDepth  ? 0.0 : 1.0;

    return shadow;
}

void main()
{
    vec3 color = texture(surfaceTexture, wTexCoord).xyz;
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

    FragColor = vec4(color * (ambient + Shadow(lFragPos) * (diffuse + specular)), 1.0);
}