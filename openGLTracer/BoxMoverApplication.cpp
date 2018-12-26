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
#include "ArcShaderProgramCreater.h"


BoxMoverApplication::BoxMoverApplication(std::shared_ptr<class Arc_Engine::ArcScene> inputScene): ArcApplication(inputScene),
	vertexShader(0), fragmentShader(0), pushableBoxTexture(0), wallTexture(0), aimTexture(0), playerTexture(0)
{
	currentPath = Arc_Engine::ArcTools::getCurrentPath();
	ArcApplication::setName("BoxMoverApplication");
	//加载资源生成renderer
	diffuseShaderProgram = Arc_Engine::ArcShaderProgramCreater::loadShaderAndCreateProgram(vertexShader, fragmentShader, currentPath + shader_path + "\\hw2\\hw2.vert", currentPath + shader_path + "\\hw2\\hw2.frag");
	
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + pushable_box_path, &pushableBoxTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + wall_path, &wallTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + aim_path, &aimTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + player_path, &playerTexture);
	
	woodenCrate = std::make_shared<Arc_Engine::ArcRenderer>(diffuseShaderProgram, sizeof(vertexData), vertexData, pushableBoxTexture);
	wall = std::make_shared<Arc_Engine::ArcRenderer>(diffuseShaderProgram, sizeof(vertexData), vertexData, wallTexture);
	aim = std::make_shared<Arc_Engine::ArcRenderer>(diffuseShaderProgram, sizeof(vertexData), vertexData, aimTexture);
	player = std::make_shared<Arc_Engine::ArcRenderer>(diffuseShaderProgram, sizeof(vertexData), vertexData, playerTexture);
	
	//生成光照
	auto cur_directionLight = std::make_shared <Arc_Engine::DirectionLight>();
	cur_directionLight->setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	cur_directionLight->setDiffuse(glm::vec3(0.6f, 0.6f, 0.6f));
	cur_directionLight->setDirection(glm::vec3(0.5f, 0.8f, 0.0f));
	ArcApplication::scene()->setLight(cur_directionLight);

	//生成场景中的物体
	createGameObjects();
}

