#version 330
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture; 
uniform sampler2D SSAOMap;

void main()
{ 
    
    float result = 0.0;
    vec2 texelSize = 1.0 / textureSize(SSAOMap, 0);
    //vec2 texelSize = 1.0 / textureSize(screenTexture, 0);
    for (int x = -2; x < 2; ++x) 
    {
        for (int y = -2; y < 2; ++y) 
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            result += texture(SSAOMap, TexCoords + offset).r;
        }
    }
    float occlusion = result / (4.0 * 4.0);

    //FragColor = texture(SSAOMap, TexCoords);
    //FragColor = texture(screenTexture, TexCoords) - texture(SSAOMap, TexCoords);
    FragColor = texture(screenTexture, TexCoords) - vec4(vec3(occlusion), 0);
}
