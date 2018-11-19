#version 330

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
out vec4 vertexWorldPosition;
out vec3 vertexWorldNormal;

void main()
{
    vertexWorldPosition =  modelMatrix * vertexPosition;
    vertexWorldNormal = normalize(vec3(transpose(inverse(modelMatrix)) * vec4(vertexNormal, 0)));
    gl_Position = projectionMatrix * viewMatrix * vertexWorldPosition;
    fragmentColor = vertexColor;
}
