#include "common/Scene/Camera/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float inFov, float inAR):
    fov(inFov), aspectRatio(inAR), zNear(1.f), zFar(200.f)
{
}

glm::mat4 PerspectiveCamera::GetProjectionMatrix() const
{
    return glm::perspective(GetFOV() * PI / 180.f, GetAspectRatio(), GetZNear(), GetZFar());
}

void PerspectiveCamera::UpdateTransformationMatrix()
{
    SceneObject::UpdateTransformationMatrix();
    cachedTransformationMatrix = glm::inverse(cachedTransformationMatrix);
}
