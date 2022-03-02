#version 400

in vec4 wNormal;
in vec3 wPosition;
in vec3 wColor;
in vec4 wLightPos;
in vec4 lFragPos;

out vec4 FragColor;

uniform samplerCube lightmap;
uniform sampler2D shadowmap;
uniform vec3 cameraPos;

float Shadow(vec4 fragPos)
{
    const float biasFactor = 0.000025;
    vec3 lightDir = normalize(wLightPos.xyz - wPosition);
    vec3 projCoords = fragPos.xyz / fragPos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float depth = texture(shadowmap, projCoords.xy).r; 
    float fragDepth = projCoords.z;
    float bias = dot(wNormal.xyz, lightDir) * biasFactor;  
    float shadow = fragDepth - bias <= depth  ? 1.0 : 0.0;

    const int pcfSampleWidth = 1;
    const int pcfSampleCount = (pcfSampleWidth * 2 + 1);
    vec2 texelSize = 1.0 / textureSize(shadowmap, 0);
    for(int x = -pcfSampleWidth; x <= pcfSampleWidth; ++x)
    {
        for(int y = -pcfSampleWidth; y <= pcfSampleWidth; ++y)
        {
            float pcfDepth = texture(shadowmap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += fragDepth - bias <= pcfDepth ? 1.0 : 0.0; 
        }
    }
    shadow /= pcfSampleCount;

    return clamp(shadow, 0.0, 1.0);
}

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 wNormalF = normalize(wNormal).xyz;

    float diffStrength = 0.5;
    float specularStrength = 0.1;
    float ambientStrength = 0.4;

    vec3 lightDir = normalize(wLightPos.xyz - wPosition.xyz);
    vec3 viewDir = normalize(wPosition.xyz - cameraPos);
    vec3 reflectDir = reflect(lightDir, wNormalF);

    float diff = clamp( dot(wNormalF, lightDir), 0.0, 1.0 );
    float spec = clamp( pow(
        clamp(dot(viewDir, reflectDir), 0.0, 1.0) * ceil(diff), 
        32), 0.0, 1.0);

    vec3 ambient = texture(lightmap, wNormalF).xyz *    ambientStrength;
    vec3 diffuse = diff * lightColor *                  diffStrength;
    vec3 specular = spec * lightColor *                 specularStrength;

    FragColor = vec4(wColor * (ambient + (Shadow(lFragPos) * (diffuse + specular))), 1.0);
}