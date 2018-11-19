#include "common/Rendering/RenderingObject.h"
#include "common/Rendering/Shaders/ShaderProgram.h"

glm::vec3 RenderingObject::DEFAULT_NORMAL(0.f, 0.f, 1.f);
glm::vec2 RenderingObject::DEFAULT_UV(0.f, 0.f);
glm::vec4 RenderingObject::DEFAULT_COLOR(1.f, 1.f, 1.f, 1.f);

RenderingObject::RenderingObject(std::shared_ptr<ShaderProgram> inputShader,
        std::unique_ptr<PositionArray> inputPositions,
        std::unique_ptr<IndexArray> inputIndices,
        std::unique_ptr<NormalArray> inputNormals,
        std::unique_ptr<UVArray> inputUV,
        std::unique_ptr<ColorArray> inputColors,
        std::unique_ptr<TangentArray> inputTangent,
        std::unique_ptr<BitangentArray> inputBitangent):
    shader(std::move(inputShader)),
    vertexPositionBuffer(0), vertexPositions(std::move(inputPositions)), 
    vertexIndexBuffer(0), vertexIndices(std::move(inputIndices)),
    vertexNormalBuffer(0), vertexNormals(std::move(inputNormals)), 
    vertexTangentBuffer(0), vertexTangents(std::move(inputTangent)),
    vertexBitangentBuffer(0), vertexBitangents(std::move(inputBitangent)),
    vertexUVBuffer(0), vertexUV(std::move(inputUV)), 
    vertexColorBuffer(0), vertexColors(std::move(inputColors)),
    drawMode(GL_TRIANGLES)
{
    assert(vertexPositions);
    InitializeOpenGL();
}

RenderingObject::~RenderingObject()
{
    CleanupVertexPositions();
    CleanupVertexNormals();
    CleanupVertexUV();
    CleanupVertexColors();
    CleanupVertexIndices();
    CleanupVertexTangents();
    CleanupVertexBitangents();
    OGL_CALL(glDeleteVertexArrays(1, &vao));
}

void RenderingObject::SetShader(std::shared_ptr<class ShaderProgram> inputShader)
{
    shader = std::move(inputShader);
}

void RenderingObject::InitializeOpenGL()
{
    // Setup mesh data
    OGL_CALL(glGenVertexArrays(1, &vao));

    // Generate a multiple buffers to hold the various vertex attributes
    UpdateVertexPositions();
    UpdateVertexNormals();
    UpdateVertexUV();
    UpdateVertexColors();
    UpdateVertexIndices();
    UpdateVertexTangents();
    UpdateVertexBitangents();
}

void RenderingObject::BeginRender() const
{
    OGL_CALL(glBindVertexArray(vao));
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffer));
}

// TODO: Use the 'Instanced' versions of all these commands to batch these commands together.
void RenderingObject::Render() const
{
    // If we have an EBO (element array buffer) then use it, otherwise assume that the 
    // order of the vertices is already correct. Note that we assume that we are always
    // rendering triangles.
    if (vertexIndexBuffer) {
        OGL_CALL(glDrawElements(drawMode, vertexIndices->size(), GL_UNSIGNED_INT, (void*)0));
    } else {
        OGL_CALL(glDrawArrays(drawMode, 0, vertexPositions->size()));
    }
}

void RenderingObject::EndRender() const
{
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    OGL_CALL(glBindVertexArray(0));
}

GLint RenderingObject::GetShaderProgram() const
{ 
    return shader->GetProgram(); 
}

const ShaderProgram* RenderingObject::GetShaderProgramRaw() const
{
    return shader.get();
}

void RenderingObject::SetVertexPositions(std::unique_ptr<PositionArray> positions)
{
    vertexPositions = std::move(positions);
    UpdateVertexPositions();
}

void RenderingObject::SetVertexIndices(std::unique_ptr<IndexArray> indices)
{
    vertexIndices = std::move(indices);
    UpdateVertexIndices();
}

void RenderingObject::SetVertexNormals(std::unique_ptr<NormalArray> normals)
{
    vertexNormals = std::move(normals);
    UpdateVertexNormals();
}

void RenderingObject::SetVertexUV(std::unique_ptr<UVArray> uv)
{
    vertexUV = std::move(uv);
    UpdateVertexUV();
}

void RenderingObject::SetVertexColors(std::unique_ptr<ColorArray> colors)
{
    vertexColors = std::move(colors);
    UpdateVertexColors();
}

void RenderingObject::SetVertexTangents(std::unique_ptr<TangentArray> input)
{
    vertexTangents = std::move(input);
    UpdateVertexTangents();
}

