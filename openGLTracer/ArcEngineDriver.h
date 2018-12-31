#pragma once
#ifndef __OPENGLTRACER__
#define __OPENGLTRACER__

#include "common.h"

#include "Swb_Model.h"
#include "ArcBehaviour.h"
#include "ArcGameObject.h"
#include "ArcRenderer.h"
#include "ArcTime.h"
#include "ArcInput.h"
#include "ArcLogger.h"
#include "ArcScene.h"
#include "ArcTools.h"
#include "ArcApplication.h"
#include "ArcTextureLoader.h"
#include "DriverSetting.h"
#include "ArcMaterial.h"

#define print Arc_Engine::ArcLogger::log 

double gScrollY = 0.0;
GLFWwindow* window;
std::shared_ptr<Arc_Engine::ArcApplication> app;

GLuint simpleDepthShaderProgram;

void draw();

void TestUpdate(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

void renderDepthToFBO(GLuint fbo);

void RenderDepthMap(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> inst, std::shared_ptr<Arc_Engine::ArcApplication> app);
#endif // !__OPENGLTRACER__
