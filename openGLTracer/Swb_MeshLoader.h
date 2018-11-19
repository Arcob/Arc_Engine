#pragma once

#ifndef __SWB_MESH_LOADER__
#define __SWB_MESH_LOADER__

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include "Swb_Model.h"
#include <sstream>

class Swb_Model;

namespace Swb_MeshLoader {

	void loadMesh(std::string filePath, Swb_Model* result);
	
	void drawMesh(Swb_Model* model);
	void loadMeshIntoVertexData(Swb_Model* model, std::vector<GLfloat> &result);
}

#endif
