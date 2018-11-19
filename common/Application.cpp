#include "common/Application.h"
#include "common/Rendering/ForwardRenderer.h"
#include "common/Scene/Scene.h"
#include "common/Scene/Camera/Camera.h"

Application::Application(std::shared_ptr<class Scene> inputScene, std::shared_ptr<class Camera> inputCamera):
    isRunning(true), scene(std::move(inputScene)), camera(std::move(inputCamera))
{
}

Application::~Application()
{
}

void Application::Initialize()
{
    SetupScene();
    SetupCamera();
}

std::unique_ptr<Application> Application::CreateApplication(std::shared_ptr<class Scene> scene, std::shared_ptr<class Camera> camera)
{
    return make_unique<Application>(std::move(scene), std::move(camera));
}

std::shared_ptr<Scene> Application::CreateScene()
{
    return std::make_shared<Scene>();
}

std::shared_ptr<Camera> Application::CreateCamera()
{
    return std::make_shared<Camera>();
}

std::unique_ptr<class Renderer> Application::CreateRenderer()
{
    return make_unique<ForwardRenderer>(scene, camera);
}

glm::vec2 Application::GetWindowSize() const
{
    return glm::vec2(1280.f, 720.f);
}

void Application::SetupScene()
{
    assert(scene);
}

void Application::SetupCamera()
{
    assert(camera);
}

bool Application::IsFinished() const
{
    return !isRunning;
}

void Application::RequestExit()
{
    isRunning = false;
}

void Application::Tick(double deltaTime)
{
    // The application tick should just handle LOGIC operations.
    // Any rendering is handled by the media layer which in turn passes the information to the Renderer.
}

void Application::HandleInput(SDL_Keysym key, Uint32 state, Uint8 repeat, double timestamp, double deltaTime)
{
}

void Application::HandleWindowEvent(SDL_WindowEventID eventId, Sint32 data1, Sint32 data2, double timestamp)
{
    switch (eventId) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
    case SDL_WINDOWEVENT_RESIZED:
        HandleWindowResize(static_cast<float>(data1), static_cast<float>(data2));
        break;
    default:
        break;
    }

}

void Application::HandleWindowResize(float x, float y)
{
    OGL_CALL(glViewport(0, 0, x, y));
}
