#version 330
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture; 
uniform sampler2D SSAOMap;

vec2 u_texelStep = vec2(1.0/1024.0, 1.0/1024.0);
int u_showEdges = 0;
int u_fxaaOn = 1;

float u_lumaThreshold_up = 0.16; //缘变化越明显，则局部差异越大。然后设定一个阈值，如果差值大于阈值则执行抗锯齿操作。这个阈值通常使用最大亮度的 0.15 倍左右
float u_lumaThreshold_down = 0.083;
float u_mulReduce = 1.0 / 8.0;
float u_minReduce = 1.0 / 128.0;
float u_maxSpan = 8.0;

#define FXAA_QUALITY__PS 12 // 迭代次数
#define FXAA_QUALITY__P0 1.0
#define FXAA_QUALITY__P1 1.0
#define FXAA_QUALITY__P2 1.0
#define FXAA_QUALITY__P3 1.0
#define FXAA_QUALITY__P4 1.0
#define FXAA_QUALITY__P5 1.5
#define FXAA_QUALITY__P6 2.0
#define FXAA_QUALITY__P7 2.0
#define FXAA_QUALITY__P8 2.0
#define FXAA_QUALITY__P9 2.0
#define FXAA_QUALITY__P10 4.0
#define FXAA_QUALITY__P11 8.0

float rgb2luma(vec3 rgb) {
    return rgb.g; // 使用官方版本
    //return dot(rgb, vec3(0.2126, 0.7152, 0.0722)); // 最流行的亮度计算
    // return dot(rgb, vec3(0.299, 0.587, 0.114)); // 曾经最流行的方法
    // return sqrt(0.299 * rgb.r * rgb.r + 0.587 * rgb.g * rgb.g + 0.114 * rgb.b * rgb.b); // 更精确的计算
    // return sqrt(dot(rgb, vec3(0.299, 0.587, 0.114))); // 添加了 gamma 校正的计算
}

