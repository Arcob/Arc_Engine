#pragma once

#ifndef __PRIMITIVE_CREATOR__
#define __PRIMITIVE_CREATOR__

#include "common/common.h"
#include "common/Rendering/RenderingObject.h"

namespace PrimitiveCreator
{

//
// Utility
//
/*! \brief Utility function to add the elements in a glm::uvec3 to the indices array.
 *  \param triangle The three vertex indices for a single triangle.
 *  \param indices The index vector that we want to add the indices to.
 */
void AddTriangleIndices(const glm::uvec3& triangle, RenderingObject::IndexArray& indices);

//
// Primitive Generation
//

/*! \brief Create a cube with a given side length.
 *  \param inputShader The shader to use.
 *  \param sideLength The length of one side of the cube.
 *  \returns A RenderingObject that holds the cube vertices.
 *  \warning Not implemented.
 */
std::shared_ptr<RenderingObject> CreateCube(std::shared_ptr<ShaderProgram> inputShader, float sideLength);

/*! \brief Create a sphere with a given radius.
 *  \param inputShader The shader to use.
 *  \param radius The radius of the sphere.
 *  \param refinementSteps The number of times to subdivide the sphere.
 *
 *  Note that the first step in this process is to create a icosahedron. Afterwards, we will subdivide it multiple times as determined by
 *  refinementSteps to smooth it out to become an actual sphere.
 */
std::shared_ptr<RenderingObject> CreateIcoSphere(std::shared_ptr<ShaderProgram> inputShader, float radius, int refinementSteps = 0);

/*! \brief Creates a plane with size 1x1.
 *  \param inputShader The shader to use.
 */
std::shared_ptr<RenderingObject> CreatePlane(std::shared_ptr<ShaderProgram> inputShader);

}

#endif
