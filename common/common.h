/*! \file common.h
 *  \brief A file included across the application framework to include common header files and other useful functions and macros.
 */
#pragma once

#ifndef __COMMON__
#define __COMMON__

#ifdef _WIN32
#include "SDL.h"
#undef main
#else
#include "SDL2/SDL.h"
#endif
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

#include "GL/glew.h"

#ifdef __APPLE__
#include "OpenGL/gl.h"
#define DISABLE_OPENGL_SUBROUTINES
#endif

#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <cassert>
#include <unordered_map>

/*! \func _OpenGLErrorToString
 *  \brief Converts an OpenGL error to an std::string.
 *  \param err The OpenGL error returned by <a href="https://www.opengl.org/sdk/docs/man/html/glGetError.xhtml">glGetError</a>.
 *  \returns A string that explain the OpenGL error. These are copied directly from the OpenGL documentation.
 * 
 * This function is called by _DisplayOpenGLError to get a user-friendly message in addition to an errror code.
 */
inline std::string _OpenGLErrorToString(GLenum err) {
    // Error messages copied from the glGetError documentation: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetError.xml
    switch (err) {
    case GL_NO_ERROR:
        return "No Error: No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
    case GL_INVALID_ENUM:
        return "Invalid enum: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag."; 
    case GL_INVALID_VALUE:
        return "Invalid value: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_INVALID_OPERATION:
        return "Invalid operation: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "Invalid framebuffer operation: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_OUT_OF_MEMORY:
        return "Out of memory: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
    case GL_STACK_UNDERFLOW:
        return "Stack Underflow: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
    case GL_STACK_OVERFLOW:
        return "Stack overflow: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
    default:
        break;
    }
    return "Unspecified error";
}

/*! \func _DisplayOpenGLError
 *  \brief Prints a user friendly message for the most recent OpenGL error (if any) to stdout.
 *  \param command The command that was run.
 *  \param file The file from which the command was run.
 *  \param line The line in the file where the command was fun.
 * 
 *  This function is used by the OGL_CALL macro to provide debugging information in stdout when an OpenGL API call fails.
 */

inline void _DisplayOpenGLError(std::string command, std::string file, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << " -- " << _OpenGLErrorToString(err) << std::endl;
        std::cerr << "Relevant Command: " << command << std::endl;
        std::cerr << "Location: " << file << " at Line: " << line << std::endl;
    }
}


/*! \def OGL_CALL
 *  \brief Provides an easy to use macro that wraps around OpenGL calls and checks their error.
 *  \param x The OpenGL command.
 *  
 *  This is only defined in the Debug build when NDEBUG is NOT defined. If you are unfamiliar with C++
 *  preprocess macros, the __FILE__ macro, or the __LINE__ macro, you can read <a href="http://www.cplusplus.com/doc/tutorial/preprocessor/">this</a>
 *  for more information.
 */
#ifndef NDEBUG
#define OGL_CALL(x) x; _DisplayOpenGLError(#x, __FILE__, __LINE__);
#else
#define OGL_CALL(x) x;
#endif

/*! \var PI
 * \brief The PI constant.
 */
const float PI = 3.14159265359f;

/*! \def STRINGIFY_HELPER
 * \brief Help stringify a macro.
 */
#define STRINGIFY_HELPER(x) #x

/*! \def STRINGIFY
 * \brief Stringify a macro.
 * 
 * This takes in a macro that was defined to be a string and actually converts it into a string that can be used by the application. See MeshLoader::LoadMesh for an example.
 * Why is this nested macro necessary? You can read about it here: <a href="https://gcc.gnu.org/onlinedocs/cpp/Stringification.html">link</a>.
 */
#define STRINGIFY(x) STRINGIFY_HELPER(x)

/*! \brief Create a std::unique_ptr much like std::make_shared.
 *
 * To avoid too many compilation problems I stuck with using C++11 where the committee forgot to include std::make_unique (it's there in C++14). This is a convenience function.
 * Curious about Modern C++? The book <a href="http://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996">Effective Modern C++</a> by Scott Meyes is a great
 * book if you are already familiar with C++.
 */
#ifdef _WIN32
#define make_unique std::make_unique
#else
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
#endif

#endif
