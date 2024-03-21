#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

#include <QOpenGLFunctions_3_3_Core>
#include <glm/glm.hpp>
#include <vector>
#include <stb_image.h>
#include <engine/cmesh.h>
#include <engine/cshader.h>


class CGameObject : public QOpenGLFunctions_3_3_Core
{
public:
    CGameObject() = default;
    CGameObject(glm::vec3 vPosition, glm::vec3 vRotation, glm::vec3 vScale);
    CGameObject(const CGameObject &vGameObject);
    ~CGameObject();
    glm::mat4 getModelMatrix() const;
    virtual void drawV(CShader& vShader);

protected:
    //transform
    glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_Rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 m_Scale{1.0f, 1.0f, 1.0f};

    virtual unsigned int _generateTextureIDV(const char* vPath, const std::string& vDirectory, bool vGamma = false); //读入texture数据设置参数，并为STexture.ID赋值
};

#endif // CGAMEOBJECT_H
