#include <engine/cmesh.h>

//public
CMesh::CMesh(std::vector<SVertex> vVertices, std::vector<unsigned int> vIndices, std::vector<STexture> vTextures) :
    m_Vertices{ vVertices }, m_Indices{ vIndices }, m_Textures{ vTextures }
{
    __setUpMesh();
}

CMesh::CMesh(const CMesh &vMesh):
    m_Vertices{vMesh.m_Vertices},m_Indices{vMesh.m_Indices}, m_Textures{vMesh.m_Textures},
    m_VAO{vMesh.m_VAO}, m_VBO{vMesh.m_VBO}, m_EBO{vMesh.m_EBO}
{
}

CMesh::~CMesh()
{
}

void CMesh::draw(CShader& vShader)
{
    initializeOpenGLFunctions();
    //shader中texture取名为TextureType + Number
    unsigned int DiffuseNumber = 1;
    unsigned int SpecularNumber = 1;
    unsigned int NormalNumber = 1;
    unsigned int HeightNumber = 1;
    //绑定texture到shader
    for (unsigned int i = 0; i < m_Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string Number;
        std::string TextureType = m_Textures[i].Type;
        if (TextureType == "texture_diffuse")
        {
            Number = std::to_string(DiffuseNumber++);
        }
        else if (TextureType == "texture_specular")
        {
            Number = std::to_string(SpecularNumber++);
        }
        else if (TextureType == "texture_normal")
        {
            Number = std::to_string(NormalNumber++);
        }
        else if (TextureType == "texture_height")
        {
            Number = std::to_string(HeightNumber++);
        }
        else
        {
            std::cout << "ERROR::MESH::UNKNOWN_TEXTURE_TYPE" << std::endl;
        }
        vShader.setUniformInt((TextureType + Number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_Textures[i].ID);
    }
    //绘制
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(m_VAO);
    //回复默认设置
    glActiveTexture(GL_TEXTURE0);
}

//private
void CMesh::__setUpMesh()
{
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(SVertex), &m_Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, TexCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Bitangent));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 3, GL_INT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, BoneIDs));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Weights));

    glBindVertexArray(0); //解绑
}
