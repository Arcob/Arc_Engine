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

std::string currentPath;

const std::string shader_path = "\\shaders";
const std::string depth_vert_shader_path = "\\shadowShader\\depth_vert.vert";
const std::string depth_frag_shader_path = "\\shadowShader\\depth_frag.frag";
const std::string debug_depth_vert_shader_path = "\\shadowShader\\shadow_vert.vert";
const std::string debug_depth_frag_shader_path = "\\shadowShader\\shadow_frag.frag";

const std::string aim_path = "\\resources\\aim.jpg";
GLuint aimTexture;

double gScrollY = 0.0;
GLFWwindow* window;
Swb_Model* testModel;
std::vector<GLfloat> tempVertexData;
std::shared_ptr<Arc_Engine::ArcApplication> app;

GLuint depthMapFBO;
GLuint depthMap;
GLuint simpleDepthShaderProgram;
GLuint debugDepthShaderProgram;
glm::mat4 lightSpaceMatrix;

std::shared_ptr<Arc_Engine::ArcMaterial> depthMaterial;
std::shared_ptr<Arc_Engine::ArcMaterial> shaderDebugMaterial;

void draw();

void loadModel();

void TestUpdate(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

//void RenderInstance(std::shared_ptr<Arc_Engine::ArcGameObject> inst);

//void RenderInstance(std::shared_ptr<Arc_Engine::ArcGameObject> inst, GLuint program, GLuint texture);

void createShadowBuffer(GLuint* depthMapFBO, GLuint depthMap);

void RenderQuad();

void RenderDepthMap(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> inst, std::shared_ptr<Arc_Engine::ArcApplication> app);

#endif // !__OPENGLTRACER__
