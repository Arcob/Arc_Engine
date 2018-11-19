#pragma once

#ifndef __RENDERER__
#define __RENDERER__

#include "common/common.h"

/*! \brief A generic rendering interface.
 *
 *  The renderer will be used by the MediaLayer and will be told to Render() every frame. It is the renderer's responsibility to 
 *  make sure everything in the scene gets rendered properly with the right shader using all the lights.
 */ 
class Renderer
{
public:
    /*! \brief The Renderer constructor takes in a scene to be rendered and the camera from which to render the scene.
     *  \param inputScene A shared pointer to the scene. This can be a null pointer but you would need to introduce functions to set it later.
     *  \param inputCamera A shared pointer to the camera. This can be a null pointer but you would need to introduce functions to set it later.
     */
    Renderer(std::shared_ptr<class Scene> inputScene, std::shared_ptr<class Camera> inputCamera);

    /*! \brief A virtual destructor to allow for safe inheritance.
     */
    virtual ~Renderer();

    /*! \brief Prepares the renderer for usage. 
     *  
     *  Called in the MediaLayer constructor.
     */
    virtual void Initialize() = 0;

    /*! \brief This function should be used to render everything onto the screen.
     */
    virtual void Render() = 0;

protected:
    /*! \brief Shared pointer to the scene. Should not be a null pointer when you go to render.
     */
    std::shared_ptr<class Scene> scene;

    /*! \brief Shared pointer to the camera. Should not be a null pointer when you go to render.
     */
    std::shared_ptr<class Camera> camera;
};

#endif
