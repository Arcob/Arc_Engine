#pragma once

#ifndef __MESH_LOADER__
#define __MESH_LOADER__

#include "common/common.h"
#include "assimp/material.h"
#include <map>

class RenderingObject;
class ShaderProgram;
class Texture2D;

namespace MeshLoader
{

/*! \brief Loads a mesh file and generates a RenderingObject for each object within the file.
 *  \param inputShader The shader to use to render all the objects. This can be a null pointer in which case you can set the shaders manually afterwards.
 *  \param filename The file to load the mesh from.
 *
 *  This will load all the different meshes stored within a file into multiple rendering objects. These rendering objects can then be stored into one scene object or multiple.
 *  In the context of an OBJ file, each of the different meshes would a separate group. We will load 5 things (if it does not exist then it is ignored):
 *  - Vertex Positions
 *  - Vertex Normals
 *  - Vertex Colors
 *  - Vertex UVs
 *  - Face Vertex Indices
 *  Note that we do not load textures or material here. If you wish to do that you will have to extend the functionality in this function.
 */
std::vector<std::shared_ptr<RenderingObject>> LoadMesh(std::shared_ptr<ShaderProgram> inputShader, const std::string& filename, std::vector<std::shared_ptr<aiMaterial>>* outputMaterials = nullptr);

}

#endif
