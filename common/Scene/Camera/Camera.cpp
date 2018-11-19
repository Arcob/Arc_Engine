#include "common/Scene/Camera/Camera.h"

Camera::Camera()
{
}

glm::mat4 Camera::GetProjectionMatrix() const 
{
    return glm::mat4(1.f);
}

void Camera::UpdateTransformationMatrix()
{
}
