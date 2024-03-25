#ifndef CSHADER_H
#define CSHADER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum EMaterial{
    BLINN_PHONE
};


enum EShaderType {
    VERTEX_SHADER,
    GEOMETRY_SHADER,
    FRAGMENT_SHADER
};


class CShader : public QOpenGLFunctions_3_3_Core
{
public:
    CShader();
    CShader(const char* vVertexShaderPath, const char* vFragmentShaderPath);
    CShader(const char* vVertexShaderPath, const char* vFragmentShaderPath, EMaterial vMaterial);
    CShader(const CShader &vShader);
    ~CShader();

    void use(); //使用程序
    void reload(const char* vVertexShaderPath, const char* vFragmentShaderPath); //重新加载shader
    void setUniformInt(const std::string& vName, int& vValue);
    void setUniformInt(const std::string& vName, unsigned int& vValue);
    void setUniformFloat(const std::string& vName, float& vValue);
    void setUniformMat4(const std::string& vName, glm::mat4& vValue);
    EMaterial getTarget();

private:
    EMaterial m_Target = BLINN_PHONE; //为哪种类型的物体材质做shading
    unsigned int m_ID; //shader program ID
    const char* m_VertexShaderPath; //path
    std::string m_VertexShaderCode; //code
    const char* m_FragmentShaderPath;
    std::string m_FragmentShaderCode;

    void __createProgram(); //编译、链接program（m_ID）
    void __getShaderSource(const char* vShaderPath, EShaderType vShaderType); //初始化Code
    void __checkCompileErrors(GLuint vShader, EShaderType vShaderType); //查看shader编译状态
    void __checkLinkErrors(); //查看program链接状态
};

#endif // CSHADER_H
