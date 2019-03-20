#version 330
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture; 
uniform sampler2D gbufferTexture; //法线在切线空间下
uniform sampler2D texNoise;
uniform sampler2D positionTexture;  //位置在世界空间下,深度在摄像机空间下

uniform vec3 samples[64];
 
// parameters (you'd probably want to use them as uniforms to more easily tweak the effect)
int kernelSize = 64;
float radius = 1.0;
 
// tile noise texture over screen based on screen dimensions divided by noise size
const vec2 noiseScale = vec2(1024.0f/4.0f, 1024.0f/4.0f); 
 
uniform mat4 projection;

void main()
{
    
    // Get input for SSAO algorithm
    vec3 fragPos = texture(positionTexture, TexCoords).xyz;
    vec3 normal = texture(gbufferTexture, TexCoords).rgb;
    vec3 randomVec = texture(texNoise, TexCoords * noiseScale).xyz;
    // Create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    // Iterate over the sample kernel and calculate occlusion factor
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; ++i)
    {
        // get sample position
        vec3 sample = TBN * samples[i]; // From tangent to view-space
        sample = fragPos + sample * radius; 
        
        // project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(sample, 1.0);
        offset = projection * offset; // from view to clip-space
        offset.xyz /= offset.w; // perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0
        
        // get sample depth
        float sampleDepth = -texture(positionTexture, offset.xy).w; // Get depth value of kernel sample
        
        // range check & accumulate
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth ));
        occlusion += (sampleDepth >= sample.z ? 1.0 : 0.0) * rangeCheck;     
        //occlusion += (sampleDepth >= sample.z ? 1.0 : 0.0);      
    }
    occlusion = (occlusion / kernelSize);
    
    //FragColor = vec4(vec3(occlusion),1) ;
    //FragColor = texture(positionTexture, TexCoords);
    //FragColor = vec4(vec3(texture(positionTexture, TexCoords).w),1) ;
    FragColor = texture(screenTexture, TexCoords) - vec4(vec3(occlusion),1);
}

/*void main()
{ 
    vec4 aaColor = texture(screenTexture, TexCoords);
    float depth = texture(screenTexture, TexCoords).a;
    vec2 texelSize = 1.0 / textureSize(screenTexture, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            aaColor += texture(screenTexture, TexCoords + vec2(x, y) * texelSize);
        }    
    }
    aaColor /= 9.0;
    vec4 tempColor = texture(screenTexture, TexCoords);
    //FragColor = vec4(vec3(texture(screenTexture, TexCoords).a),1.0);
    //FragColor = aaColor;
    FragColor = texture(screenTexture, TexCoords);
}*/
