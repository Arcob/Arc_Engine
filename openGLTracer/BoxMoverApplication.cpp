#include "BoxMoverApplication.h"
#include "ArcTools.h"
#include "ArcScene.h"
#include "ArcApplication.h"
#include "ArcTextureLoader.h"


BoxMoverApplication::BoxMoverApplication(std::shared_ptr<class Arc_Engine::ArcScene> inputScene): ArcApplication(inputScene)
{
	currentPath = Arc_Engine::ArcTools::getCurrentPath();
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + pushable_box_path, &pushableBoxTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + wall_path, &wallTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + aim_path, &aimTexture);
	Arc_Engine::ArcTextureLoader::loadImageToTexture(currentPath + player_path, &playerTexture);

	woodenCrate = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, pushableBoxTexture);
	wall = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, wallTexture);
	aim = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, aimTexture);
	player = std::make_shared<Arc_Engine::ArcRenderer>(shaderProgram, sizeof(vertexData), vertexData, playerTexture);
}


BoxMoverApplication::~BoxMoverApplication()
{
}