/*float fxaa_quality(int i){
    retrun i/3;
}

vec4 fxaa(){
    vec3 rgbM = texture(screenTexture, TexCoords).rgb;
    if (u_fxaaOn == 0)
	{
		return vec4(rgbM, 1.0);
	}

    vec2 RcpFrame = 1.0 / textureSize(screenTexture, 0);

    vec3 rgbNW = textureOffset(screenTexture, TexCoords, ivec2(-1, 1)).rgb;
    vec3 rgbNE = textureOffset(screenTexture, TexCoords, ivec2(1, 1)).rgb;
    vec3 rgbSW = textureOffset(screenTexture, TexCoords, ivec2(-1, -1)).rgb;
    vec3 rgbSE = textureOffset(screenTexture, TexCoords, ivec2(1, -1)).rgb;
    vec3 rgbN = textureOffset(screenTexture, TexCoords, ivec2(0, 1)).rgb;
    vec3 rgbS = textureOffset(screenTexture, TexCoords, ivec2(0, -1)).rgb;
    vec3 rgbE = textureOffset(screenTexture, TexCoords, ivec2(1, 0)).rgb;
    vec3 rgbW = textureOffset(screenTexture, TexCoords, ivec2(-1, 0)).rgb;

	// Convert from RGB to luma.
	float lumaNW = rgb2luma(rgbNW);
	float lumaNE = rgb2luma(rgbNE);
	float lumaSW = rgb2luma(rgbSW);
	float lumaSE = rgb2luma(rgbSE);
    float lumaN = rgb2luma(rgbN);
    float lumaS = rgb2luma(rgbS);
    float lumaE = rgb2luma(rgbE);
    float lumaW = rgb2luma(rgbW);
	float lumaM = rgb2luma(rgbM);

    #define fxaaQualityEdgeThreshold 0.166
    // 最低判断阈值
    #define fxaaQualityEdgeThresholdMin 0.0833

    // 计算最大最小亮度
    float maxSM = max(lumaS, lumaM);
    float minSM = min(lumaS, lumaM);
    float maxESM = max(lumaE, maxSM);
    float minESM = min(lumaE, minSM);
    float maxWN = max(lumaN, lumaW);
    float minWN = min(lumaN, lumaW);
    float rangeMax = max(maxWN, maxESM); // 最大亮度
    float rangeMin = min(minWN, minESM); // 最小亮度
    float rangeMaxScaled = rangeMax * u_lumaThreshold_up; // 如果亮度较高，则上阈值生效
    float range = rangeMax - rangeMin;
    float rangeMaxClamped = max(u_lumaThreshold_down, rangeMaxScaled); // 如果亮度较低，则设定的固定下阈值生效
    bool earlyExit = range < rangeMaxClamped;
    if(earlyExit)
        return vec4(rgbM, 1.0); // 返回中心像素

    float lumaNS = lumaN + lumaS;
    float lumaWE = lumaW + lumaE;
    float edgeHorz1 = (-2.0 * lumaM) + lumaNS;
    float edgeVert1 = (-2.0 * lumaM) + lumaWE;
    float lumaNESE = lumaNE + lumaSE;
    float lumaNWNE = lumaNW + lumaNE;
    float edgeHorz2 = (-2.0 * lumaE) + lumaNESE;
    float edgeVert2 = (-2.0 * lumaN) + lumaNWNE;
    float lumaNWSW = lumaNW + lumaSW;
    float lumaSWSE = lumaSW + lumaSE;
    float edgeHorz3 = (-2.0 * lumaW) + lumaNWSW;
    float edgeVert3 = (-2.0 * lumaS) + lumaSWSE;
    // 整合
    float edgeHorz4 = (abs(edgeHorz1) * 2.0) + abs(edgeHorz2);
    float edgeVert4 = (abs(edgeVert1) * 2.0) + abs(edgeVert2);
    float edgeHorz = abs(edgeHorz3) + edgeHorz4;
    float edgeVert = abs(edgeVert3) + edgeVert4;

    bool horzSpan = edgeHorz >= edgeVert;
    float luma1 = horzSpan ? lumaS : lumaW;
    float luma2 = horzSpan ? lumaN : lumaE;
    float lengthSign = horzSpan ? RcpFrame.y : RcpFrame.x; // 记录像素偏移量和方向
    float gradient1 = luma1 - lumaM;
    float gradient2 = luma2 - lumaM;
    bool gradientBigger1 = abs(gradient1) >= abs(gradient2);
    float gradient = max(abs(gradient1), abs(gradient2)); // 这是一个绝对值
    if(gradientBigger1) lengthSign = -lengthSign;

    vec2 posB = TexCoords;
    if(!horzSpan) posB.x += lengthSign * 0.5;
    if( horzSpan) posB.y += lengthSign * 0.5;

    // 计算第一次迭代的位置
    vec2 offNP; // 偏移值记录
    offNP.x = (!horzSpan) ? 0.0 : RcpFrame.x;
    offNP.y = ( horzSpan) ? 0.0 : RcpFrame.y;
    vec2 posN;
    posN.x = posB.x - offNP.x * FXAA_QUALITY__P0;
    posN.y = posB.y - offNP.y * FXAA_QUALITY__P0;
    vec2 posP;
    posP.x = posB.x + offNP.x * FXAA_QUALITY__P0;
    posP.y = posB.y + offNP.y * FXAA_QUALITY__P0;
    // 计算第一次迭代的亮度
    float lumaEndN = rgb2luma(texture(screenTexture, posN).rgb);
    float lumaEndP = rgb2luma(texture(screenTexture, posP).rgb);
    // 比较是否满足跳出条件
    float lumaAverage1 = (luma1 + lumaM) * 0.5f;
    float lumaAverage2 = (luma2 + lumaM) * 0.5f;
    float lumAverage = gradientBigger1 ? lumaAverage1 : lumaAverage2; 
    lumaEndN -= lumAverage;
    lumaEndP -= lumAverage;
    float gradientScaled = gradient * 0.25; // 参考量
    bool doneN = abs(lumaEndN) >= gradientScaled; // 如果偏移得到的亮度在平均亮度周围轻微波动，就可以继续进行迭代，否则跳出
    bool doneP = abs(lumaEndP) >= gradientScaled;
    bool bothDone = doneN && doneP;

    float dstN = posM.x - posN.x;
    float dstP = posP.x - posM.x;
    if(!horzSpan) dstN = posM.y - posN.y;
    if(!horzSpan) dstP = posP.y - posM.y;
    bool goodSpanN = (lumaEndN < 0.0) != lumaMLTZero; // 剔除掉中心像素亮度低的情况
    float spanLength = (dstP + dstN);
    bool goodSpanP = (lumaEndP < 0.0) != lumaMLTZero;
    float spanLengthRcp = 1.0 / spanLength;

    bool directionN = dstN < dstP;
    float dst = min(dstN, dstP);
    bool goodSpan = directionN ? goodSpanN : goodSpanP;
    float pixelOffset = (dst * (-spanLengthRcp)) + 0.5; // 肯定大于0
    }

    return vec4(rgbM, 1.0);
}*/

