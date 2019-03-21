#version 330

uniform sampler2D U_MainTexture;
uniform sampler2D ShadowMap;

uniform bool EnableShadow;
//uniform sampler2D GBufferMap;


in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;
in vec4 FragPosLightSpace;

in vec3 gFragPos;
in vec3 gNormal;

layout(location = 0) out vec4 finalColor;
layout(location = 1) out vec4 GBufferMap;
layout(location = 2) out vec4 positionMap;

// 光源属性结构体
struct LightAttr
{
	vec3 direction;	// 方向光源
	vec3 ambient;
	vec3 diffuse;
};

const float NEAR = 0.3; // 投影矩阵的近平面
const float FAR = 100; // 投影矩阵的远平面

//const float NEAR = 0.3; // 投影矩阵的近平面
//const float FAR = 100; // 投影矩阵的远平面
uniform LightAttr light;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace, float bias)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(ShadowMap, projCoords.xy).r; 
    // 取得当前片元在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片元是否在阴影中
    //float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(ShadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(ShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            // 检查当前片元是否在阴影中
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // 回到NDC
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));    
}

void main() {
	vec3	ambient = light.ambient;
    float bias = max(0.0005 * (1.0 - dot(FragNormal, light.direction)), 0.00005);
    //float bias = 0;
	

	// 漫反射光成分 此时需要光线方向为指向光源
    vec3	lightDir = normalize(-light.direction);	// 翻转方向光源的方向
	vec3	normal = normalize(FragNormal);
	float	diffFactor = max(dot(lightDir, normal), 0.0);
	vec3	diffuse = diffFactor * light.diffuse;
    GBufferMap = vec4(normalize(gNormal),1);
    //GBufferMap = vec4(gNormal,1);
    positionMap = vec4(gFragPos,  LinearizeDepth(gl_FragCoord.z));
    //positionMap = vec4(gFragPos,  gl_FragCoord.z);
	vec4 albedo = texture(U_MainTexture, TexCoord);

    vec3 result = ambient;
    if (EnableShadow){
        float shadow = ShadowCalculation(FragPosLightSpace, bias);  
	    result += (1.0 - shadow) * diffuse;
    }else{
        result += diffuse;
    }
    
	finalColor	= vec4(result ,1) * albedo; //gl_FragCoord.z是片元的深度信息，将深度信息写入到颜色的alpha通道里
    //finalColor	= vec4(vec3(gl_FragCoord.z),1.0f);

}

