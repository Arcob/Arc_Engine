#pragma once
#ifndef __OPENGLTRACER__
#define __OPENGLTRACER__

#include "common.h"

#include "FreeImage.h"
#include "Swb_Model.h"
#include "Camera.h"
#include "ArcBehaviour.h"
#include "TestScript.h"
#include "PushableBox.h"
#include "LightBundle.h"
#include "ArcGameObject.h"
#include "ArcRenderer.h"
#include "ArcInput.h"
#include "ArcTime.h"
#include "ArcLogger.h"
#include "Player.h"
#include "GameController.h"
#include "ArcScene.h"
#include "ArcApplication.h"
#include "ArcTextureLoader.h"
#include "BoxMoverApplication.h"

#define print Arc_Engine::ArcLogger::log 
#define Application BoxMoverApplication

std::string currentPath;

const std::string shader_path = "\\shaders";
const std::string pushable_box_path = "\\resources\\wooden-crate3.jpg";
const std::string wall_path = "\\resources\\edge.jpg";
const std::string aim_path = "\\resources\\aim.jpg";
const std::string player_path = "\\resources\\PandaPlayer.jpg";
const std::string model_path = "\\resources\\bunny.obj";

GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
double gScrollY = 0.0;
GLFWwindow* window;
GLuint pushableBoxTexture;
GLuint wallTexture;
GLuint aimTexture;
GLuint playerTexture;
Swb_Model* testModel;
std::vector<GLfloat> tempVertexData;
std::shared_ptr<Arc_Engine::Camera> mainCamera;
float deltaTime;
std::unique_ptr<Arc_Engine::ArcApplication> app;

std::shared_ptr<Arc_Engine::ArcRenderer> woodenCrate;
std::shared_ptr<Arc_Engine::ArcRenderer> wall;
std::shared_ptr<Arc_Engine::ArcRenderer> aim;
std::shared_ptr<Arc_Engine::ArcRenderer> player;

std::list<Arc_Engine::ArcGameObject> gInstances;

void draw();

void loadModel();

void TestUpdate(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

void RenderInstance(std::shared_ptr<Arc_Engine::ArcGameObject> inst);

#endif // !__OPENGLTRACER__
