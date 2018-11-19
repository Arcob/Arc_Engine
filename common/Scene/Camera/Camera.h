#pragma once

#ifndef __CAMERA__
#define __CAMERA__

#include "common/Scene/SceneObject.h"

/*! \brief The camera interface that also serves as a "null" camera.
 *
 *  If you use the Camera class directly, it will apply no transformations (aka the projection
 *  and view matrices will be the identity matrix) so you will be working with in normalized
 *  device coordinates.
 */
class Camera: public SceneObject
{
public:
    /*! \brief Creates the default camera.
     */
    Camera();
    
    /*! \brief Creates the projection matrix.
     *  \returns The identity matrix.
     *
     *  This matrix will be the "P" in the MVP matrices.
     */
    virtual glm::mat4 GetProjectionMatrix() const;
protected:
    /*! \brief Override the SceneObject::UpdateTransformationMatrix() to do nothing.
     *
     *  This will guarantee that the transformation matrix will always be an identity matrix
     *  regardless of whether you move/rotate/scale the camera.
     */
    virtual void UpdateTransformationMatrix();
};


#endif
