#version 330

in vec4 fragVertexPosition;
out vec4 finalColor;

uniform samplerCube tex;

void main()
{
    finalColor = texture(tex,  fragVertexPosition.xyz);
}
