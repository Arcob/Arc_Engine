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
#include "ArcInput.h"
#include "ArcTime.h"
#include "ArcLogger.h"
#include "Player.h"
#include "GameController.h"
#include <direct.h>
#include <typeinfo>


// GLEW    
#define GLEW_STATIC    
#include <GL/glew.h>    

// GLFW    
#include <GLFW/glfw3.h>    

std::string currentPath;//"D:\\Workspace\\openGLTracer"
//const std::string shader_path = "D:\\Workspace\\openGLTracer\\shaders";
const std::string shader_path = "\\shaders";
const std::string pushable_box_path = "\\resources\\wooden-crate.jpg";
const std::string wall_path = "\\resources\\edge.jpg";
const std::string aim_path = "\\resources\\aim.jpg";
const std::string player_path = "\\resources\\panda.jpg";
const std::string model_path = "\\resources\\bunny.obj";

GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLuint vao;
GLuint vbo;
double gScrollY = 0.0;
GLFWwindow* window;
GLuint pushableBoxTexture;
GLuint wallTexture;
GLuint aimTexture;
GLuint playerTexture;
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
Arc_Engine::ArcRenderer wall;
Arc_Engine::ArcRenderer aim;
Arc_Engine::ArcRenderer player;
std::list<Arc_Engine::ArcGameObject> gInstances;


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

void loadImage(std::string texture_path, GLuint* tempTexture);

void loadModel();

void Update(float secondsElapsed);

void treatKeyboardInput(float secondsElapsed);

void treatMouseInput(float secondsElapsed);

void OnScroll(GLFWwindow* window, double deltaX, double deltaY);

void LoadRenderer(Arc_Engine::ArcRenderer* renderer, GLuint* texture);

void CreateInstances();

void CreateSingleInstance(std::list<Arc_Engine::ArcGameObject>::iterator it, std::string name, Arc_Engine::ArcRenderer renderer, Arc_Engine::ArcTransform transform, std::vector<Arc_Engine::ArcBehaviour> ArcBehavoiurList);

glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z);

glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z);

glm::mat4 rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

void RenderInstance(const Arc_Engine::ArcGameObject& inst);

void PrintUpdate();

std::string getCurrentPath();

//用到模板的函数声明和定义要放在一起否则会出现链接错误
template<typename T>
std::vector<Arc_Engine::ArcGameObject*> findGameObjectsOfType() {
	std::vector<Arc_Engine::ArcGameObject*> result = std::vector<Arc_Engine::ArcGameObject*>();
	std::list<Arc_Engine::ArcGameObject>::iterator it;//start
	for (it = gInstances.begin(); it != gInstances.end(); ++it) {
		for (int i = 0; i < (it->behaviourListLength()); i++) {
			//(it->getBehaviourList())[i]->Start();
			//if (dynamic_cast<T*>(&*((it->getBehaviourList())[i])) != nullptr) {
			if (dynamic_cast<T*>(((it->getBehaviourList())[i]).get()) != nullptr) {
				Arc_Engine::ArcGameObject* temp = &*it;
				result.push_back(temp);
			}
		}
	}
	return result;
}

#endif // !__OPENGLTRACER__
