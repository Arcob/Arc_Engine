#pragma once
#include "ArcApplication.h"
#include "ArcRenderer.h"
#include "ArcMaterial.h"

void RenderInstance(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> inst, std::shared_ptr<Arc_Engine::ArcApplication> app);


class BoxMoverApplication :
	public Arc_Engine::ArcApplication
{
public:
	BoxMoverApplication(std::shared_ptr<class Arc_Engine::ArcScene> inputScene, GLuint WIDTH, GLuint HEIGHT);
	void createGameObjects();
	~BoxMoverApplication() = default;

private:
	std::string currentPath;

	const std::string shader_path = "\\shaders";
	const std::string normal_vert_shader_path = "\\boxShader\\box_vert.vert";
	const std::string normal_frag_shader_path = "\\boxShader\\box_frag.frag";
	const std::string depth_vert_shader_path = "\\shadowShader\\depth_vert.vert";
	const std::string depth_frag_shader_path = "\\shadowShader\\depth_frag.frag";
	const std::string pushable_box_path = "\\resources\\wooden-crate3.jpg";
	const std::string wall_path = "\\resources\\edge.jpg";
	const std::string aim_path = "\\resources\\aim.jpg";
	const std::string player_path = "\\resources\\PandaPlayer.jpg";
	const std::string model_path = "\\resources\\bunny.obj";

	std::shared_ptr<Arc_Engine::ArcMaterial> diffuseShaderMaterial;

	std::shared_ptr<Arc_Engine::ArcRenderer> woodenCrate;
	std::shared_ptr<Arc_Engine::ArcRenderer> wall;
	std::shared_ptr<Arc_Engine::ArcRenderer> aim;
	std::shared_ptr<Arc_Engine::ArcRenderer> player;

	GLuint pushableBoxTexture;
	GLuint wallTexture;
	GLuint aimTexture;
	GLuint playerTexture;

	GLuint depthMap;
	
	GLfloat vertexData[288] = {
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
};

