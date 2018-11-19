#include "common/Rendering/Shaders/ShaderProgram.h"
#include "common/Scene/Light/Light.h"
#include "common/Scene/Light/LightProperties.h"
#include <fstream>
#include <iterator>

#define VERIFY_SHADER_UNIFORM_EXISTS(program, name, var) \
    GLint var = OGL_CALL(glGetUniformLocation(program, name)); \
    if (var == -1) { \
        return; \
    } \

ShaderProgram::ShaderProgram(const std::unordered_map<GLenum, std::string>& inputShaders):
    shaderProgram(0)
{
    if (inputShaders.find(GL_VERTEX_SHADER) == inputShaders.end())
    {
        std::cerr << "ERROR: Your shader program is either missing a vertex shader which is required." << std::endl;
        return;
    }
    bool hasFragmentShader = inputShaders.find(GL_FRAGMENT_SHADER) != inputShaders.end();
    if (!hasFragmentShader) {
        std::cerr << "WARNING: You did not specify a fragment shader. Although this may be valid, be warned that things may go very wrong!" << std::endl;
        return;
    }

    // Read and setup the vertex and fragment shaders.
    // TODO: Make the shader objects be cached so we don't incur the cost of creating a shader object multiple times if it is being reused.
    shaderObjects[GL_VERTEX_SHADER] = LoadShaderObject(GL_VERTEX_SHADER, inputShaders.at(GL_VERTEX_SHADER));

    if (hasFragmentShader) {
        shaderObjects[GL_FRAGMENT_SHADER] = LoadShaderObject(GL_FRAGMENT_SHADER, inputShaders.at(GL_FRAGMENT_SHADER));
    }

    // Now link the vertex and fragment shader together to create the shader program.
    shaderProgram = OGL_CALL(glCreateProgram());

    OGL_CALL(glAttachShader(shaderProgram, shaderObjects[GL_VERTEX_SHADER]));
    if (hasFragmentShader) {
        OGL_CALL(glAttachShader(shaderProgram, shaderObjects[GL_FRAGMENT_SHADER]));
    }
    OGL_CALL(glLinkProgram(shaderProgram));
    
    // Check if any errors happened during the linker stage.
    GLint linkStatus;
    OGL_CALL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus));
    if (linkStatus != GL_TRUE) {
        char errorLogBuffer[SHADER_ERROR_LOG_SIZE];
        OGL_CALL(glGetProgramInfoLog(shaderProgram, SHADER_ERROR_LOG_SIZE, NULL, errorLogBuffer));
        std::cerr << "ERROR: Program link compilation failure -- " << std::endl << errorLogBuffer << std::endl;
        shaderProgram = 0;
    }

    OGL_CALL(glDetachShader(shaderProgram, shaderObjects[GL_VERTEX_SHADER]));
    OGL_CALL(glDeleteShader(shaderObjects[GL_FRAGMENT_SHADER]));

    if (hasFragmentShader) {
        OGL_CALL(glDetachShader(shaderProgram, shaderObjects[GL_FRAGMENT_SHADER]));
        OGL_CALL(glDeleteShader(shaderObjects[GL_VERTEX_SHADER]));
    }
}

ShaderProgram::~ShaderProgram()
{
    OGL_CALL(glDeleteProgram(shaderProgram));
}

GLuint ShaderProgram::LoadShaderObject(GLenum type, const std::string& filename)
{
#ifndef SHADER_PATH
    static_assert(false, "SHADER_PATH is not defined. Check to make sure your projects are setup correctly");
#endif

    const std::string completeFilename = std::string(STRINGIFY(SHADER_PATH)) + "/" + filename;
    std::ifstream fs(completeFilename, std::ifstream::in);

    if (!fs.is_open()) {
        std::cerr << "ERROR: Could not read shader from " << completeFilename << std::endl;
        return 0;
    }
    
    // This reads in the whole file into an std::string. Google for more information!
    std::string shaderText((std::istreambuf_iterator<char>(fs)), 
        std::istreambuf_iterator<char>());

    GLuint newShaderObject = OGL_CALL(glCreateShader(type));

    // Need to associate the actual shader text we loaded ('shaderText') with the shader we just
    // made so that the driver knows what to compile!
    const char* shaderTextStr = shaderText.c_str();
    OGL_CALL(glShaderSource(newShaderObject, 1, &shaderTextStr, NULL));

    // Compile the shader and make sure compilation passes! Will spit out compilation debugging information if it does not.
    OGL_CALL(glCompileShader(newShaderObject));

    GLint compileStatus;
    OGL_CALL(glGetShaderiv(newShaderObject, GL_COMPILE_STATUS, &compileStatus));
    if (compileStatus != GL_TRUE) {
        char errorLogBuffer[SHADER_ERROR_LOG_SIZE];
        OGL_CALL(glGetShaderInfoLog(newShaderObject, SHADER_ERROR_LOG_SIZE, NULL, errorLogBuffer));
        std::cerr << "ERROR: Shader compilation failure -- " << std::endl << errorLogBuffer << std::endl;
        return 0;
    }

    return newShaderObject;
}

void ShaderProgram::StartUseShader() const
{
    OGL_CALL(glUseProgram(shaderProgram));
}

void ShaderProgram::StopUseShader() const
{
    OGL_CALL(glUseProgram(0));
}

void ShaderProgram::SetShaderUniform(const std::string& location, const glm::mat4& value) const
{
    VERIFY_SHADER_UNIFORM_EXISTS(shaderProgram, location.c_str(), uniformLocation);
    OGL_CALL(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value)));
}

void ShaderProgram::SetShaderUniform(const std::string& location, int value) const
{
    VERIFY_SHADER_UNIFORM_EXISTS(shaderProgram, location.c_str(), uniformLocation);
    OGL_CALL(glUniform1i(uniformLocation, value));
}

void ShaderProgram::SetShaderUniform(const std::string& location, float value) const
{
    VERIFY_SHADER_UNIFORM_EXISTS(shaderProgram, location.c_str(), uniformLocation);
    OGL_CALL(glUniform1f(uniformLocation, value));
}

void ShaderProgram::SetShaderUniform(const std::string& location, const glm::vec4& value) const
{
    VERIFY_SHADER_UNIFORM_EXISTS(shaderProgram, location.c_str(), uniformLocation);
    OGL_CALL(glUniform4fv(uniformLocation, 1, glm::value_ptr(value)));
}

// Currently only supports 1 subroutine per shader...
void ShaderProgram::SetShaderSubroutine(const std::string& location, const std::string& subroutine, GLenum substage) const
{
#ifndef DISABLE_OPENGL_SUBROUTINES
    GLint uniformLocation = OGL_CALL(glGetSubroutineUniformLocation(shaderProgram, substage, location.c_str()));
    if (uniformLocation != 0) {
        return;
    }

    GLuint subroutineIndex = OGL_CALL(glGetSubroutineIndex(shaderProgram, substage, subroutine.c_str()));
    if (subroutineIndex == GL_INVALID_INDEX) {
        return;
    }
    
    OGL_CALL(glUniformSubroutinesuiv(substage, 1, &subroutineIndex));
#else
    assert(false);
    std::cerr << "Subroutines are disabled via the 'DISABLE_OPENGL_SUBROUTINES' macro in common.h. Please undefine that macro to use subroutines. Do note that NVIDIA devices running on Apple do not properly support subroutines." << std::endl;
#endif
}

void ShaderProgram::SetupShaderLighting(const Light* light) const
{
}

void ShaderProgram::SetupShaderMaterials() const
{
}

void ShaderProgram::SetupShaderCamera(const Camera* camera) const
{
}
