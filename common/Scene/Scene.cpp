#include "common/Scene/Scene.h"

void Scene::AddSceneObject(std::shared_ptr<SceneObject> object)
{
    if (!object) {
        return;
    }
    sceneObjects.emplace_back(std::move(object));
}

void Scene::AddLight(std::shared_ptr<Light> light)
{
    if (!light) {
        return;
    }
    sceneLights.emplace_back(std::move(light));
}

void Scene::ClearScene()
{
    sceneObjects.clear();
    sceneLights.clear();
}
