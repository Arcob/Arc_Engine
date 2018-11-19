#pragma once

#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include "common/common.h"

/*! \brief Interfaces with the underlying GLSL shader program.
 *
 *  This class wil manage the GLSL shader program from loading and compiling to setting
 *  runtime variables. The shader interfaces closely with the underlying shader especially in
 *  ShaderProgram::SetupShaderLighting(), ShaderProgram::SetupShaderMaterials(), and ShaderProgram::SetupShaderCamera().
 *  This class (and its subclasses) will directly correspond to a shader program (vertex shader plus
 *  a fragment shader). So if you ever decide to create a new type of shader (not the provided
 *  Blinn-Phong one), you will have to create a new sub-class of ShaderProgram to make sure
 *  that its uniforms are setup properly.
 */
class ShaderProgram
{
public:
    /*! \brief Creates a shader program.
     *  \param inputShaders A map of the shader type to the shader file location. 
     *  
     *  At the minimum a vertex shader is required to create a GLSL shader program; however, using a fragment
     *  shader is highly recommended unless you know what you are doing. 
     */
    ShaderProgram(const std::unordered_map<GLenum, std::string>& inputShaders);

    virtual void LoadMaterialFromAssimp(std::shared_ptr<struct aiMaterial> assimpMaterial) {}
    
    /*! \brief A destructor to clean up the shader program.
     */
    virtual ~ShaderProgram();

    /*! \brief Notifies the OpenGL state that we will be using the underlying GLSL program.
     *
     *  If the shader program failed to compile or link (and you still manage to get to this function call),
     *  StartUseShader() will do nothing.
     */
    virtual void StartUseShader() const;

    /*! \brief Tells the OpenGL state to no longer us the underlying shader.
     */
    virtual void StopUseShader() const;

    /*! \brief Gets the underlying shader program identifier created by <a href="https://www.opengl.org/sdk/docs/man/html/glCreateProgram.xhtml">glCreateProgram</a>.
     *  \return The shader program identifier created by <a href="https://www.opengl.org/sdk/docs/man/html/glCreateProgram.xhtml">glCreateProgram</a>.
     */
    GLuint GetProgram() const { return shaderProgram; }

    /*! \brief This function will pass to the GLSL shader the variables needed by the shader to accurately shade the model using the given light.
     *  \param light The light we want to use for shading. This should not be a null pointer.
     */
    virtual void SetupShaderLighting(const class Light* light) const;

    /*! \brief Sets up the shader material (what this material is depends on the shader).
     *
     *  This functions is meant to be a general setup function for the shader. This function has no access to the scene or anything else stored 
     *  in the application so its primary purpose is to work with objects stored within the shader program object (i.e. textures).
     */
    virtual void SetupShaderMaterials() const;

    /*! \brief Passes camera parameters to the shader if necessary.
     *  \param camera The camera we want to use for shading. This should not be a null pointer.
     */
    virtual void SetupShaderCamera(const class Camera* camera) const;

    /*! \brief Sets a shader uniform with a mat4x4 value.
     *  \param location The name of the uniform variable in the shader.
     *  \param value The value to pass to the shader.
     */
    void SetShaderUniform(const std::string& location, const glm::mat4& value) const;

    /*! \brief Sets a shader uniform with a float value.
     *  \param location The name of the uniform variable in the shader.
     *  \param value The value to pass to the shader.
     *  \warning A value of type double will be implicity cast to a float. If you ever need to pass a double to the shader, make sure to add 
     *  a function overload for double!
     */
    void SetShaderUniform(const std::string& location, float value) const;

    /*! \brief Sets a shader uniform with a int value.
     *  \param location The name of the uniform variable in the shader.
     *  \param value The value to pass to the shader.
     */
    void SetShaderUniform(const std::string& location, int value) const;

    /*! \brief Sets a shader uniform with a vec4 value.
     *  \param location The name of the uniform variable in the shader.
     *  \param value The value to pass to the shader.
     */
    void SetShaderUniform(const std::string& location, const glm::vec4& value) const;

    /*! \brief Sets a shader subroutine variable to point to the desired subroutine.
     *  \param location The name of the uniform variable in the shader.
     *  \param subroutine The name of the subroutine function in the shader.
     *  \param substage The stage of the shader program that the subroutine is in (i.e. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
     *  \warning Subroutines are broken on Mac OSX with a NVIDIA graphics card.
     * 
     *  You can read more about shader subroutines <a href="https://www.opengl.org/wiki/Shader_Subroutine">here</a> or in Chapter 2 of the OpenGL Programming Guide.
     */
    void SetShaderSubroutine(const std::string& location, const std::string& subroutine, GLenum substage) const;

    /*! \brief Sets up a shader uniform block with N variables.
     *  \param blockName The name of the uniform block in the shader.
     *  \param names The names of the variables within the uniform block.
     *  \param indices The indices of the variable within the uniform block.
     *  \param offsets The offset (number of bytes) into memory for the data that we pass to the buffer that is linked to the uniform block for each variable.
     *  \param blockLocation The uniform location of the uniform block.
     *  \param blockSize The number of bytes allocated for the uniform block. 
     *  \param bufferLocation The buffer object name generated by <a href="https://www.opengl.org/sdk/docs/man/html/glGenBuffers.xhtml">glGenBuffers</a>.
     * 
     *  You can read more about uniform blocks (uniform buffer objects) 
     *  <a href="https://www.packtpub.com/books/content/opengl-40-using-uniform-blocks-and-uniform-buffer-objects">here</a>.
     */
    template<int N>
    void SetupUniformBlock(const std::string& blockName,
        std::array<const char*, N>& names, 
        std::array<GLuint, N>& indices,
        std::array<GLint, N>& offsets,
        std::vector<GLubyte>& data,
        GLuint& blockLocation, GLint& blockSize, GLuint& bufferLocation)
    {
        StartUseShader();

        blockLocation = OGL_CALL(glGetUniformBlockIndex(shaderProgram, blockName.c_str()));
        if (blockLocation == GL_INVALID_INDEX) {
            return;
        }

        OGL_CALL(glGetActiveUniformBlockiv(shaderProgram, blockLocation, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize));
        data.resize(blockSize);

        OGL_CALL(glGetUniformIndices(shaderProgram, N, names.data(), indices.data()));
        OGL_CALL(glGetActiveUniformsiv(shaderProgram, N, indices.data(), GL_UNIFORM_OFFSET, offsets.data()));

        OGL_CALL(glGenBuffers(1, &bufferLocation));

        StopUseShader();  
    }

    virtual bool IsAffectedByLight(const class Light* light) const { return true;  }
protected:
    /*! \brief Reads in a shader object and returns the OpenGL shader object name.
     *  \param type Is the same as the shaderType paramter in <a href="https://www.opengl.org/sdk/docs/man/html/glCreateShader.xhtml">glCreateShader</a>.
     *  \param filename The filename to load the shader from. Note that the base directory of shaders is defined in SHADER_PATH 
     *  which is set in the configuration step with CMake.
     *  \returns The OpenGL shader object name.
     */
    static GLuint LoadShaderObject(GLenum type, const std::string& filename);

    GLuint shaderProgram;
private:
    std::unordered_map<GLenum, GLuint> shaderObjects;

    const static int SHADER_ERROR_LOG_SIZE = 500;
};

#endif
