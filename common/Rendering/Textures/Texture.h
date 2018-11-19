#pragma once

#ifndef __TEXTURE__
#define __TEXTURE__

#include "common/common.h"

/*! \brief Stores the assignment framework's representation of a texture and allows reuse of the underlying OpenGL texture.
 *
 *  Note that this class does not handle loading the texture. To see how a texture is loaded, look at TextureLoader::LoadTexture().
 */
class Texture: public std::enable_shared_from_this<Texture>
{
public:

    Texture(GLenum inputTarget);

    /*! \brief Destructor.
     */
    virtual ~Texture();
    
    /*! \brief Binds the texture to a texture unit and sets the target as GL_TEXTURE_2D.
     *  \param unit The texture unit to bind to.
     */
    virtual void BeginRender(int unit) const;

    /*! \brief Unbinds the texture.
     */
    virtual void EndRender() const;

protected:
    GLenum textureTarget;
    GLuint glTexture;
};

#endif
