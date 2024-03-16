#ifndef CSHADER_H
#define CSHADER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


enum EShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER
};


class CShader : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
public:
public:
    CShader(const char* vVertexShaderPath, const char* vFragmentShaderPath);
    ~CShader();

    void use() const; //使用程序
    void setUniformInt(const std::string& vName, int& vValue) const;
    void setUniformInt(const std::string& vName, unsigned int& vValue) const;
    void setUniformFloat(const std::string& vName, float& vValue) const;
    void setUniformMat4(const std::string& vName, glm::mat4& vValue) const;

private:
    unsigned int m_ID; //shader program ID
    const char* m_VertexShaderPath; //path
    std::string m_VertexShaderCode; //code
    const char* m_FragmentShaderPath;
    std::string m_FragmentShaderCode;

    void __getShaderSource(const char* vShaderPath, EShaderType vShaderType); //初始化Code
    void __checkCompileErrors(GLuint vShader, EShaderType vShaderType); //查看shader编译状态
    void __checkLinkErrors(); //查看program链接状态
};

#endif // CSHADER_H