void RenderingObject::SetVertexBitangents(std::unique_ptr<BitangentArray> input)
{
    vertexBitangents = std::move(input);
    UpdateVertexBitangents();
}

void RenderingObject::UpdateVertexPositions()
{
    assert(vertexPositions);

    BeginRender();
    if (!vertexPositionBuffer) {
        OGL_CALL(glGenBuffers(1, &vertexPositionBuffer));
    }
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer));
    OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertexPositions->size(), &(*vertexPositions.get())[0], GL_STATIC_DRAW));
    OGL_CALL(glVertexAttribPointer(static_cast<int>(VertexAttributePositions::Position), 4, GL_FLOAT, GL_FALSE, 0, 0));
    OGL_CALL(glEnableVertexAttribArray(static_cast<int>(VertexAttributePositions::Position)));
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    EndRender();
}


void RenderingObject::UpdateVertexIndices()
{
    BeginRender();
    // If vertex indices are used, then we can use an element array buffer to make use of more efficient rendering.
    if (vertexIndices) {
        if (!vertexIndexBuffer) {
            OGL_CALL(glGenBuffers(1, &vertexIndexBuffer));
        }
        OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffer));
        OGL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * vertexIndices->size(), &(*vertexIndices.get())[0], GL_STATIC_DRAW));
        OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    } else {
        CleanupVertexIndices();
    }
    EndRender();
}

void RenderingObject::UpdateVertexNormals()
{
    BeginRender();
    if (vertexNormals) {
        if (vertexNormals->size() == vertexPositions->size()) {
            if (!vertexNormalBuffer) {
                OGL_CALL(glGenBuffers(1, &vertexNormalBuffer));
            }
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexNormalBuffer));
            OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexNormals->size(), &(*vertexNormals.get())[0], GL_STATIC_DRAW));
            OGL_CALL(glVertexAttribPointer(static_cast<int>(VertexAttributePositions::Normals), 3, GL_FLOAT, GL_FALSE, 0, 0));
            OGL_CALL(glEnableVertexAttribArray(static_cast<int>(VertexAttributePositions::Normals)));
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        } else {
            std::cerr << "WARNING: Ignoring input vertex normals. It needs to have the same number of elements as the vertex positions vector." << std::endl;   
            CleanupVertexNormals();
        }
    } else {
        CleanupVertexNormals();
    }
    
    if (!vertexNormalBuffer) {
        OGL_CALL(glVertexAttrib3fv(static_cast<int>(VertexAttributePositions::Normals), glm::value_ptr(DEFAULT_NORMAL)));
    }
    EndRender();
}

void RenderingObject::UpdateVertexUV()
{
    BeginRender();
    if (vertexUV) {
        if (vertexUV->size() == vertexPositions->size()) {
            if (!vertexUVBuffer) {
                OGL_CALL(glGenBuffers(1, &vertexUVBuffer));
            }
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexUVBuffer));
            OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertexUV->size(), &(*vertexUV.get())[0], GL_STATIC_DRAW));
            OGL_CALL(glVertexAttribPointer(static_cast<int>(VertexAttributePositions::UV), 2, GL_FLOAT, GL_FALSE, 0, 0));
            OGL_CALL(glEnableVertexAttribArray(static_cast<int>(VertexAttributePositions::UV)));
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        } else {
            std::cerr << "WARNING: Ignoring input vertex UVs. It needs to have the same number of elements as the vertex positions vector." << std::endl;   
            CleanupVertexUV();
        }
    } else {
        CleanupVertexUV();
    }

    if (!vertexUVBuffer) {
        OGL_CALL(glVertexAttrib2fv(static_cast<int>(VertexAttributePositions::UV), glm::value_ptr(DEFAULT_UV)));
    }
    EndRender();
}

void RenderingObject::UpdateVertexColors()
{
    BeginRender();
    if (vertexColors) {
        if (vertexColors->size() == vertexPositions->size()) {
            if (!vertexColorBuffer) {
                OGL_CALL(glGenBuffers(1, &vertexColorBuffer));
            }
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer));
            OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertexColors->size(), &(*vertexColors.get())[0], GL_STATIC_DRAW));
            OGL_CALL(glVertexAttribPointer(static_cast<int>(VertexAttributePositions::Colors), 4, GL_FLOAT, GL_FALSE, 0, 0));
            OGL_CALL(glEnableVertexAttribArray(static_cast<int>(VertexAttributePositions::Colors)));
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        } else {
            std::cerr << "WARNING: Ignoring input vertex colors. It needs to have the same number of elements as the vertex positions vector." << std::endl;   
            CleanupVertexColors();
        }
    } else {
        CleanupVertexColors();
    }

    if (!vertexColorBuffer) {
        OGL_CALL(glVertexAttrib4fv(static_cast<int>(VertexAttributePositions::Colors), glm::value_ptr(DEFAULT_COLOR)));
    }
    EndRender();
}

