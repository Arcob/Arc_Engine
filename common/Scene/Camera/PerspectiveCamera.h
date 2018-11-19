#pragma once

#ifndef __PERSPECTIVE_CAMERA__
#define __PERSPECTIVE_CAMERA__

#include "common/Scene/Camera/Camera.h"

/*! \brief Camera that performs perspective projection.
 *  \warning The FOV in this class is the VERTICAL field of view. If you are familiar with video games, the FOV is usually presented to you as the HORIZONTAL
 *  field of view which is usually wider than the vertical field of view! Be careful! Setting your vertical field of view to something like 120 degrees is insane!
 *
 *  We will not be covering the math behind perspective projection in this class, but you can read about it on the
 *  <a href="https://en.wikipedia.org/wiki/3D_projection#Perspective_projection">Wikipedia page</a> or 
 *  <a href="http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html">this tutorial</a> if you are interested.
 *  The variables and functions in this class are just parameters to calculate the perspective projection matrix.
 */
class PerspectiveCamera: public Camera
{
public:
    PerspectiveCamera(float inFov, float inAR);

    virtual glm::mat4 GetProjectionMatrix() const;

    /*! \brief Retrieve the vertical FOV.
     *  \returns The vertical FOV in degrees.
     */
    virtual float GetFOV() const { return fov; }

    /*! \brief Set the vertical FOV.
     *  \param in The vertical FOV in degrees.
     */
    virtual void SetFOV(float in) {fov = in;}

    virtual float GetAspectRatio() const { return aspectRatio; }
    virtual void SetAspectRatio(float in) { aspectRatio = in; }

    virtual float GetZNear() const { return zNear; }
    virtual void SetZNear(float in) { zNear = in; }

    virtual float GetZFar() const { return zFar; }
    virtual void SetZFar(float in) { zFar = in; }
protected:
    virtual void UpdateTransformationMatrix();

private:
    float fov;
    float aspectRatio;
    float zNear;
    float zFar;
};

#endif
