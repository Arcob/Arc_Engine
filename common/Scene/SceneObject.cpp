#include "common/Scene/SceneObject.h"
#include "common/Scene/Camera/Camera.h"
#include "common/Scene/Light/Light.h"
#include "common/Rendering/Shaders/ShaderProgram.h"
#include "common/Rendering/RenderingObject.h"

const std::string SceneObject::MODEL_MATRIX_LOCATION = "modelMatrix";
const std::string SceneObject::VIEW_MATRIX_LOCATION = "viewMatrix";
const std::string SceneObject::PROJECTION_MATRIX_LOCATION = "projectionMatrix";
const float SceneObject::MINIMUM_SCALE = 0.01f;

SceneObject::SceneObject():
    cachedTransformationMatrix(1.f), position(0.f, 0.f, 0.f, 1.f), rotation(1.f, 0.f, 0.f, 0.f), scale(1.f)
{
}

SceneObject::SceneObject(std::shared_ptr<class RenderingObject> baseObject):
    cachedTransformationMatrix(1.f), position(0.f, 0.f, 0.f, 1.f), rotation(1.f, 0.f, 0.f, 0.f), scale(1.f)
{
    renderObject.push_back(std::move(baseObject));
}

SceneObject::SceneObject(const std::vector<std::shared_ptr<class RenderingObject>>& baseObjects):
    cachedTransformationMatrix(1.f), position(0.f, 0.f, 0.f, 1.f), rotation(1.f, 0.f, 0.f, 0.f), scale(1.f),
    renderObject(baseObjects)
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::PrepareShaderForRendering(const ShaderProgram* shader, const Camera* currentCamera, const Light* currentLight) const
{
    assert(shader);
    // Send the model, view, and projection matrix to the shader only if the shader
    // requests those variables.
    shader->SetShaderUniform(MODEL_MATRIX_LOCATION, GetTransformationMatrix());
    shader->SetShaderUniform(VIEW_MATRIX_LOCATION, currentCamera->GetTransformationMatrix());
    shader->SetShaderUniform(PROJECTION_MATRIX_LOCATION, currentCamera->GetProjectionMatrix());

    shader->SetupShaderCamera(currentCamera);
    shader->SetupShaderLighting(currentLight);
    shader->SetupShaderMaterials();
}

const RenderingObject* SceneObject::GetRenderObject(int index) const
{
    assert(index >= 0 && index < renderObject.size());
    return renderObject[index].get();
}

glm::mat4 SceneObject::GetTransformationMatrix() const
{
    return cachedTransformationMatrix;
}

void SceneObject::UpdateTransformationMatrix()
{
    glm::mat4 newTransformation(1.f);
    newTransformation = glm::scale(glm::mat4(1.f), scale) * newTransformation;
    newTransformation = glm::mat4_cast(rotation) * newTransformation;
    newTransformation = glm::translate(glm::mat4(1.f), glm::vec3(position)) * newTransformation;
    cachedTransformationMatrix = std::move(newTransformation);
}

glm::vec4 SceneObject::GetForwardDirection() const
{
    return glm::mat4_cast(rotation) * GetWorldForward();
}

glm::vec4 SceneObject::GetRightDirection() const
{
    return glm::mat4_cast(rotation) * GetWorldRight();
}

glm::vec4 SceneObject::GetUpDirection() const
{
    return glm::mat4_cast(rotation) * GetWorldUp();
}

glm::vec4 SceneObject::GetWorldUp()
{
    return glm::vec4(0.f, 1.f, 0.f, 0.f);
}

glm::vec4 SceneObject::GetWorldRight()
{
    return glm::vec4(1.f, 0.f, 0.f, 0.f);
}

glm::vec4 SceneObject::GetWorldForward()
{
    return glm::vec4(0.f, 0.f, -1.f, 0.f);
}

void SceneObject::SetPosition(const glm::vec3& in)
{
    position = glm::vec4(in, 1.f);
    UpdateTransformationMatrix();
}

void SceneObject::Translate(const glm::vec3& translation)
{
    position += glm::vec4(translation, 0.f);
    UpdateTransformationMatrix();
}

void SceneObject::Rotate(const glm::vec3& axis, float radians)
{
    glm::quat newRotation = glm::angleAxis(radians, axis);
    rotation = newRotation * rotation;
    UpdateTransformationMatrix();
}

void SceneObject::MultScale(float inputScale)
{
    scale *= inputScale;
    scale = glm::max(scale, MINIMUM_SCALE);
    UpdateTransformationMatrix();
}

void SceneObject::AddScale(float inputScale)
{
    scale += inputScale;
    scale = glm::max(scale, MINIMUM_SCALE);
    UpdateTransformationMatrix();
}
