#ifndef CMODEL_H
#define CMODEL_H

#include <QOpenGLFunctions_3_3_Core>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <engine/cgameobject.h>
#include <vector>
#include <string>

class CModel : public CGameObject
{
public:
    CModel();
    explicit CModel(std::string const& vPath, bool vGamma = false);
    ~CModel();
    void reload(std::string const& vPath);

private:
    bool m_GammaCorrection;

    void __loadModel(std::string const& vPath);
    void __processNode(aiNode* vNode, const aiScene* vScene);
    CMesh __processMesh(aiMesh* vMesh, const aiScene* vScene);
    std::vector<STexture> __loadMaterialTextures(aiMaterial* vMaterial, aiTextureType vType, std::string vTypeName);
};

#endif // CMODEL_H
