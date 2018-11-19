#pragma once

#ifndef __APPLICATION__
#define __APPLICATION__

#include "common/common.h"

/*! \brief Handles creating configurable objects (i.e. scene, camera, renderer), handling SDL events passed in by the MediaLayer, and handles creating the scene to be display.
 *
 *  An 'Application' MUST be created to run the assignment framework. By default, the application will create a 1280x720 window that is completely black. 
 *  After the 'Application' is created, it must be passed to the 'MediaLayer' who will call the 'Application's tick function every frame.
 */
class Application
{
public:
    /*! \brief Create an application with a pre-allocated scene and camera.
     *  \param inputScene A pre-allocated scene. This should be generated using CreateScene() in the appropriate subclass.
     *  \param inputCamera A pre-allocated camera. This should be generated using CreateCamera() in the appropriate subclass.
     *  \warning Do not use directly. Use CreateApplication instead.
     */
    Application(std::shared_ptr<class Scene> inputScene, std::shared_ptr<class Camera> inputCamera);

    /*! \brief Virtual deconstrcutor to allow inheritance.
     */
    virtual ~Application();

    /*! \brief Initialization function to setup the stored camera and scene.
     *
     * This initialization function exists because the SetupScene() and SetupCamera() functions are virtual and thus can not exist
     * within the constructor. This function is called in MediaLayer::MediaLayer().
     */
    virtual void Initialize();

    /*! \brief Creates a unique pointer to an Application. This should be used instead of the constructor. 
     *  \returns A unique pointer to an Application.
     *
     *  See Application() for more details.
     */
    static std::unique_ptr<Application> CreateApplication(std::shared_ptr<class Scene> scene, std::shared_ptr<class Camera> camera);

    /*! \brief Creates a shared pointer of type Scene.
     *  \returns A shared pointer to a Scene.
     *
     *  The subclass should also create a function CreateScene() that returns the proper type of Scene to create.
     */
    static std::shared_ptr<class Scene> CreateScene();

    /*! \brief Creates a shared pointer of type Camera.
     *  \returns A shared pointer to a Camera.
     *
     *  The subclass should also create a function CreateCamera() that returns the proper type of Camera to create.
     */
    static std::shared_ptr<class Camera> CreateCamera();

    /*! \brief Creates a shared pointer of type Renderer.
     *  \returns A unique pointer to a Renderer.
     *
     *  The subclass should override this function CreateRenderer() to return the proper type of Renderer to create.
     */
    virtual std::unique_ptr<class Renderer> CreateRenderer();

    /*! \brief Specifies the initial window size.
     *  \returns The desired window size.
     */
    virtual glm::vec2 GetWindowSize() const;

    /*! \brief Whether or not the application is finished running.
     *  \returns Whether the application is finished running.
     *
     *  When the MediaLayer::Tick() function detects that the application is finished, the program will exit.
     */
    virtual bool IsFinished() const;

    /*! \brief Notifies the Application that it should finish. 
     *
     *  An external source (i.e. the MediaLayer) may request for the Application to finish. This lets the Application exit
     *  gracefully.  The Application can choose to ignore the request (thought that is not recommended). 
     *  After this function is called, IsFinished() should return true.
     */
    virtual void RequestExit();

    /*! \brief Called every frame to advance program logic.
     *  \param deltaTime The amount of time (in seconds) since the last tick.
     *
     *  If you need something in the Scene to change over time, this is where you should implement that logic. It is recommended that you 
     *  make use of the deltaTime variable to make things change smoothly!
     */
    virtual void Tick(double deltaTime);

    /*! \brief Processes an SDL keyboard event which has type <a href="https://wiki.libsdl.org/SDL_KeyboardEvent">SDL_KeyboardEvent</a>.
     *  \param key See the SDL documentation for more details about <a href="https://wiki.libsdl.org/SDL_Keysym">SDL_Keysym</a>.
     *  \param state This is the type field in the <a href="https://wiki.libsdl.org/SDL_Event">SDL_Event</a>datastructure.
     *  \param repeat This value is non-zero is the key is being repeated. 
     *  \param timestamp Timestamp is the number of seconds since the program was first started.
     *  \param deltaTime The amount of time (in seconds) since the last tick.
     *
     *  Takes in a keyboard event and process it. This does nothing by default. 'deltaTime' is included to allow you to move something
     *  and have the movement look smooth. For example, if you have an object that you want to move forward whenever 'W' is pressed. You
     *  know that the object travels at 10 meters per second when 'W' is pressed and 0 meters per second when it is not. How far should you
     *  move the object? You would want to move it forward by \f$10 \cdot deltaTime \f$ units.
     */
    virtual void HandleInput(SDL_Keysym key, Uint32 state, Uint8 repeat, double timestamp, double deltaTime);

    /*! \brief Processes an SDL window event. Details about an SDL window event can be found <a href="https://wiki.libsdl.org/SDL_WindowEvent">here</a>
      * \param eventId This is an <a href="https://wiki.libsdl.org/SDL_WindowEventID">SDL_WindowEventID</a>. See the SDL documentation for more details.
      * \param data1 This changes depending on what eventId is. See the docs for SDL_WindowEventID.
      * \param data2 This changes depending on what eventId is. See the docs for SDL_WindowEventID.
      * \param timestamp Timestamp is the number of seconds since the program was first started.
      *
      * This takes in a window event and process it. By default it handles when the size of the window change and calls HandleWindowResize().
      * You can expand on this functionality in the sub-class to handle other events such as the window moving, etc. However,
      * make sure you maintain a call to Application::HandleWindowEvent() to make sure glViewport is still called!
      */
    virtual void HandleWindowEvent(SDL_WindowEventID eventId, Sint32 data1, Sint32 data2, double timestamp);
protected:
    /*! \brief Whether or not the application is currently running.
     *
     * This variable is negated and returned by IsFinished().
     */
    bool isRunning;


    /*! \brief A shared pointer to the scene.
     *
     *  Currently, there can only ever be one scene at a time. You will add lights and other objects to the scene to generate your image. This scene is used across
     *  the framework to perform rendering.
     */
    std::shared_ptr<class Scene> scene;

    /*! \brief A shared pointer to the camera.
     *
     *  Currently, only one camera is supported at a time. This one camera will be shared across the framework to properly generate the view and projection matrices.
     *  Additionally, shaders utilize some camera properties to calculate the fragment color.
     */
    std::shared_ptr<class Camera> camera;

    /*! \brief Called by HandleWindowEvent() when the window is resized.
     *  \param x The width of the window.
     *  \param y The height of the window.
     * 
     *  By default calls, <a href="https://www.opengl.org/sdk/docs/man/html/glViewport.xhtml">glViewport</a> to resize the viewport as necessary. If any part of your
     *  application depends on the window resize, you will want to take care of it in this function! (Hint for the OPTIONAL deferred rendering task in assignment 2: 
     *  your 'G-Buffers' should be resized).
     */
    virtual void HandleWindowResize(float x, float y);
private:
    /*! \brief Called by Initialize() to populate the scene.
     *
     *  Note by the time this function is called, the Application sub-class is fully constructed and Scene object is already created.
     */
    virtual void SetupScene();

    /*! \brief Called by Initialize() to setup the camera.
     *
     *  Note by the time this function is called, the Application sub-class is fully constructed and Camera object is already created.
     */
    virtual void SetupCamera();
};

#endif
