#pragma once

#include "common/Rendering/Shaders/ShaderProgram.h"

class CubeMapShader : public ShaderProgram
{
public:
    CubeMapShader(const std::unordered_map<GLenum, std::string>& inputShaders, std::shared_ptr<class CubeMapTexture> inputTexture);
    virtual void SetupShaderMaterials() const;

    virtual bool IsAffectedByLight(const class Light* light) const;
private:
    std::shared_ptr<class CubeMapTexture> envMap;
};