#pragma once

#ifndef __SCENE_OBJECT__
#define __SCENE_OBJECT__

#include "common/common.h"

/*! \brief Represents a generic object that will live in the 3D world that we call our Scene.
 *
 *  Note that this class stores no information about the actual topology of the object. Rather, all it cares
 *  about is the relationship between the object space and the world space. The position, rotation, and scale
 *  properties all come together to form the 'model matrix' which is just the way of going from object space
 *  to world space. Yay math!
 */
class SceneObject: public std::enable_shared_from_this<SceneObject>
{
public:
    /*! \brief Creates an object at the origin, with no rotation, and no scale.
     */
    SceneObject();

    /*! \brief \copybrief SceneObject::SceneObject().
     *  \param baseObject The rendering object to associate with this object.
     */
    SceneObject(std::shared_ptr<class RenderingObject> baseObject);

    /*! \brief \copybrief SceneObject::SceneObject().
     *  \param baseObjects The rendering objects (note: plural) to associate with this object.
     */
    SceneObject(const std::vector<std::shared_ptr<class RenderingObject>>& baseObjects);

    /*! \brief Destructor
     */
    virtual ~SceneObject();

    /*! \brief Passes all uniforms, binds all textures, etc. to the currently bound shader program.
     *  \param shader The shader program to use. 
     *  \param currentCamera The current camera to use.
     *  \param currentLight The current light to use.
     *
     *  Note that this assumes that the shader will only depend on five things:
     *  - The material stored in the shader.
     *  - The passed in camera.
     *  - The passed in light.
     *  - The current object's orientation in world space.
     *  - The topology of the various meshes stored in the rendering object (not handled in this function).
     *  This function will personally take care of writing the MVP matrices to the shader, but will let the shader object itself handle processing
     *  its necessary camera and light properties.
     */
    virtual void PrepareShaderForRendering(const class ShaderProgram* shader, const class Camera* currentCamera, const class Light* currentLight) const;

    /*! \brief Returns the total number of rendering objects.
     *  \returns The total number of rendering objects.
     */
    size_t GetTotalRenderObjects() const { return renderObject.size(); }

    /*! \brief Gets the specified rendering object.
     *  \param index The index to access in the SceneObject::renderObject vector.
     *  \returns Returns the a pointer to the rendering object at the given index.
     *
     *  If the index access is out of bounds in the vector then a null pointer is returned.
     */
    virtual const class RenderingObject* GetRenderObject(int index = 0) const;

    /*! \brief Retrieves the current transformation matrix.
     *  \returns SceneObject::cachedTransformationMatrix
     *
     *  This function does not perform any computation. Instead, it returns the value of whatever was computed
     *  the last time UpdateTransformationMatrix() was called.
     */
    virtual glm::mat4 GetTransformationMatrix() const;

    /*! \brief Computes and returns the forward direction of the object.
     *  \returns Returns the forward direction of the object.
     *  
     *  Rotates the world forward direction by the object's rotation.
     */
    virtual glm::vec4 GetForwardDirection() const;

    /*! \brief Computes and returns the right direction of the object.
     *  \returns Returns the right direction of the object.
     *  
     *  Rotates the world right direction by the object's rotation.
     */
    virtual glm::vec4 GetRightDirection() const;

    /*! \brief Computes and returns the up direction of the object.
     *  \returns Returns the up direction of the object.
     *  
     *  Rotates the world up direction by the object's rotation.
     */
    virtual glm::vec4 GetUpDirection() const;

    /*! \brief The world 'Up' direction.
     *  \returns glm::vec4(0, 1, 0, 0).
     */
    static glm::vec4 GetWorldUp();

    /*! \brief The world 'Right' direction.
     *  \returns glm::vec4(1, 0, 0, 0).
     */
    static glm::vec4 GetWorldRight();

    /*! \brief The world 'Forward' direction.
     *  \returns glm::vec4(0, 0, -1, 0).
     */
    static glm::vec4 GetWorldForward();

    //
    // Functions to transform the object.
    //
    /*! \brief Changes the position of the object.
     *  \param translation The world space translation to give to the object.
     */
    void Translate(const glm::vec3& translation);

    /*! \brief Changes the rotation of the object.
     *  \param axis The axis to rotate around.
     *  \param radians The number of radians to rotate around the axis.
     */
    void Rotate(const glm::vec3& axis, float radians);

    /*! \brief Changes the scale of the object uniformly.
     *  \param inputScale The scale to multiply to the current scale.
     *
     *  Let's say the current scale is \f$(x, x, x)\f$ and the input scale is \f$y\f$ then the final scale is,
     *  \f$(xy, xy, xy)\f$.
     */
    void MultScale(float inputScale);

    /*! \brief Changes the scale of the object uniformly.
     *  \param inputScale The scale to add to the current scale.
     *
     *  Let's say the current scale is \f$(x, x, x)\f$ and the input scale is \f$y\f$ then the final scale is,
     *  \f$(x + y, x + y, x + y)\f$.
     */
    void AddScale(float inputScale);

    /*! \brief Changes the position of the object.
     *  \param in The new position of the object.
     */
    void SetPosition(const glm::vec3& in);

    //
    // Individual transform retrieval.
    //
    /*! \brief Gets the position of the object.
     *  \returns The world space position of the object.
     */
    glm::vec4 GetPosition() const { return position; }
protected:
    /*! \brief Recomputes the cachedTransformationMatrix.
     *  
     *  This function should be called whenever you need the cachedTransformationMatrix and there has been
     *  a change in the position, rotation, or scale of an object. Currently it is called every time
     *  Translate(), Rotate(), MultScale(), AddScale(), and SetPosition() are called; however, it would be more
     *  efficient to only call it once per frame right before the render call.
     */
    virtual void UpdateTransformationMatrix();
    glm::mat4 cachedTransformationMatrix;

    glm::vec4 position;
    glm::quat rotation;
    glm::vec3 scale;

    static const std::string MODEL_MATRIX_LOCATION;
    static const std::string VIEW_MATRIX_LOCATION;
    static const std::string PROJECTION_MATRIX_LOCATION;
    static const float MINIMUM_SCALE;

private:
    std::vector<std::shared_ptr<class RenderingObject>> renderObject;
};

#endif
