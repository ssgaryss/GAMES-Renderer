#include <engine/cshader.h>

CShader::CShader()
{
}

CShader::CShader(const char *vVertexShaderPath, const char *vFragmentShaderPath)
{
    initializeOpenGLFunctions();
    this->m_VertexShaderPath = vVertexShaderPath;
    this->m_FragmentShaderPath = vFragmentShaderPath;
    __getShaderSource(vVertexShaderPath, VERTEX_SHADER);
    __getShaderSource(vFragmentShaderPath, FRAGMENT_SHADER);

    __createProgram();
}

CShader::CShader(const char *vVertexShaderPath, const char *vFragmentShaderPath, EMaterial vMaterial)
    :CShader{vVertexShaderPath, vFragmentShaderPath}
{
    m_Target = vMaterial;
}

CShader::CShader(const CShader &vShader):
    m_ID{vShader.m_ID},m_VertexShaderPath{vShader.m_VertexShaderPath},m_VertexShaderCode{vShader.m_VertexShaderCode},
    m_FragmentShaderPath{vShader.m_FragmentShaderPath},m_FragmentShaderCode{vShader.m_FragmentShaderCode}
{
}

CShader::~CShader()
{

}

void CShader::use()
{
    glUseProgram(this->m_ID);
}

void CShader::reload(const char *vVertexShaderPath, const char *vFragmentShaderPath)
{
    initializeOpenGLFunctions();
    this->m_VertexShaderPath = vVertexShaderPath;
    this->m_FragmentShaderPath = vFragmentShaderPath;
    __getShaderSource(vVertexShaderPath, VERTEX_SHADER);
    __getShaderSource(vFragmentShaderPath, FRAGMENT_SHADER);

    __createProgram();
}

void CShader::setUniformInt(const std::string& vName, int& vValue)
{
    glUniform1i(glGetUniformLocation(this->m_ID, vName.c_str()), vValue);
}

void CShader::setUniformInt(const std::string& vName, unsigned int& vValue)
{
    glUniform1i(glGetUniformLocation(this->m_ID, vName.c_str()), vValue);
}

void CShader::setUniformFloat(const std::string& vName, float& vValue)
{
    glUniform1f(glGetUniformLocation(this->m_ID, vName.c_str()), vValue);
}

void CShader::setUniformMat4(const std::string& vName, glm::mat4& vValue)
{
    glUniformMatrix4fv(glGetUniformLocation(this->m_ID, vName.c_str()), 1, GL_FALSE, &vValue[0][0]);
}

EMaterial CShader::getTarget()
{
    return m_Target;
}

void CShader::__createProgram()
{
    unsigned int Vertex = glCreateShader(GL_VERTEX_SHADER);
    unsigned int Fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //编译+检查
    const char* VTemp = this->m_VertexShaderCode.c_str();
    glShaderSource(Vertex, 1, &VTemp, NULL);
    glCompileShader(Vertex);
    __checkCompileErrors(Vertex, VERTEX_SHADER);
    const char* FTemp = this->m_FragmentShaderCode.c_str();
    glShaderSource(Fragment, 1, &FTemp, NULL);
    glCompileShader(Fragment);
    __checkCompileErrors(Fragment, FRAGMENT_SHADER);
    //link
    this->m_ID = glCreateProgram();
    glAttachShader(this->m_ID, Vertex);
    glAttachShader(this->m_ID, Fragment);
    glLinkProgram(this->m_ID);
    __checkLinkErrors();

    //删除
    glDeleteShader(Vertex);
    glDeleteShader(Fragment);
}


//private
void CShader::__getShaderSource(const char* vShaderPath, EShaderType vShaderType)
{
    std::string ShaderCode; //CODE
    std::ifstream ShaderFile; //READ FILE DATA
    //异常
    ShaderFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    try
    {
        //打开
        ShaderFile.open(vShaderPath);
        //string stream
        std::stringstream ShaderStream;
        ShaderStream << ShaderFile.rdbuf();
        //数据保存至CODE
        ShaderCode = ShaderStream.str();
    }
    catch (std::fstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: \n" << e.what() << std::endl;
    }

    if (vShaderType == VERTEX_SHADER)
    {
        this->m_VertexShaderCode = ShaderCode;
    }
    else if (vShaderType == FRAGMENT_SHADER)
    {
        this->m_FragmentShaderCode = ShaderCode;
    }
    else {
        std::cout << "ERROR::SHADER::SHADER_TYPE_NOT_MATCHED! " << std::endl;
    }
    //关闭
    ShaderFile.close();
}

void CShader::__checkCompileErrors(GLuint vShader, EShaderType vShaderType)
{
    GLint Success; //是否成功
    GLchar InfoLog[1024]; //compile错误信息
    if (vShaderType == VERTEX_SHADER) {
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &Success); //检查是否成功
        if (!Success)
        {
            glGetShaderInfoLog(vShader, 1024, NULL, InfoLog); //不成功输出报错信息
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED: \n" << InfoLog << std::endl;
        }
    }
    else if (vShaderType == FRAGMENT_SHADER)
    {
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &Success); //检查是否成功
        if (!Success)
        {
            glGetShaderInfoLog(vShader, 1024, NULL, InfoLog); //不成功输出报错信息
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: \n" << InfoLog << std::endl;
        }
    }
}

void CShader::__checkLinkErrors()
{
    GLint Success; //是否成功
    GLchar InfoLog[1024]; //link错误信息
    glGetProgramiv(this->m_ID, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        glGetProgramInfoLog(this->m_ID, 512, NULL, InfoLog);
        std::cout << "ERROR::LINK_FAILED::PROGRAM_ID:" << this->m_ID << "\n" << InfoLog << std::endl;
    }
}
