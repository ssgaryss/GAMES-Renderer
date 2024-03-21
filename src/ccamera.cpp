#include <engine/ccamera.h>

//public
CCamera::CCamera(glm::vec3 vPosition, glm::vec3 vFront, glm::vec3 vWorldUp)
{
    this->m_Position = vPosition;
    this->m_Front = vFront;
    this->m_WorldUp = vWorldUp;
    __updateCameraDirection();
}

CCamera::~CCamera()
{
}

glm::mat4 CCamera::getViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::vec3 CCamera::getPosition() const { return m_Position; }
glm::vec3 CCamera::getFront() const { return m_Front; }
glm::vec3 CCamera::getUp() const { return m_Up; }
glm::vec3 CCamera::getRight() const { return m_Right; }
float CCamera::getYaw() const { return m_Yaw; }
float CCamera::getPitch() const { return m_Pitch; }
float CCamera::getFOV(EFOVType vFOVType) const
{
    if (vFOVType == VERTICAL_FOV)
    {
        return m_VFOV;
    }
    else if (vFOVType == HORIZONTAL_FOV)
    {
        return m_HFOV;
    }
    else if (vFOVType == DIAGONAL_FOV)
    {
        return m_DFOV;
    }
    else
    {
        std::cout << "FOVType not matched！" << std::endl;
        throw "undefined FOV type!";
    }
}

float CCamera::getZNear() const { return m_ZNear; }
float CCamera::getZFar() const { return m_ZFar; }

void CCamera::setPosition(glm::vec3 vPosition) { this->m_Position = vPosition; }

void CCamera::setDirection(float vYaw, float vPitch)
{
    this->m_Yaw = vYaw;
    this->m_Pitch = vPitch;
    __updateCameraDirection();
}

void CCamera::setFOV(EFOVType vFOVType, float vValue)
{
    if (vValue > 179.0f) vValue = 179.0f;
    if (vValue < 3.0f) vValue = 3.0f;
    if (vFOVType == VERTICAL_FOV)
    {
        m_VFOV = vValue;
    }
    else if (vFOVType == HORIZONTAL_FOV)
    {
        m_HFOV = vValue;
    }
    else if (vFOVType == DIAGONAL_FOV)
    {
        m_DFOV = vValue;
    }
    else
    {
        std::cout << "FOVType not matched！" << std::endl;
    }
}

//private
void CCamera::__updateCameraDirection()
{
    glm::vec3 Front;
    Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    Front.y = sin(glm::radians(m_Pitch));
    Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(Front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    if (glm::isnan(m_Right.x) || glm::isnan(m_Right.y) || glm::isnan(m_Right.z)) { m_Right = glm::vec3(1.0f, 0.0f, 0.0f); }
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    std::cout << "m_Front: " << m_Front.x << " " << m_Front.y << " " << m_Front.z << std::endl;
    std::cout << "m_Right: " << m_Right.x << " " << m_Right.y << " " << m_Right.z << std::endl;
    std::cout << "m_Up: " << m_Up.x << " " << m_Up.y << " " << m_Up.z << std::endl;
}
