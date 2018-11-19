#version 400 

// Blinn-Phong Lighting comes from Blinn's 1977 paper "Models of Light Reflection for Computer Synthesized Pictures"
// Link: https://design.osu.edu/carlson/history/PDFs/blinn-light.pdf

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec4 vertexColor;

out vec4 fragmentColor;

uniform InputMaterial {
    vec4 matDiffuse;
    vec4 matSpecular;
    float matShininess;
    vec4 matAmbient;
} material;

struct LightProperties {
    vec4 diffuseColor;
    vec4 specularColor;
};
uniform LightProperties genericLight;

struct PointLight {
    vec4 pointPosition;
};
uniform PointLight pointLight;

uniform vec4 cameraPosition;

uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;

uniform int lightingType;

vec4 pointLightSubroutine(vec4 worldPosition, vec3 worldNormal)
{
    // Normal to the surface
    vec4 N = vec4(normalize(worldNormal), 0.f);
    
    // Direction from the surface to the light
    vec4 L = normalize(pointLight.pointPosition - worldPosition);

    // Direction from the surface to the eye
    vec4 E = normalize(cameraPosition - worldPosition);

    // Direction of maximum highlights (see paper!)
    vec4 H = normalize(L + E);

    // Amount of diffuse reflection
    float d = max(0, dot(N, L));
    vec4 diffuseColor = d * genericLight.diffuseColor * material.matDiffuse;
    
    // Amount of specular reflection
    float s = pow(max(0, dot(N, H)), material.matShininess);
    vec4 specularColor = s * genericLight.specularColor * material.matSpecular;

    return diffuseColor + specularColor;
}

vec4 globalLightSubroutine(vec4 worldPosition, vec3 worldNormal)
{
    return material.matAmbient;
}

vec4 AttenuateLight(vec4 originalColor, vec4 worldPosition)
{
    float lightDistance = length(pointLight.pointPosition - worldPosition);
    float attenuation = 1.0 / (constantAttenuation + lightDistance * linearAttenuation + lightDistance * lightDistance * quadraticAttenuation);
    return originalColor * attenuation;
}

void main()
{
    vec4 vertexWorldPosition =  modelMatrix * vertexPosition;
    vec3 vertexWorldNormal = transpose(inverse(mat3(modelMatrix))) * vertexNormal;
    gl_Position = projectionMatrix * viewMatrix * vertexWorldPosition;

    vec4 lightingColor = vec4(0);
    if (lightingType == 0) {
        lightingColor = globalLightSubroutine(vertexWorldPosition, vertexWorldNormal);
    } else if (lightingType == 1) {
        lightingColor = pointLightSubroutine(vertexWorldPosition, vertexWorldNormal);
    }
    fragmentColor = AttenuateLight(lightingColor, vertexWorldPosition) * vertexColor;
}
