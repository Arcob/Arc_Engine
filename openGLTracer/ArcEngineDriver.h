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

double gScrollY;
GLFWwindow* window;
std::shared_ptr<Arc_Engine::ArcApplication> app;

#pragma region Unclear

GLuint gBufferMap;

std::shared_ptr<Arc_Engine::ArcRenderer> screenQuadRenderer;

GLfloat screenVertices[20] =
{
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,  0.0f, 0.0f, 1.0f
};

std::shared_ptr<Arc_Engine::ArcMaterial> postEffectMaterial;

const std::string depth_vert_shader_path = "\\shadowShader\\depth_vert.vert";
const std::string depth_frag_shader_path = "\\shadowShader\\depth_frag.frag";

const std::string quad_vert_shader_path = "\\QuadShader\\quad_vert.vert";
const std::string quad_frag_shader_path = "\\QuadShader\\quad_frag.frag";

GLuint simpleDepthShaderProgram;

void RenderPostEffectMap(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> inst, std::shared_ptr<Arc_Engine::ArcApplication> app);

void setScreenQuadRenderer();

void renderToScreenQuad();

void renderScreenQuad(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> inst, std::shared_ptr<Arc_Engine::ArcApplication> app);

#pragma endregion

void draw();

void TestUpdate(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

void renderDepthToFBO(GLuint fbo);

void RenderDepthMap(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> inst, std::shared_ptr<Arc_Engine::ArcApplication> app);

#endif // !__OPENGLTRACER__