void BoxMoverApplication::createGameObjects() {
	auto tempGameObject0 = std::make_shared<Arc_Engine::ArcGameObject>();
	auto tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(2.5, 7, 1));
	tempTransform->setRotation(glm::vec3(75, 180, 0));
	tempGameObject0->setName("Camera");
	tempGameObject0->setTransfrom(tempTransform);
	auto mainCamera = std::make_shared<Arc_Engine::Camera>();
	mainCamera->setViewportAspectRatio(WIDTH / HEIGHT);
	tempGameObject0->attachScript(mainCamera);
	ArcApplication::setMainCamera(mainCamera);
	auto gameController = std::make_shared<GameController>();
	tempGameObject0->attachScript(gameController);
	scene()->addGameObject(tempGameObject0);

	auto tempGameObject1 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject1->setName("DownCube1");
	tempGameObject1->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(0.5f, 0, 5.0f));
	tempTransform->setScale(glm::vec3(2, 1, 3));
	tempGameObject1->setTransfrom(tempTransform);
	std::shared_ptr<TestScript> testScript = std::make_shared<TestScript>();
	tempGameObject1->attachScript(testScript);
	//std::cout << testScript->gameObject()->name() << std::endl;
	scene()->addGameObject(tempGameObject1);

	auto tempGameObject2 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject2->setName("DownCube2");
	tempGameObject2->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(3.5, 0, 5.5));
	tempTransform->setScale(glm::vec3(4, 1, 2));
	tempGameObject2->setTransfrom(tempTransform);
	std::shared_ptr<PushableBox> testScript2 = std::make_shared<PushableBox>();
	scene()->addGameObject(tempGameObject2);

	auto tempGameObject3 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject3->setName("DownCube3");
	tempGameObject3->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(4, 0, 2));
	tempTransform->setScale(glm::vec3(3, 1, 5));
	tempGameObject3->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject3);

	auto tempGameObject4 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject4->setName("DownCube4");
	tempGameObject4->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(1, 0, 1));
	tempTransform->setScale(glm::vec3(3, 1, 3));
	tempGameObject4->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject4);

	auto tempGameObject5 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject5->setName("DownCube5");
	tempGameObject5->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(0, 0, 3));
	tempTransform->setScale(glm::vec3(1, 1, 1));
	tempGameObject5->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject5);

	auto tempGameObject6 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject6->setName("UpCube1");
	tempGameObject6->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(5, 1, 5));
	tempTransform->setScale(glm::vec3(1, 1, 3));
	tempGameObject6->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject6);

	auto tempGameObject7 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject7->setName("UpCube2");
	tempGameObject7->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(0, 1, 3));
	tempTransform->setScale(glm::vec3(1, 1, 7));
	tempGameObject7->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject7);

	auto tempGameObject8 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject8->setName("UpCube3");
	tempGameObject8->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(1.5, 1, 6));
	tempTransform->setScale(glm::vec3(2, 1, 1));
	tempGameObject8->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject8);

	auto tempGameObject9 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject9->setName("UpCube4");
	tempGameObject9->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(3.5, 1, 5.5));
	tempTransform->setScale(glm::vec3(2, 1, 2));
	tempGameObject9->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject9);

	auto tempGameObject10 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject10->setName("UpCube5");
	tempGameObject10->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(4, 1, 3.5));
	tempTransform->setScale(glm::vec3(1, 1, 2));
	tempGameObject10->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject10);

	auto tempGameObject11 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject11->setName("UpCube6");
	tempGameObject11->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(5, 1, 2));
	tempTransform->setScale(glm::vec3(1, 1, 3));
	tempGameObject11->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject11);

	auto tempGameObject12 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject12->setName("UpCube7");
	tempGameObject12->setRenderer(wall);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(3, 1, 0));
	tempTransform->setScale(glm::vec3(5, 1, 1));
	tempGameObject12->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject12);

	auto tempGameObject13 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject13->setName("Target1");
	tempGameObject13->setRenderer(aim);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(2, 0, 4));
	tempGameObject13->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject13);

	auto tempGameObject14 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject14->setName("Target2");
	tempGameObject14->setRenderer(aim);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(2, 0, 3));
	tempGameObject14->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject14);

	auto tempGameObject15 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject15->setName("Target3");
	tempGameObject15->setRenderer(aim);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(1, 0, 3));
	tempGameObject15->setTransfrom(tempTransform);
	scene()->addGameObject(tempGameObject15);

	auto tempGameObject16 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject16->setName("PushableBox1");
	tempGameObject16->setRenderer(woodenCrate);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(3, 1, 3));
	tempGameObject16->setTransfrom(tempTransform);
	auto movableCube1 = std::make_shared<MovableCube>();
	movableCube1->setCoord(glm::vec2(3.0f, 3.0f));
	tempGameObject16->attachScript(movableCube1);
	scene()->addGameObject(tempGameObject16);

	auto tempGameObject17 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject17->setName("PushableBox2");
	tempGameObject17->setRenderer(woodenCrate);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(3, 1, 2));
	tempGameObject17->setTransfrom(tempTransform);
	auto movableCube2 = std::make_shared<MovableCube>();
	movableCube2->setCoord(glm::vec2(3.0f, 2.0f));
	tempGameObject17->attachScript(movableCube2);
	scene()->addGameObject(tempGameObject17);

	auto tempGameObject18 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject18->setName("PushableBox3");
	tempGameObject18->setRenderer(woodenCrate);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(2, 1, 2));
	tempGameObject18->setTransfrom(tempTransform);
	auto movableCube3 = std::make_shared<MovableCube>();
	movableCube3->setCoord(glm::vec2(2.0f, 2.0f));
	tempGameObject18->attachScript(movableCube3);
	scene()->addGameObject(tempGameObject18);

	auto tempGameObject19 = std::make_shared<Arc_Engine::ArcGameObject>();
	tempGameObject19->setName("Player");
	tempGameObject19->setRenderer(player);
	tempTransform = std::make_shared<Arc_Engine::ArcTransform>();
	tempTransform->setPosition(glm::vec3(1, 1.5, 4));
	tempTransform->setScale(glm::vec3(1, 2, 1));
	tempGameObject19->setTransfrom(tempTransform);
	auto player = std::make_shared<Player>();
	player->setCoord(glm::vec2(1.0f, 4.0f));
	tempGameObject19->attachScript(player);
	scene()->addGameObject(tempGameObject19);
}

