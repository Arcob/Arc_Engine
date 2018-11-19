#version 330

in vec4 vertexWorldPosition;
in vec3 vertexWorldNormal;
in vec2 fragmentUV;
in vec3 vertexWorldTangent;
in vec3 vertexWorldBitangent;

out vec4 finalColor;

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

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform sampler2D normalTexture;
uniform bool useNormalTexture;


vec4 pointLightSubroutine(vec4 worldPosition, vec3 worldNormal)
{
    mat3 worldToTangentMatrix = inverse(mat3(vertexWorldTangent, vertexWorldBitangent, normalize(worldNormal)));
    // Normal to the surface
    vec3 N = normalize(worldNormal);
    vec3 tangentN = useNormalTexture ? normalize(vec3(texture(normalTexture, fragmentUV)) * 2.f - 1.f) : normalize(worldToTangentMatrix * N);
    
    // Direction from the surface to the light
    vec3 L = normalize(vec3(pointLight.pointPosition - worldPosition));
    vec3 tangentL = normalize(worldToTangentMatrix * L);

    // Direction from the surface to the eye
    vec3 E = normalize(vec3(cameraPosition - worldPosition));
    vec3 tangentE = normalize(worldToTangentMatrix * E);

    // Direction of maximum highlights (see paper!)
    vec3 tangentH = normalize(tangentL + tangentE);

    // Amount of diffuse reflection
    float d = max(0, dot(tangentN, tangentL));
    vec4 diffuseColor = d * genericLight.diffuseColor * material.matDiffuse * texture(diffuseTexture, fragmentUV);
    
    // Amount of specular reflection
    float s = pow(max(0, dot(tangentN, tangentH)), material.matShininess);
    vec4 specularColor = s * genericLight.specularColor * material.matSpecular * texture(specularTexture, fragmentUV);

    return texture(diffuseTexture, fragmentUV);
    return diffuseColor + specularColor;
}

vec4 globalLightSubroutine(vec4 worldPosition, vec3 worldNormal)
{
    return vec4(0);
    return material.matAmbient * texture(diffuseTexture, fragmentUV);
}

vec4 AttenuateLight(vec4 originalColor, vec4 worldPosition)
{
    return originalColor;
    float lightDistance = length(pointLight.pointPosition - worldPosition);
    float attenuation = 1.0 / (constantAttenuation + lightDistance * linearAttenuation + lightDistance * lightDistance * quadraticAttenuation);
    return originalColor * attenuation;
}

void main()
{
    vec4 lightingColor = vec4(0);
    if (lightingType == 0) {
        lightingColor = globalLightSubroutine(vertexWorldPosition, vertexWorldNormal);
    } else if (lightingType == 1) {
        lightingColor = pointLightSubroutine(vertexWorldPosition, vertexWorldNormal);
    }
    finalColor = AttenuateLight(lightingColor, vertexWorldPosition);
}
