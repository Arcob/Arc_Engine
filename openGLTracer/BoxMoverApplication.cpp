#include "BoxMoverApplication.h"
#include "ArcTools.h"
#include "ArcScene.h"
#include "ArcApplication.h"
#include "ArcTextureLoader.h"
#include "Player.h"
#include "GameController.h"
#include "TestScript.h"
#include "PushableBox.h"
#include "LightBundle.h"
#include "ArcGameObject.h"


BoxMoverApplication::BoxMoverApplication(std::shared_ptr<class Arc_Engine::ArcScene> inputScene): ArcApplication(inputScene),
	vertexShader(0), fragmentShader(0), shaderProgram(0), pushableBoxTexture(0), wallTexture(0), aimTexture(0), playerTexture(0)
{
	loadShaderAndCreateProgram(vertexShader, fragmentShader, currentPath + "\\hw2\\hw2.vert", currentPath + "\\hw2\\hw2.frag");
	currentPath = Arc_Engine::ArcTools::getCurrentPath();
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + pushable_box_path, &pushableBoxTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + wall_path, &wallTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + aim_path, &aimTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + player_path, &playerTexture);

	woodenCrate = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, pushableBoxTexture);
	wall = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, wallTexture);
	aim = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, aimTexture);
	player = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, playerTexture);
	
	createGameObjects();
}

void BoxMoverApplication::loadShaderAndCreateProgram(GLuint vertexShader, GLuint fragmentShader, std::string vertexShaderPath, std::string fragmentShaderPath) {
	std::ifstream v(shader_path + vertexShaderPath);
	std::string vertBuffer((std::istreambuf_iterator<char>(v)), std::istreambuf_iterator<char>());
	std::ifstream f(shader_path + fragmentShaderPath);
	std::string fragBuffer((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

	const GLchar* vertCharArray = vertBuffer.c_str();
	const GLchar* fragCharArray = fragBuffer.c_str();
	const GLint vertCharArrayLength = vertBuffer.size();
	const GLint fragCharArrayLength = fragBuffer.size();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertCharArray, &vertCharArrayLength);
	glShaderSource(fragmentShader, 1, &fragCharArray, &fragCharArrayLength);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
}

void BoxMoverApplication::createGameObjects() {
	auto tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	auto tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(2.5, 7, 1));
	tempTransform.setRotation(glm::vec3(75, 180, 0));
	tempGameObject->setName("Camera");
	tempGameObject->setTransfrom(tempTransform);
	auto mainCamera = std::make_shared<Arc_Engine::Camera>();
	mainCamera->setViewportAspectRatio(WIDTH / HEIGHT);
	tempGameObject->attachScript(mainCamera);
	ArcApplication::setMainCamera(mainCamera);
	auto gameController = std::make_shared<GameController>();
	tempGameObject->attachScript(gameController);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("DownCube1");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(0.5f, 0, 5.0f));
	tempTransform.setScale(glm::vec3(2, 1, 3));
	tempGameObject->setTransfrom(tempTransform);
	std::shared_ptr<TestScript> testScript = std::make_shared<TestScript>();
	tempGameObject->attachScript(testScript);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("DownCube2");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(3.5, 0, 5.5));
	tempTransform.setScale(glm::vec3(4, 1, 2));
	tempGameObject->setTransfrom(tempTransform);
	std::shared_ptr<PushableBox> testScript2 = std::make_shared<PushableBox>();
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("DownCube3");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(4, 0, 2));
	tempTransform.setScale(glm::vec3(3, 1, 5));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("DownCube4");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(1, 0, 1));
	tempTransform.setScale(glm::vec3(3, 1, 3));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("DownCube5");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(0, 0, 3));
	tempTransform.setScale(glm::vec3(1, 1, 1));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube1");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(5, 1, 5));
	tempTransform.setScale(glm::vec3(1, 1, 3));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube2");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(0, 1, 3));
	tempTransform.setScale(glm::vec3(1, 1, 7));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube3");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(1.5, 1, 6));
	tempTransform.setScale(glm::vec3(2, 1, 1));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube4");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(3.5, 1, 5.5));
	tempTransform.setScale(glm::vec3(2, 1, 2));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube5");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(4, 1, 3.5));
	tempTransform.setScale(glm::vec3(1, 1, 2));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube6");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(5, 1, 2));
	tempTransform.setScale(glm::vec3(1, 1, 3));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("UpCube7");
	tempGameObject->setRenderer(wall);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(3, 1, 0));
	tempTransform.setScale(glm::vec3(5, 1, 1));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("Target1");
	tempGameObject->setRenderer(aim);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(2, 0, 4));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("Target2");
	tempGameObject->setRenderer(aim);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(2, 0, 3));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("Target3");
	tempGameObject->setRenderer(aim);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(1, 0, 3));
	tempGameObject->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("PushableBox1");
	tempGameObject->setRenderer(woodenCrate);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(3, 1, 3));
	tempGameObject->setTransfrom(tempTransform);
	auto movableCube1 = std::make_shared<MovableCube>();
	movableCube1->setCoord(glm::vec2(3.0f, 3.0f));
	tempGameObject->attachScript(movableCube1);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("PushableBox2");
	tempGameObject->setRenderer(woodenCrate);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(3, 1, 2));
	tempGameObject->setTransfrom(tempTransform);
	auto movableCube2 = std::make_shared<MovableCube>();
	movableCube2->setCoord(glm::vec2(3.0f, 2.0f));
	tempGameObject->attachScript(movableCube2);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("PushableBox3");
	tempGameObject->setRenderer(woodenCrate);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(2, 1, 2));
	tempGameObject->setTransfrom(tempTransform);
	auto movableCube3 = std::make_shared<MovableCube>();
	movableCube3->setCoord(glm::vec2(2.0f, 2.0f));
	tempGameObject->attachScript(movableCube3);
	scene()->addGameObject(tempGameObject);

	tempGameObject = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject->setName("Player");
	tempGameObject->setRenderer(player);
	tempTransform = Arc_Engine::ArcTransform();
	tempTransform.setPosition(glm::vec3(1, 1.5, 4));
	tempTransform.setScale(glm::vec3(1, 2, 1));
	tempGameObject->setTransfrom(tempTransform);
	auto player = std::make_shared<Player>();
	player->setCoord(glm::vec2(1.0f, 4.0f));
	tempGameObject->attachScript(player);
	scene()->addGameObject(tempGameObject);
}