#version 330

uniform sampler2D U_MainTexture;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;

out vec4 finalColor;

// 光源属性结构体
struct LightAttr
{
	vec3 direction;	// 方向光源
	vec3 ambient;
	vec3 diffuse;
};

uniform LightAttr light;
uniform vec3 viewPos;

void main() {
    /*vec3	ambient = light.ambient * vec3(texture(material.diffuseMap, TextCoord));

	// 漫反射光成分 此时需要光线方向为指向光源
    vec3	lightDir = normalize(-light.direction);	// 翻转方向光源的方向
	vec3	normal = normalize(FragNormal);
	float	diffFactor = max(dot(lightDir, normal), 0.0);
	vec3	diffuse = diffFactor * light.diffuse * vec3(texture(material.diffuseMap, TextCoord));

    // 镜面反射成分 此时需要光线方向为由光源指出
	float	specularStrength = 0.5f;
	vec3	reflectDir = normalize(reflect(-lightDir, normal));
	vec3	viewDir = normalize(viewPos - FragPos);
	float	specFactor = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3	specular = specFactor * light.specular * vec3(texture(material.specularMap, TextCoord));

	vec3	result = ambient + diffuse + specular;
	finalColor	= vec4(result , 1.0f);*/

	vec3	ambient = light.ambient;

	// 漫反射光成分 此时需要光线方向为指向光源
    vec3	lightDir = normalize(-light.direction);	// 翻转方向光源的方向
	vec3	normal = normalize(FragNormal);
	float	diffFactor = max(dot(lightDir, normal), 0.0);
	vec3	diffuse = diffFactor * light.diffuse;

	vec4 albedo = texture(U_MainTexture, TexCoord);

	vec3	result = ambient + diffuse;
	finalColor	= vec4(result , 1.0f) * albedo;

    //finalColor = texture(U_MainTexture, TexCoord);
    //finalColor = vec4(fragTexCoord,0,1.0);
}
