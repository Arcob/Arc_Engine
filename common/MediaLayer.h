//
// Class that abstracts the boilerplate to initialize SDL and 
// setup the OpenGL context.
//
#pragma once

#ifndef __MEDIA_LAYER__
#define __MEDIA_LAYER__

#include "common/common.h"
#include "common/Application.h"
#include "common/Rendering/Renderer.h"
#include <memory>

/*! \brief Class that initializes the application and makes it ready to process OpenGL commands.
 *
 * This class "owns" the Application. It will handle telling when the application and the renderer should
 * do their per-frame actions as well as handling I/O events and passing it to the application. Should you ever
 * decide to handle audio and networking this is the class that should own the respective handlers.
 */
class MediaLayer
{
public:
    /*! \brief Constructs a MediaLayer object and readies the Application and Renderer for immediate use.
     *  \warning After passing in the std::unique_ptr's to MediaLayer, you will no longer be able to use the previous std::unique_ptr's. For example, let's say you have
     *  the unique pointers x and y and you call MediaLayer(std::move(x), std::move(y)). After this call, x and y will NO LONGER BE VALID POINTERS. DO NOT USE THEM. For
     *  more information about this, you will want to read more about <a href="http://thbecker.net/articles/rvalue_references/section_01.html">R-Values</a> and 
     *  <a href="http://thbecker.net/articles/rvalue_references/section_02.html">move semantics</a>.
     *  \param inputApp The unique pointer to the application. We will own this pointer.
     *  \param inputRenderer The unique pointer to the renderer. We will own this pointer.
     *
     *  This class assumes that the Application and Renderer are ready for use once the MediaLayer is created. After passing them to
     *  the MediaLayer constructor, you will no longer be able to modify them without doing some black magic within the MediaLayer.
     */
    MediaLayer(std::unique_ptr<Application> inputApp, std::unique_ptr<Renderer> inputRenderer);

    /*! \brief A destructor. Carry on.
     */
    ~MediaLayer();

    /*! \brief Whether or not the program should keep running.
     *
     *  The main loop will query CanTick() to see if the program should keep running. If SDL or OpenGL fails, 
     *  the program will immediately exit. Also, if the application wants to exit (i.e. Application::IsFinished()) is true, then
     *  the main loop will stop as well.
     */
    bool CanTick() const;

    /*! \brief Handles what happens every frame.
     *  \param deltaTime The amount of time (seconds) since the last tick.
     *  \param currentTime The amount of time (seconds) since the program started.
     *
     *  This function does a multitude of things. First it will clear the color and depth buffers for OpenGL. If you ever decide to use a 
     *  stencil buffer, you will want to clear this here as well. Next, it will process SDL Events and cause the application to tick to
     *  move the "gameplay" logic forward. Finally we will render to the back buffer (since we are double buffering) and then swap the front
     *  and back buffers.
     */
    void Tick(double deltaTime, double currentTime);

private:
    /*! \brief Underlying Application to run. 
     */
    std::unique_ptr<Application> app;

    /*! \brief Underlying Renderer to run.
     */
    std::unique_ptr<Renderer> renderer;

    /*! \brief Initializes SDL.
     *
     *  This function will initialize SDL with <a href="https://wiki.libsdl.org/SDL_Init">SDL_Init</a> and create a window. The size
     *  of the window will initially be the value returned by Application::GetWindowSize().
     */
    void InitializeSDL();

    /*! \brief Store a pointer to the sdlWindow so we can clean this up later.
     */
    SDL_Window* sdlWindow;

    /*! \brief Set to true if InitializeSDL() runs successfully.
     */
    bool sdlInitialized;

    /*! \brief Initializes OpenGL.
     *
     *  This function will not run if SDL was not initialized. If SDL was initialized, this function will request an OpenGL context and then 
     *  setup the OpenGL function pointers using GLEW. If GLEW initialization succeeds, we will enable some sane defaults for rendering.
     */
    void InitializeOpenGL();

    /*! \brief Store the OpenGL context so that we can clean it up later.
     */
    SDL_GLContext glContext;

    /*! \brief Set to true after GLEW initialization succeeds.
     */
    bool openglInitialized;
};

#endif
