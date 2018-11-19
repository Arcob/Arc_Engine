#include "common/Rendering/Shaders/CubeMapShader.h"
#include "common/Rendering/Textures/CubeMapTexture.h"

CubeMapShader::CubeMapShader(const std::unordered_map<GLenum, std::string>& inputShaders, std::shared_ptr<CubeMapTexture> inputTexture):
    ShaderProgram(inputShaders), envMap(inputTexture)
{
}

void CubeMapShader::SetupShaderMaterials() const
{
    assert(envMap);
    envMap->BeginRender(0);

    // While we're here, also setup the textures too.
    SetShaderUniform("tex", 0);
}

bool CubeMapShader::IsAffectedByLight(const class Light* light) const
{
    return (light == nullptr);
}