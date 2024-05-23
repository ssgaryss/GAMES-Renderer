#include <engine/csceneview.h>
#include <QDebug>


CSceneView::CSceneView(QWidget *parent)
    : QOpenGLWidget{parent}, m_FPSLabel{this}
{
}

// CSceneView::CSceneView(const CSceneView &vSceneView)
//     : m_SceneViewShaders{vSceneView.m_SceneViewShaders}, m_SceneViewCamera{vSceneView.m_SceneViewCamera}
// {
// }

void CSceneView::initializeGL()
{
    initializeOpenGLFunctions();
    CModel a("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/resources/objects/bunny/bunny.obj");
    CModel b("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/resources/objects/mary/Marry.obj");
    CModel c("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/resources/objects/base_objects/plane/plane.obj");
    this->loadGameObject(a);
    this->loadGameObject(b);
    this->loadGameObject(c);
    m_SceneViewShader.reload("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/src/shaders/model.vs",
                             "D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/src/shaders/model.fs");
    m_FrameTimer.start();
}

void CSceneView::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void CSceneView::paintGL()
{
    m_FPS = 1000.0f / m_FrameTimer.elapsed();
    m_FrameTimer.restart();
    m_FPSLabel.setText(QString("FPS: %1").arg(QString::number(m_FPS, 'f', 2)));
    glEnable(GL_DEPTH_TEST);

    m_SceneViewShader.use();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_GameObjects.at(0).setPosition(glm::vec3{-0.5f, -0.3f, 0.0f});
    m_GameObjects.at(1).setPosition(glm::vec3{0.0f, -0.3f, 0.0f});
    m_GameObjects.at(2).setPosition(glm::vec3{0.0f, -0.3f, 0.0f});
    m_GameObjects.at(1).setScale(glm::vec3{0.2f, 0.2f, 0.2f});
    __draw();
    update();
}

void CSceneView::loadShader(const char *vVertexShaderPath, const char *vFragmentShaderPath, EMaterial vMaterial)
{
    for(std::vector<CShader>::iterator it = m_SceneViewShaders.begin(); it < m_SceneViewShaders.end(); ++it){
        if(it->getTarget() == vMaterial){
            std::cout << "ERROR::SCENE_VIEW::SHADER_ALREADY_EXISTS: \n" << std::endl;
            return;
        }
    }
    CShader Shader(vVertexShaderPath, vFragmentShaderPath, vMaterial);
    m_SceneViewShaders.push_back(Shader);
}

CShader CSceneView::selectShader(EMaterial vTarget)
{
    for(std::vector<CShader>::iterator it = m_SceneViewShaders.begin(); it < m_SceneViewShaders.end(); ++it){
        if(it->getTarget() == vTarget){
            return *it;
        }
    }
    std::cout << "ERROR::SCENE_VIEW::SHADER_NOT_EXISTS: \n" << std::endl;
}

void CSceneView::mouseMoveEvent(QMouseEvent *vEvent)
{
    QPoint CurrentPos = vEvent->pos();
    float XOffset = CurrentPos.x() - m_lastFrameMousePos.x();
    float YOffset = m_lastFrameMousePos.y() - CurrentPos.y(); // reversed since y-coordinates go from bottom to top
    m_lastFrameMousePos = CurrentPos;
    if(allowShake){
        __shakeSceneView(XOffset, YOffset, true);
    }
}

void CSceneView::keyPressEvent(QKeyEvent *vEvent)
{
    if(vEvent->key() == Qt::Key_W){
        __moveSceneView(FORWARD);
    }
    else if(vEvent->key() == Qt::Key_S){
        __moveSceneView(BACKWARD);
    }
    else if(vEvent->key() == Qt::Key_A)
    {
        __moveSceneView(LEFT);
    }
    else if(vEvent->key() == Qt::Key_D)
    {
        __moveSceneView(RIGHT);
    }
    else if(vEvent->key() == Qt::Key_Q)
    {
        __moveSceneView(UP);
    }
    else if(vEvent->key() == Qt::Key_E)
    {
        __moveSceneView(DOWN);
    }

    if(vEvent->key() == Qt::Key_Alt && Qt::AltModifier){
            allowShake = true;
    }
}

void CSceneView::keyReleaseEvent(QKeyEvent *vEvent)
{
    if(vEvent->key() == Qt::Key_Alt){
        allowShake = false;
    }
}

void CSceneView::__draw()
{
    glm::mat4 Projection = __getProjectionMatrix();
    glm::mat4 View = m_SceneViewCamera.getViewMatrix();
    m_SceneViewShader.setUniformMat4("projection", Projection);
    m_SceneViewShader.setUniformMat4("view", View);
    for(std::vector<CGameObject>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it){
        glm::mat4 Model = it->getModelMatrix();
        m_SceneViewShader.setUniformMat4("model", Model);
        it->drawV(m_SceneViewShader);
    }
}

glm::mat4 CSceneView::__getProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_SceneViewCamera.getFOV(VERTICAL_FOV) / 2),
                            (float)this->width() / (float)this->height(),
                            m_SceneViewCamera.getZNear(),
                            m_SceneViewCamera.getZFar());
}

void CSceneView::__shakeSceneView(float vXOffset, float vYOffset, GLboolean vConstrainPitch)
{
    vXOffset *= m_MouseSensitivity;
    vYOffset *= m_MouseSensitivity;

    float Yaw = m_SceneViewCamera.getYaw();
    float Pitch = m_SceneViewCamera.getPitch();
    Yaw += vXOffset;
    Pitch += vYOffset;

    //vConstrainPitch = true防止翻转画面
    if (vConstrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    m_SceneViewCamera.setDirection(Yaw, Pitch);
}

void CSceneView::__zoomSceneView(float vYOffset)
{
    float Value = m_SceneViewCamera.getFOV(VERTICAL_FOV);
    Value -= (float)vYOffset;
    m_SceneViewCamera.setFOV(VERTICAL_FOV, Value);
}

void CSceneView::__moveSceneView(ESceneViewMovement vDirection)
{
    float DeltaTime = 1.0f / m_FPS;
    float Velocity = m_MovementSpeed * DeltaTime;
    glm::vec3 Position = m_SceneViewCamera.getPosition();
    glm::vec3 Front = m_SceneViewCamera.getFront();
    glm::vec3 Up = m_SceneViewCamera.getUp();
    glm::vec3 Right = m_SceneViewCamera.getRight();
    if (vDirection == FORWARD)
    {
        Position += Front * Velocity;
    }
    else if (vDirection == BACKWARD)
    {
        Position -= Front * Velocity;
    }
    else if (vDirection == LEFT)
    {
        Position -= Right * Velocity;
    }
    else if (vDirection == RIGHT)
    {
        Position += Right * Velocity;
    }
    else if (vDirection == UP)
    {
        Position += Up * Velocity;
    }
    else if (vDirection == DOWN)
    {
        Position -= Up * Velocity;
    }
    m_SceneViewCamera.setPosition(Position);
}

