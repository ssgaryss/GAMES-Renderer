#include <engine/cgameobject.h>

//public
CGameObject::CGameObject(glm::vec3 vPosition, glm::vec3 vRotation, glm::vec3 vScale)
    : m_Position{vPosition}, m_Rotation{vRotation}, m_Scale{vScale}
{
}

CGameObject::CGameObject(const CGameObject &vGameObject)
    :m_Position{vGameObject.m_Position}, m_Rotation{vGameObject.m_Rotation}, m_Scale{vGameObject.m_Scale}
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::drawV(CShader& vShader)
{
}

glm::mat4 CGameObject::getModelMatrix() const
{
    glm::mat4 voTransform(1.0f);
    voTransform = glm::translate(voTransform, m_Position);
    //voTransform = glm::rotate(voTransform, m_Position);
    return voTransform;

}

//protected
unsigned int CGameObject::_generateTextureIDV(const char* vPath, const std::string& vDirectory, bool vGamma)
{
    initializeOpenGLFunctions();
    std::string FileName = std::string(vPath);
    FileName = vDirectory + '/' + FileName;

    unsigned int voTextureID;
    glGenTextures(1, &voTextureID);

    int Width, Height, Channels;
    unsigned char* Data = stbi_load(FileName.c_str(), &Width, &Height, &Channels, 0);
    if (Data)
    {
        GLenum Format;
        if (Channels == 1)
        {
            Format = GL_RED;
        }
        else if (Channels == 3)
        {
            Format = GL_RGB;
        }
        else if (Channels == 4)
        {
            Format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D, voTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
        //设置参数
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(Data);
    }
    else
    {
        std::cout << "ERROR::MODEL::TEXTURE_NOT_FOUND" << std::endl;
        stbi_image_free(Data);
    }
    return voTextureID;
}


