#pragma once

#ifndef __SCENE__
#define __SCENE__

#include "common/common.h"

class SceneObject;
class Light;

/*! \brief Contains all the objects that need to be rendered as well as the lights.
 *
 *  A Scene object functions more or less as a giant container. It stores all the objects
 *  and lights that will be used for rendering.
 */
class Scene: public std::enable_shared_from_this<Scene>
{
public:
    /*! \brief Returns the total number of objects in the scene.
     *  \returns Total number of objects in the scene.
     */
    size_t GetTotalObjects() const 
    { 
        return sceneObjects.size(); 
    }

    /*! \brief Returns the total number of lights in the scene.
     *  \returns Total number of lights in the scene.
     */
    size_t GetTotalLights() const
    {
        return sceneLights.size();
    }

    /*! \brief Retrive the specified object.
     *  \param index The index to use to access the Scene::sceneObjects vector.
     *  \returns A reference to the object in the object vector at the specified index.
     *
     *  Confused about the whole std::enable_if shenanigans? You can look at the 
     *  <a href="http://en.cppreference.com/w/cpp/types/enable_if">std::enable_if</a> docs. This 
     *  is part of C++'s <a href="http://en.cppreference.com/w/cpp/language/sfinae">SFINAE</a> rule.
     *  Don't worry about it if you don't get most of it. The std::enable_if is just to make sure that
     *  index is an integral (since we want to support int, uint, size_t, long, etc.) without casting.
     */
    template<typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    const SceneObject& GetSceneObject(T index) const
    {
        assert(index >= 0 && index < sceneObjects.size());
        const std::shared_ptr<SceneObject>& internalObject = sceneObjects[index];
        return *internalObject.get();
    }

    /*! \brief Retrive the specified light.
     *  \param index The index to use to access the Scene::sceneLights vector.
     *  \returns A pointer to the light in the light vector at the specified index.
     *
     *  Read the Scene::GetSceneObject() docs for more information about std::enable_if.
     *  Note the difference between this function and Scene::GetSceneObject(). Here, if we access
     *  the vector out of bounds we return a null pointer, but in Scene::GetSceneObject(), that would
     *  be an error.
     */
    template<typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    const Light* GetLightObject(T index) const
    {
        if (index >= 0 && index < sceneLights.size()) {
            return sceneLights[index].get();
        }
        return nullptr;
    }

    /*! \brief Adds a new object to the scene.
     *  \param object The object to add.
     */
    void AddSceneObject(std::shared_ptr<SceneObject> object);

    /*! \brief Adds a new light to the scene.
     *  \param light The light to add.
     */
    void AddLight(std::shared_ptr<Light> light);

    /*! \brief Removes all objects and lights from the scene. This prevents them from being rendered.
     */
    void ClearScene();

    friend class Renderer;
private:
    std::vector<std::shared_ptr<SceneObject>> sceneObjects;
    std::vector<std::shared_ptr<Light>> sceneLights;
};

#endif
