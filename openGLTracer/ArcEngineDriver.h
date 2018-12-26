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
#include "ArcApplication.h"
#include "ArcTextureLoader.h"
#include "BoxMoverApplication.h"
#include "DriverSetting.h"

#define print Arc_Engine::ArcLogger::log 

std::string currentPath;

const std::string shader_path = "\\shaders";
const std::string pushable_box_path = "\\resources\\wooden-crate3.jpg";
const std::string wall_path = "\\resources\\edge.jpg";
const std::string aim_path = "\\resources\\aim.jpg";
const std::string player_path = "\\resources\\PandaPlayer.jpg";
const std::string model_path = "\\resources\\bunny.obj";

double gScrollY = 0.0;
GLFWwindow* window;
Swb_Model* testModel;
std::vector<GLfloat> tempVertexData;
std::unique_ptr<Arc_Engine::ArcApplication> app;

void draw();

void loadModel();

void TestUpdate(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

void RenderInstance(std::shared_ptr<Arc_Engine::ArcGameObject> inst);

#endif // !__OPENGLTRACER__
