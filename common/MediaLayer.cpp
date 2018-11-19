#include "common/MediaLayer.h"
#include <iostream>

MediaLayer::MediaLayer(std::unique_ptr<Application> inputApp, std::unique_ptr<Renderer> inputRenderer):
    app(std::move(inputApp)), renderer(std::move(inputRenderer)), sdlWindow(nullptr), sdlInitialized(false), openglInitialized(false)
{
    assert(app);
    assert(renderer);

    InitializeSDL();
    InitializeOpenGL();

    renderer->Initialize();
    app->Initialize();
}

MediaLayer::~MediaLayer()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
}

void MediaLayer::InitializeSDL()
{
    // Initialize all the SDL Subsytems you need.
    // Checkout https://wiki.libsdl.org/SDL_Init#Remarks for more subsystems.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "ERROR: SDL Initialization failed." << std::endl;
        return;
    }

    // Create OpenGL Context with the set attributes. This tells SDL to create an OpenGL context
    // with the specifies properties.
    // More information can be found here: https://wiki.libsdl.org/SDL_GL_SetAttribute 
    // Note that these properties must be set before the window is created.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE ); 
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1); 

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

    glm::vec2 windowSize(app->GetWindowSize());
    sdlWindow = SDL_CreateWindow("CS148 Fall 2018-2019", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowSize.x, windowSize.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!sdlWindow) {
        std::cerr << "ERROR: SDL failed to create a window." << std::endl;
        return;
    }

    sdlInitialized = true;
}

void MediaLayer::InitializeOpenGL()
{
    if (!sdlInitialized) {
        std::cerr << "ERROR: Can not initialize OpenGL before setting up SDL." << std::endl;
        return;
    }

    glContext = SDL_GL_CreateContext(sdlWindow);
    if (glContext == NULL) {
        std::cerr << "ERROR: SDL failed to create an OpenGL context" << std::endl;
        return;
    }

    // 0 - Disables Vsync, 1 - Enables Vsync
    // More information: https://www.opengl.org/wiki/Swap_Interval
    // Documentation: https://wiki.libsdl.org/SDL_GL_SetSwapInterval
    SDL_GL_SetSwapInterval(0);

    // Initialize GLEW 
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "ERROR: GLEW failed to initialize." << std::endl;
        return;
    }
    // At this point we want to flush out all of the OpenGL errors that might have been caused by GLEW.
    while ((err = glGetError()) != GL_NO_ERROR);

    openglInitialized = true;

    // Sane default settings for OpenGL rendering
    OGL_CALL(glEnable(GL_DEPTH_TEST));
    OGL_CALL(glDepthFunc(GL_LEQUAL));

    OGL_CALL(glEnable(GL_BLEND));
    OGL_CALL(glBlendFunc(GL_ONE, GL_ONE));

    OGL_CALL(glEnable(GL_CULL_FACE));
    OGL_CALL(glCullFace(GL_BACK));
    OGL_CALL(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));

    OGL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

#ifdef __APPLE__
    SDL_PumpEvents();
    SDL_SetWindowSize(sdlWindow, app->GetWindowSize().x, app->GetWindowSize().y);
#endif
}

bool MediaLayer::CanTick() const
{
    return (openglInitialized && sdlInitialized && !app->IsFinished());
}

void MediaLayer::Tick(double deltaTime, double currentTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // First let the events happen to change the application state (if necessary)
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
        switch (event.type)
        {
        case SDL_QUIT:
            app->RequestExit();
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            app->HandleInput(event.key.keysym, event.type, event.key.repeat, currentTime, deltaTime);
            break;
        case SDL_WINDOWEVENT:
            app->HandleWindowEvent(static_cast<SDL_WindowEventID>(event.window.event), event.window.data1, event.window.data2, currentTime);
            break;
        default:            
            break;
        }
    }

    // Then call the app->Tick() to let the application handle logic updates and make changes to the scene.
    app->Tick(deltaTime);

    // The rendering operation should come after the logic update so that we can get the updated results immediately.
    renderer->Render();
    
    // More info: https://wiki.libsdl.org/SDL_GL_SwapWindow
    // Note this is only used because we requested a double buffered OpenGL context, hence why we need to tell OpenGL
    // to swap the buffers and show the buffer that was being written to. 
    SDL_GL_SwapWindow(sdlWindow);
}
