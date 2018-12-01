#pragma once
#ifndef __OPENGLTRACER__
#define __OPENGLTRACER__



#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <list>
#include "FreeImage.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/common.hpp>
#include <glm/glm.hpp>
#include "Swb_Model.h"
#include "Camera.h"
#include "ArcBehaviour.h"
#include "TestScript.h"
#include "PushableBox.h"
#include "LightBundle.h"
#include "ArcGameObject.h"
#include "ArcRenderer.h"


// GLEW    
#define GLEW_STATIC    
#include <GL/glew.h>    

// GLFW    
#include <GLFW/glfw3.h>    

const std::string shader_path = "D:\\Workspace\\openGLTracer\\shaders";
const std::string texture_path = "D:\\Workspace\\openGLTracer\\resources\\wooden-crate.jpg";
const std::string model_path = "D:\\Workspace\\openGLTracer\\resources\\bunny.obj";

GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLuint vao;
GLuint vbo;
double gScrollY = 0.0;
GLFWwindow* window;
GLuint _textureId;
Swb_Model* testModel;
std::vector<GLfloat> tempVertexData;
std::shared_ptr<Arc_Engine::Camera> mainCamera;
Arc_Engine::DirectionLight directionLight;
double deltaTime;

/*struct ArcRenderer {
	GLuint program;
	GLuint texture;
	GLuint vbo;
	GLuint vao;
	GLenum drawType;
	GLint drawStart;
	GLint drawCount;
};*/

/*struct ArcGameObject {
	ArcRenderer* renderer = NULL;
	glm::mat4 transform;
	std::vector<std::shared_ptr<ArcBehaviour>> ArcBehaviourList;
};*/

Arc_Engine::ArcRenderer woodenCrate;
std::list<Arc_Engine::ArcGameObject> gInstances;

/*GLfloat vertexData[] = {
	//  X     Y     Z       U     V
	0.0f, 0.8f, 0.0f,   0.5f, 1.0f,
	-0.8f,-0.8f, 0.0f,   0.0f, 0.0f,
	0.8f,-0.8f, 0.0f,   1.0f, 0.0f,
};*/

/*GLfloat vertexData[] = {
	//  X     Y     Z       U     V
	// bottom
	-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
	1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,

	// top
	-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
	1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

	// front
	-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
	1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

	// back
	-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

	// left
	-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

	// right
	1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,   0.0f, 1.0f
};*/

GLfloat vertexData[] = {
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,1.0f,	// A
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,	// B
	0.5f, 0.5f, 0.5f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,	// C
	0.5f, 0.5f, 0.5f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,	// C
	-0.5f, 0.5f, 0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,	// D
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// A


	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,	// E
	-0.5f, 0.5f, -0.5f,  0.0, 1.0f,  0.0f, 0.0f, -1.0f, // H
	0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 0.0f, -1.0f,	// G
	0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 0.0f, -1.0f,	// G
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,	// F
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,	// E

	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,	// D
	-0.5f, 0.5f, -0.5f, 1.0, 1.0f,   -1.0f, 0.0f, 0.0f, // H
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,	// E
	-0.5f, -0.5f, -0.5f,1.0f, 0.0f, -1.0f, 0.0f, 0.0f,	// E
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,	// A
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,	// D

	0.5f, -0.5f, -0.5f,1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // F
	0.5f, 0.5f, -0.5f,1.0f, 1.0f,  1.0f, 0.0f, 0.0f, // G
	0.5f, 0.5f, 0.5f,0.0f, 1.0f,   1.0f, 0.0f, 0.0f, // C
	0.5f, 0.5f, 0.5f,0.0f, 1.0f,   1.0f, 0.0f, 0.0f, // C
	0.5f, -0.5f, 0.5f,0.0f, 0.0f,  1.0f, 0.0f, 0.0f, // B
	0.5f, -0.5f, -0.5f,1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // F

	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// G
	-0.5f, 0.5f, -0.5f, 0.0, 1.0f, 0.0f, 1.0f, 0.0f,    // H
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,	// D
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,	// D
	0.5f, 0.5f, 0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,	// C
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// G

	-0.5f, -0.5f, 0.5f,0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  // A
	-0.5f, -0.5f, -0.5f,0.0f, 1.0f, 0.0f, -1.0f, 0.0f,  // E
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f, // F
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f, // F
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   0.0f, -1.0f, 0.0f, // B
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, // A
};

void loadShader(std::string vertexShaderPath, std::string fragmentShaderPath);

void setupBuffer();

void draw();

void loadImage();

void loadModel();

void Update(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

void LoadWoodenCrateAsset();

void CreateInstances();

void CreateSingleInstance(std::list<Arc_Engine::ArcGameObject>::iterator it, std::string name, Arc_Engine::ArcRenderer renderer, Arc_Engine::ArcTransform transform, std::vector<Arc_Engine::ArcBehaviour> ArcBehavoiurList);

glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z);

glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z);

glm::mat4 rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

void RenderInstance(const Arc_Engine::ArcGameObject& inst);

void PrintUpdate();

#endif // !__OPENGLTRACER__
