#ifndef CMESH_H
#define CMESH_H

#include <QOpenGLFunctions_3_3_Core>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <engine/cshader.h>

#define MAX_BONE_INFLUENCE 4

struct SVertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent; //二重切线
    //bone indexes which will influence this vertex
    int BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float Weights[MAX_BONE_INFLUENCE];

};

struct STexture
{
    unsigned int ID;
    std::string Type; //texture_diffuse/specular/normal/height
    std::string Path;
};

class CMesh : public QOpenGLFunctions_3_3_Core
{
public:
    std::vector<SVertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<STexture> m_Textures;

    CMesh(std::vector<SVertex> vVertices, std::vector<unsigned int> vIndices, std::vector<STexture> vTextures);
    CMesh(const CMesh& vMesh);
    ~CMesh();
    void draw(CShader& vShader);

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    void __setUpMesh();
};

#endif // CMESH_H
