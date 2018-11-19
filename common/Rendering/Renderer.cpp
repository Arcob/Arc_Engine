#include "common/Rendering/Renderer.h"
#include "common/Scene/Scene.h"
#include "common/Scene/SceneObject.h"
#include "common/Scene/Camera/Camera.h"

Renderer::Renderer(std::shared_ptr<Scene> inputScene, std::shared_ptr<Camera> inputCamera):
    scene(std::move(inputScene)), camera(std::move(inputCamera))
{
}

Renderer::~Renderer()
{
}


