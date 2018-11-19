/*! \file core.h
 *  \brief The file to include to include all relevant classes of the assignment framework.
 */
#pragma once

#ifndef __CORE__
#define __CORE__

#include "common/common.h"

#include "common/Rendering/RenderingObject.h"
#include "common/Rendering/Shaders/ShaderProgram.h"
#include "common/Rendering/Shaders/BlinnPhongShader.h"
#include "common/Scene/Scene.h"
#include "common/Scene/SceneObject.h"
#include "common/Scene/Camera/Camera.h"
#include "common/Scene/Camera/PerspectiveCamera.h"
#include "common/Scene/Light/Light.h"
#include "common/Scene/Light/LightProperties.h"
#include "common/Rendering/Textures/Texture2D.h"
#include "common/Rendering/Textures/CubeMapTexture.h"
#include "common/Rendering/Shaders/CubeMapShader.h"

#endif
