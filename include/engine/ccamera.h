#ifndef CCAMERA_H
#define CCAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

enum EProjectionType
{
    PERSPECTIVE,
    OTHOGRAPHIC
};

enum EFOVType
{
    VERTICAL_FOV,
    HORIZONTAL_FOV,
    DIAGONAL_FOV
};

class CCamera
{
public:
    CCamera(glm::vec3 vPosition = glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3 vFront = glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3 vWorldUp = glm::vec3(0.0f, 1.0f, 0.0f));
    ~CCamera();

    glm::mat4 getViewMatrix() const; //生成view matrix
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    float getYaw() const;
    float getPitch() const;
    float getFOV(EFOVType vFOVType) const; //选择返回三种FOV中的一种
    float getZNear() const;
    float getZFar() const;
    void setPosition(glm::vec3 vPosition);
    void setDirection(float vYaw, float vPitch); //暂时只允许yaw、pitch
    void setFOV(EFOVType vFOVType, float vValue);

private:
    glm::vec3 m_Position; //位置
    glm::vec3 m_Front; //前方-z
    glm::vec3 m_Up; //上方y
    glm::vec3 m_Right; //右方x
    glm::vec3 m_WorldUp; //世界坐标系上方

    float m_Yaw = -90.0f; //上下角(m_Font初始为（0，0，-1）)
    float m_Pitch = 0.0f; //左右角度

    EFOVType m_UsedFOV = VERTICAL_FOV;
    float m_VFOV = 90.0f; //vertical fov
    float m_HFOV = 90.0f; //horizontal fov
    float m_DFOV = 90.0f; //diagonal fov
    float m_ZNear = 0.1f;
    float m_ZFar = 100.0f;

    void __updateCameraDirection(); //更新m_Up, m_Right, m_WorldUp
};

#endif // CCAMERA_H