vec4 fxaa()
{
    vec3 rgbM = texture(screenTexture, TexCoords).rgb;
    if (u_fxaaOn == 0)
	{
		return vec4(rgbM, 1.0);
	}

    vec3 rgbNW = textureOffset(screenTexture, TexCoords, ivec2(-1, 1)).rgb;
    vec3 rgbNE = textureOffset(screenTexture, TexCoords, ivec2(1, 1)).rgb;
    vec3 rgbSW = textureOffset(screenTexture, TexCoords, ivec2(-1, -1)).rgb;
    vec3 rgbSE = textureOffset(screenTexture, TexCoords, ivec2(1, -1)).rgb;


	// Convert from RGB to luma.
	float lumaNW = rgb2luma(rgbNW);
	float lumaNE = rgb2luma(rgbNE);
	float lumaSW = rgb2luma(rgbSW);
	float lumaSE = rgb2luma(rgbSE);
	float lumaM = rgb2luma(rgbM);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    float rangeMaxScale = lumaMax * u_lumaThreshold_up;
    float range = lumaMax - lumaMin;
    float rangeMaxClamped = max(u_lumaThreshold_down, rangeMaxScale);
    bool earlyExit = (range < rangeMaxClamped);
    if (earlyExit){
        return vec4(rgbM, 1.0); // 返回中心像素
    }

    vec2 samplingDirection;	
	samplingDirection.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    samplingDirection.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
    // Sampling step distance depends on the luma: The brighter the sampled texels, the smaller the final sampling step direction.
    // This results, that brighter areas are less blurred/more sharper than dark areas.  
    float samplingDirectionReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * 0.25 * u_mulReduce, u_minReduce);

	// Factor for norming the sampling direction plus adding the brightness influence. 
	float minSamplingDirectionFactor = 1.0 / (min(abs(samplingDirection.x), abs(samplingDirection.y)) + samplingDirectionReduce);

    // Calculate final sampling direction vector by reducing, clamping to a range and finally adapting to the texture size. 
    samplingDirection = clamp(samplingDirection * minSamplingDirectionFactor, vec2(-u_maxSpan), vec2(u_maxSpan)) * u_texelStep;

    vec3 rgbSampleNeg = texture(screenTexture, TexCoords + samplingDirection * (1.0/3.0 - 0.5)).rgb;
	vec3 rgbSamplePos = texture(screenTexture, TexCoords + samplingDirection * (2.0/3.0 - 0.5)).rgb;

	vec3 rgbTwoTab = (rgbSamplePos + rgbSampleNeg) * 0.5;  

	// Outer samples on the tab.
	vec3 rgbSampleNegOuter = texture(screenTexture, TexCoords + samplingDirection * (0.0/3.0 - 0.5)).rgb;
	vec3 rgbSamplePosOuter = texture(screenTexture, TexCoords + samplingDirection * (3.0/3.0 - 0.5)).rgb;
	
	vec3 rgbFourTab = (rgbSamplePosOuter + rgbSampleNegOuter) * 0.25 + rgbTwoTab * 0.5;   
	
	// Calculate luma for checking against the minimum and maximum value.
	float lumaFourTab = rgb2luma(rgbFourTab);

    vec4 result = vec4(rgbM, 1.0);
    if (lumaFourTab < lumaMin || lumaFourTab > lumaMax)
	{
		// ... yes, so use only two samples.
		result = vec4(rgbTwoTab, 1.0); 
	}
	else
	{
		// ... no, so use four samples. 
		result = vec4(rgbFourTab, 1.0);
	}

	// Show edges for debug purposes.	
	if (u_showEdges != 0)
	{
		result.r = 1.0;
	}

    return result;
}

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
    FragColor = fxaa() - vec4(vec3(occlusion * 0.8), 0);
    //FragColor = texture(screenTexture, TexCoords) - texture(SSAOMap, TexCoords);
    //FragColor = texture(screenTexture, TexCoords) - vec4(vec3(occlusion * 0.5), 0);
}
