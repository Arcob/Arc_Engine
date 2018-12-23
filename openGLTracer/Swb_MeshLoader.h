#pragma once

#ifndef __SWB_MESH_LOADER__
#define __SWB_MESH_LOADER__

#include "commom.h"

class Swb_Model;

namespace Swb_MeshLoader {

	void loadMesh(std::string filePath, Swb_Model* result);
	
	void drawMesh(Swb_Model* model);
	void loadMeshIntoVertexData(Swb_Model* model, std::vector<GLfloat> &result);
}

#endif