void RenderingObject::UpdateVertexTangents()
{
    BeginRender();
    if (vertexTangents) {
        if (vertexTangents->size() == vertexPositions->size()) {
            if (!vertexTangentBuffer) {
                OGL_CALL(glGenBuffers(1, &vertexTangentBuffer));
            }
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexTangentBuffer));
            OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexTangents->size(), &(*vertexTangents.get())[0], GL_STATIC_DRAW));
            OGL_CALL(glVertexAttribPointer(static_cast<int>(VertexAttributePositions::Tangent), 3, GL_FLOAT, GL_FALSE, 0, 0));
            OGL_CALL(glEnableVertexAttribArray(static_cast<int>(VertexAttributePositions::Tangent)));
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        } else {
            std::cerr << "WARNING: Ignoring input tangents. It needs to have the same number of elements as the vertex positions vector." << std::endl;
            CleanupVertexTangents();
        }
    } else {
        CleanupVertexTangents();
    }

    if (!vertexTangentBuffer) {
        OGL_CALL(glVertexAttrib3fv(static_cast<int>(VertexAttributePositions::Tangent), glm::value_ptr(DEFAULT_NORMAL)));
    }
    EndRender();
}

void RenderingObject::UpdateVertexBitangents()
{
    BeginRender();
    if (vertexBitangents) {
        if (vertexBitangents->size() == vertexPositions->size()) {
            if (!vertexBitangentBuffer) {
                OGL_CALL(glGenBuffers(1, &vertexBitangentBuffer));
            }
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexBitangentBuffer));
            OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexBitangents->size(), &(*vertexBitangents.get())[0], GL_STATIC_DRAW));
            OGL_CALL(glVertexAttribPointer(static_cast<int>(VertexAttributePositions::Bitangent), 3, GL_FLOAT, GL_FALSE, 0, 0));
            OGL_CALL(glEnableVertexAttribArray(static_cast<int>(VertexAttributePositions::Bitangent)));
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        } else {
            std::cerr << "WARNING: Ignoring input vertex bitangents. It needs to have the same number of elements as the vertex positions vector." << std::endl;
            CleanupVertexBitangents();
        }
    } else {
        CleanupVertexBitangents();
    }

    if (!vertexBitangentBuffer) {
        OGL_CALL(glVertexAttrib3fv(static_cast<int>(VertexAttributePositions::Bitangent), glm::value_ptr(DEFAULT_NORMAL)));
    }
    EndRender();
}

void RenderingObject::CleanupVertexPositions()
{
    OGL_CALL(glDeleteBuffers(1, &vertexPositionBuffer));
    vertexPositionBuffer = 0;
}

void RenderingObject::CleanupVertexIndices()
{
    OGL_CALL(glDeleteBuffers(1, &vertexIndexBuffer));
    vertexIndexBuffer = 0;
}

void RenderingObject::CleanupVertexNormals()
{
    OGL_CALL(glDeleteBuffers(1, &vertexNormalBuffer));
    vertexNormalBuffer = 0;
}

void RenderingObject::CleanupVertexUV()
{
    OGL_CALL(glDeleteBuffers(1, &vertexUVBuffer));
    vertexUVBuffer = 0;
}

void RenderingObject::CleanupVertexColors()
{
    OGL_CALL(glDeleteBuffers(1, &vertexColorBuffer));
    vertexColorBuffer = 0;
}

void RenderingObject::CleanupVertexTangents()
{
    OGL_CALL(glDeleteBuffers(1, &vertexTangentBuffer));
    vertexTangentBuffer = 0;
}

void RenderingObject::CleanupVertexBitangents()
{
    OGL_CALL(glDeleteBuffers(1, &vertexBitangentBuffer));
    vertexBitangentBuffer = 0;
}

