#include <engine/cmodel.h>

//public
CModel::CModel()
{
}

CModel::CModel(std::string const& vPath, bool vGamma)
    : m_GammaCorrection{ vGamma }
{
    __loadModel(vPath);
}

CModel::~CModel()
{
}

void CModel::drawV(CShader& vShader)
{
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i].draw(vShader);
    }
}

void CModel::reload(const std::string &vPath)
{
    __loadModel(vPath);
}

//private
void CModel::__loadModel(std::string const& vPath)
{
    Assimp::Importer Importer;
    const aiScene* Scene = Importer.ReadFile(vPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << Importer.GetErrorString() << std::endl;
        return;
    }
    m_Directory = vPath.substr(0, vPath.find_last_of("/"));
    __processNode(Scene->mRootNode, Scene); //递归找到ASSIMP所有节点
}

void CModel::__processNode(aiNode* vNode, const aiScene* vScene)
{
    //当前node的所有meshes
    for (unsigned int i = 0; i < vNode->mNumMeshes; i++)
    {
        aiMesh* Mesh = vScene->mMeshes[vNode->mMeshes[i]];
        m_Meshes.push_back(__processMesh(Mesh, vScene));
    }
    //递归
    for (unsigned int i = 0; i < vNode->mNumChildren; i++)
    {
        __processNode(vNode->mChildren[i], vScene);
    }
}

CMesh CModel::__processMesh(aiMesh* vMesh, const aiScene* vScene)
{
    std::vector<SVertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<STexture> Textures;

    //Vertices
    for (unsigned int i = 0; i < vMesh->mNumVertices; i++)
    {
        glm::vec3 VectorTemp;
        SVertex Vertex;
        //Position
        VectorTemp.x = vMesh->mVertices[i].x;
        VectorTemp.y = vMesh->mVertices[i].y;
        VectorTemp.z = vMesh->mVertices[i].z;
        Vertex.Position = VectorTemp;
        //Normal
        if (vMesh->HasNormals())
        {
            VectorTemp.x = vMesh->mNormals[i].x;
            VectorTemp.y = vMesh->mNormals[i].y;
            VectorTemp.z = vMesh->mNormals[i].z;
            Vertex.Normal = VectorTemp;
        }
        //Texture
        //一个Vertex可以有8个不同的TexCoords此处Vertex只有一个，所以只关注编号为0的TexCoords
        if (vMesh->HasTextureCoords(0))
        {
            glm::vec2 VectorTempTexture;
            VectorTempTexture.x = vMesh->mTextureCoords[0][i].x;
            VectorTempTexture.y = vMesh->mTextureCoords[0][i].y;
            Vertex.TexCoords = VectorTempTexture;
        }
        else
        {
            Vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        //Tangent & Bitangent
        if (vMesh->HasTangentsAndBitangents())
        {
            VectorTemp.x = vMesh->mTangents[i].x;
            VectorTemp.y = vMesh->mTangents[i].y;
            VectorTemp.z = vMesh->mTangents[i].z;
            Vertex.Tangent = VectorTemp;
            VectorTemp.x = vMesh->mBitangents[i].x;
            VectorTemp.y = vMesh->mBitangents[i].y;
            VectorTemp.z = vMesh->mBitangents[i].z;
            Vertex.Bitangent = VectorTemp;
        }
        Vertices.push_back(Vertex);
    }

    //Indices
    for (unsigned int i = 0; i < vMesh->mNumFaces; i++)
    {
        //Face是一个mesh的其中一个triangle
        aiFace Face = vMesh->mFaces[i];
        for (unsigned int j = 0; j < Face.mNumIndices; j++)
        {
            Indices.push_back(Face.mIndices[j]);
        }
    }

    //Textures
    aiMaterial* Material = vScene->mMaterials[vMesh->mMaterialIndex];
    //diffuse
    std::vector<STexture> DiffuseTexture = __loadMaterialTextures(Material, aiTextureType_DIFFUSE, "texture_diffuse");
    Textures.insert(Textures.end(), DiffuseTexture.begin(), DiffuseTexture.end());
    //specular
    std::vector<STexture> SpecularTexture = __loadMaterialTextures(Material, aiTextureType_SPECULAR, "texture_specular");
    Textures.insert(Textures.end(), SpecularTexture.begin(), SpecularTexture.end());
    //normal
    std::vector<STexture> NormalTexture = __loadMaterialTextures(Material, aiTextureType_HEIGHT, "texture_specular");
    Textures.insert(Textures.end(), NormalTexture.begin(), NormalTexture.end());
    //height
    std::vector<STexture> HeightTexture = __loadMaterialTextures(Material, aiTextureType_AMBIENT, "texture_specular");
    Textures.insert(Textures.end(), HeightTexture.begin(), HeightTexture.end());

    return CMesh(Vertices, Indices, Textures);
}

std::vector<STexture> CModel::__loadMaterialTextures(aiMaterial* vMaterial, aiTextureType vType, std::string vTypeName)
{
    std::vector<STexture> voTextures;
    for (unsigned int i = 0; i < vMaterial->GetTextureCount(vType); i++)
    {
        aiString StringTemp;
        vMaterial->GetTexture(vType, i, &StringTemp);
        bool Skip = false; //如果texture之前已经加载则跳过
        for (unsigned int j = 0; j < m_LoadedTextures.size(); j++)
        {
            if (std::strcmp(m_LoadedTextures[j].Path.data(), StringTemp.C_Str()) == 0)
            {
                voTextures.push_back(m_LoadedTextures[j]);
                Skip = true;
                break;
            }
        }
        if (!Skip)
        {
            STexture TextureTemp;
            TextureTemp.ID = _generateTextureIDV(StringTemp.C_Str(), this->m_Directory);
            TextureTemp.Type = vTypeName;
            TextureTemp.Path = StringTemp.C_Str();
            voTextures.push_back(TextureTemp);
            m_LoadedTextures.push_back(TextureTemp);
        }
    }
    return voTextures;
}
