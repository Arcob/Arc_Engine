#version 330

//uniform mat4 projection;
//uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 vertTexCoord;
layout(location = 2) in vec3 normal;

//layout(location = 3) out vec4 GBufferMap;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 FragNormal;
out vec4 FragPosLightSpace;

out vec3 gFragPos;
out vec3 gNormal;

void main() {
    // Pass the tex coord straight through to the fragment shader
    
    gl_Position = projection * view * model * vec4(vert, 1);
    FragPos = vec3(model * vec4(vert, 1.0)); // 在世界坐标系中指定片元位置

    TexCoord = vertTexCoord;
    mat3 normalMatrix = mat3(transpose(inverse(model)));
	FragNormal = normalMatrix * normal; // 计算法向量经过模型变换后值
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

    gFragPos = vec4(view * model * vec4(vert, 1)).xyz;
    gNormal = transpose(inverse(mat3(view * model))) * normal;
}