void RenderingObject::ComputeTangentSpace()
{
    assert(vertexUV->size() == vertexPositions->size());
    vertexTangents = make_unique<TangentArray>(vertexPositions->size());
    vertexBitangents = make_unique<BitangentArray>(vertexPositions->size());

    bool hasValidNormals = true;
    if (!vertexNormals) {
        hasValidNormals = false;
        vertexNormals = make_unique<BitangentArray>(vertexPositions->size());
    }
    
    auto totalIndices = vertexIndices->size();
    auto totalVertices = vertexPositions->size();
    // Iterate through every triangle and for each triangle calculate the tangent and bitangent for each vertex.
    // This uses the equations shown in class (Lecture 8).
    std::vector<int> tangentAverager(vertexPositions->size());
    if (vertexIndices && !vertexIndices->empty()) {
        assert(vertexIndices->size() % 3 == 0);
        for (decltype(totalIndices) i = 0; i < totalIndices; i += 3) {
            glm::ivec3 triangle(vertexIndices->at(i), vertexIndices->at(i + 1), vertexIndices->at(i + 2));
            ComputeTangentSpaceHelper(triangle, hasValidNormals, tangentAverager);
        }
    } else {
        assert(vertexPositions->size() % 3 == 0);
        
        for (decltype(totalVertices) i = 0; i < totalVertices; i += 3) {
            glm::ivec3 triangle(i, i + 1, i + 2);
            ComputeTangentSpaceHelper(triangle, hasValidNormals, tangentAverager);
        }
    }

    for (decltype(totalVertices) i = 0; i < totalVertices; ++i) {
        vertexTangents->at(i) = glm::normalize(vertexTangents->at(i) / static_cast<float>(tangentAverager[i]));
        vertexBitangents->at(i) = glm::normalize(vertexBitangents->at(i) / static_cast<float>(tangentAverager[i]));
        if (!hasValidNormals) {
            vertexNormals->at(i) = glm::normalize(vertexNormals->at(i) / static_cast<float>(tangentAverager[i]));
        }
    }

    UpdateVertexBitangents();
    UpdateVertexTangents();
    UpdateVertexNormals();
}

void RenderingObject::ComputeTangentSpaceHelper(glm::ivec3 triangleVertexIndices, bool useStoredNormals, std::vector<int>& averager)
{
    for (int x = 0; x < 3; ++x) {
        const int i = triangleVertexIndices[x];
        const int j = triangleVertexIndices[(x + 1) % 3];
        const int k = triangleVertexIndices[(x + 2) % 3];

        glm::vec3 deltaPos21 = glm::vec3(vertexPositions->at(j) - vertexPositions->at(i));
        glm::vec3 deltaPos31 = glm::vec3(vertexPositions->at(k) - vertexPositions->at(i));

        glm::vec2 deltaUV21 = vertexUV->at(j) - vertexUV->at(i);
        glm::vec2 deltaUV31 = vertexUV->at(k) - vertexUV->at(i);
            
        glm::vec3 bitangent = (deltaPos21 * deltaUV31.x - deltaPos31 * deltaUV21.x) / (deltaUV21.y * deltaUV31.x - deltaUV31.y * deltaUV21.x);
        glm::vec3 tangent;
        if (useStoredNormals) {
            glm::vec3 currentNormal = vertexNormals->at(i);
            tangent = glm::cross(bitangent, currentNormal);
        } else {
            tangent = (deltaPos21 - bitangent * deltaUV21.y) / deltaUV21.x;
            vertexNormals->at(i) += glm::cross(tangent, bitangent);
        }
        
        vertexTangents->at(i) += tangent;
        vertexBitangents->at(i) += bitangent;

        ++averager[i];
    }
}

void RenderingObject::ReverseNormals()
{
    if (!vertexNormals) {
        return;
    }

    for (size_t i = 0; i < vertexNormals->size(); ++i) {
        vertexNormals->at(i) *= -1.f;
    }

    UpdateVertexNormals();
}

void RenderingObject::ReverseVertexOrder()
{
    if (vertexIndices) {
        assert(vertexIndices->size() % 3 == 0);
        for (size_t i = 0; i < vertexIndices->size(); i += 3) {
            std::swap(vertexIndices->at(i + 1), vertexIndices->at(i + 2));
        }
    } else {
        assert(vertexPositions->size() % 3 == 0);
        for (size_t i = 0; i < vertexPositions->size(); ++i) {
            std::swap(vertexPositions->at(i + 1), vertexPositions->at(i + 2));

            if (vertexNormals) {
                std::swap(vertexNormals->at(i + 1), vertexNormals->at(i + 2));
            }

            if (vertexTangents) {
                std::swap(vertexTangents->at(i + 1), vertexTangents->at(i + 2));
            }

            if (vertexBitangents) {
                std::swap(vertexBitangents->at(i + 1), vertexBitangents->at(i + 2));
            }

            if (vertexUV) {
                std::swap(vertexUV->at(i + 1), vertexUV->at(i + 2));
            }

            if (vertexColors) {
                std::swap(vertexColors->at(i + 1), vertexColors->at(i + 2));
            }
        }
    }

    UpdateVertexPositions();
    UpdateVertexNormals();
    UpdateVertexUV();
    UpdateVertexColors();
    UpdateVertexIndices();
    UpdateVertexTangents();
    UpdateVertexBitangents();
}
