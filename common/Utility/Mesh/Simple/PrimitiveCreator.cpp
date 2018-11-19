#include "common/Utility/Mesh/Simple/PrimitiveCreator.h"
#include "common/Rendering/RenderingObject.h"
#include <cmath>
#include <algorithm>

namespace PrimitiveCreator 
{
void AddTriangleIndices(const glm::uvec3& triangle, RenderingObject::IndexArray& indices)
{
    for (int i = 0; i < 3; ++i) {
        indices.push_back(triangle[i]);
    }
}

std::shared_ptr<RenderingObject> CreateCube(std::shared_ptr<ShaderProgram> inputShader, float sideLength)
{
    return nullptr;
}

std::shared_ptr<RenderingObject> CreatePlane(std::shared_ptr<ShaderProgram> inputShader)  
{
    std::unique_ptr<RenderingObject::PositionArray> vertexPositions = make_unique<RenderingObject::PositionArray>();
    vertexPositions->emplace_back(0.f, 0, 0.f, 1.f);
    vertexPositions->emplace_back(1.f, 0, 0.f, 1.f);
    vertexPositions->emplace_back(0.f, 0, 1.f, 1.f);
    vertexPositions->emplace_back(1.f, 0, 1.f, 1.f);

    std::unique_ptr<RenderingObject::NormalArray> vertexNormals = make_unique<RenderingObject::NormalArray>();
    vertexNormals->emplace_back(0.f, 1.f, 0.f);
    vertexNormals->emplace_back(0.f, 1.f, 0.f);
    vertexNormals->emplace_back(0.f, 1.f, 0.f);
    vertexNormals->emplace_back(0.f, 1.f, 0.f);

    RenderingObject::IndexArray vertexIndices = {
        0, 2, 1,
        1, 2, 3
    };

    std::shared_ptr<RenderingObject> newObj = std::make_shared<RenderingObject>(std::move(inputShader),
        std::move(vertexPositions),
        make_unique<RenderingObject::IndexArray>(std::move(vertexIndices)),
        std::move(vertexNormals)
    );

    return newObj;
}

std::shared_ptr<RenderingObject> CreateIcoSphere(std::shared_ptr<ShaderProgram> inputShader, float radius, int refinementSteps)
{
    // First generate an icosahedron and then subdivide it to get the final sphere.
    // More specifics in generating the icosahedron can be found at: 
    //  http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
    //  https://en.wikipedia.org/wiki/Regular_icosahedron
    const float gr = (1.f + std::sqrt(5.f)) * 0.5f;

    std::unique_ptr<RenderingObject::PositionArray> vertexPositions = make_unique<RenderingObject::PositionArray>();
    // An Icohedron's vertices can be placed onto three orthogonal rectangles (check the links for pictures!)
    // Note that the icosahedron code is based off of the implementation by Andreas Kahler.
    vertexPositions->emplace_back(-1.f, gr, 0.f, 1.f);
    vertexPositions->emplace_back(1.f, gr, 0.f, 1.f);
    vertexPositions->emplace_back(-1.f, -gr, 0.f, 1.f);
    vertexPositions->emplace_back(1.f, -gr, 0.f, 1.f);

    vertexPositions->emplace_back(0.f, -1.f, gr, 1.f);
    vertexPositions->emplace_back(0.f, 1.f, gr, 1.f);
    vertexPositions->emplace_back(0.f, -1.f, -gr, 1.f);
    vertexPositions->emplace_back(0.f, 1.f, -gr, 1.f);

    vertexPositions->emplace_back(gr, 0.f, -1.f, 1.f);
    vertexPositions->emplace_back(gr, 0.f, 1.f, 1.f);
    vertexPositions->emplace_back(-gr, 0.f, -1.f, 1.f);
    vertexPositions->emplace_back(-gr, 0.f, 1.f, 1.f);

    // Force every vertex to be on the sphere of radius 'radius'
    std::for_each(vertexPositions->begin(), vertexPositions->end(),
        [=](decltype(*vertexPositions->begin())& position) {
            position = glm::vec4(glm::normalize(glm::vec3(position)) * radius, 1.f);
        }
    );

    RenderingObject::IndexArray vertexIndices = {
        0, 11, 5,
        0, 5, 1,
        0, 1, 7,
        0, 7, 10,
        0, 10, 11,

        1, 5, 9,
        5, 11, 4,
        11, 10, 2,
        10, 7, 6,
        7, 1, 8,

        3, 9, 4,
        3, 4, 2,
        3, 2, 6,
        3, 6, 8,
        3, 8, 9,

        4, 9, 5,
        2, 4, 11,
        6, 2, 10,
        8, 6, 7,
        9, 8, 1
    };

    // Subdivide each triangle into 4 different triangles by adding the midpoints of on each edge. Force the one vertex to be on the sphere of the given radius.
    for (int i = 0; i < refinementSteps; ++i) {
        auto totalTriangles = vertexIndices.size() / 3;

        RenderingObject::IndexArray newVertexIndices;
        newVertexIndices.reserve(totalTriangles * 4);
        for (decltype(totalTriangles) t = 0; t < totalTriangles; ++t) {
            const int triangleOffset = t * 3;
            const glm::vec4 midpointA = glm::vec4(glm::normalize(glm::vec3(vertexPositions->at(vertexIndices[triangleOffset]) + vertexPositions->at(vertexIndices[triangleOffset  + 1])) / 2.f) * radius, 1.f);
            const glm::vec4 midpointB = glm::vec4(glm::normalize(glm::vec3(vertexPositions->at(vertexIndices[triangleOffset + 1]) + vertexPositions->at(vertexIndices[triangleOffset  + 2])) / 2.f) * radius, 1.f);
            const glm::vec4 midpointC = glm::vec4(glm::normalize(glm::vec3(vertexPositions->at(vertexIndices[triangleOffset + 2]) + vertexPositions->at(vertexIndices[triangleOffset])) / 2.f) * radius, 1.f);

            unsigned int aIndex = static_cast<unsigned int>(vertexPositions->size());
            unsigned int bIndex = static_cast<unsigned int>(vertexPositions->size() + 1);
            unsigned int cIndex = static_cast<unsigned int>(vertexPositions->size() + 2);

            // NOTE: Slow. VERY SLOW. O(n^2) SLOW. :((
            // TODO: Use a KD-Tree to speed this up.
            for (decltype(vertexPositions->size()) j = 0; j < vertexPositions->size(); ++j) {
                if (aIndex >= vertexPositions->size() && glm::distance(midpointA, vertexPositions->at(j)) < 1e-6f) {
                    aIndex = j;
                }

                if (bIndex >= vertexPositions->size() && glm::distance(midpointB, vertexPositions->at(j)) < 1e-6f) {
                    bIndex = j;
                }

                if (cIndex >= vertexPositions->size() && glm::distance(midpointC, vertexPositions->at(j)) < 1e-6f) {
                    cIndex = j;
                }
            }

            if (aIndex >= vertexPositions->size()) {
                vertexPositions->push_back(midpointA);
                aIndex = vertexPositions->size() - 1;
            }

            if (bIndex >= vertexPositions->size()) {
                vertexPositions->push_back(midpointB);
                bIndex = vertexPositions->size() - 1;
            }

            if (cIndex >= vertexPositions->size()) {
                vertexPositions->push_back(midpointC);
                cIndex = vertexPositions->size() - 1;
            }

            AddTriangleIndices(glm::uvec3(vertexIndices[triangleOffset], aIndex, cIndex), newVertexIndices);
            AddTriangleIndices(glm::uvec3(vertexIndices[triangleOffset + 1], bIndex, aIndex), newVertexIndices);
            AddTriangleIndices(glm::uvec3(vertexIndices[triangleOffset + 2], cIndex, bIndex), newVertexIndices);
            AddTriangleIndices(glm::uvec3(aIndex, bIndex, cIndex), newVertexIndices);

        }
        vertexIndices = std::move(newVertexIndices);
    }

    std::unique_ptr<RenderingObject::NormalArray> vertexNormals = make_unique<RenderingObject::NormalArray>(vertexPositions->size());
    for (decltype(vertexNormals->size()) i = 0; i < vertexNormals->size(); ++i) {
        vertexNormals->at(i) = glm::normalize(glm::vec3(vertexPositions->at(i)));
    }

    std::unique_ptr<RenderingObject::UVArray> vertexUV = make_unique<RenderingObject::UVArray>(vertexPositions->size());
    for (decltype(vertexUV->size()) i = 0; i < vertexUV->size(); ++i) {
        const glm::vec3 position = glm::vec3(vertexPositions->at(i));
        float theta = acos(position.z / glm::length(position)) / PI;
        float phi = (atan2(position.y, position.x) / PI + 1.f) / 2.f;
        vertexUV->at(i) = glm::vec2(phi, theta);
    }

    std::shared_ptr<RenderingObject> newObj = std::make_shared<RenderingObject>(std::move(inputShader),
        std::move(vertexPositions), 
        make_unique<RenderingObject::IndexArray>(std::move(vertexIndices)),
        std::move(vertexNormals),
        std::move(vertexUV)
    );
            
    return newObj;
}
}
