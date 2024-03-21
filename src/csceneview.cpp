#include <engine/csceneview.h>
#include <QDebug>


CSceneView::CSceneView(QWidget *parent)
    : QOpenGLWidget{parent}
{
}

CSceneView::CSceneView(const CSceneView &vSceneView)
    : m_SceneViewShader{vSceneView.m_SceneViewShader}, m_SceneViewCamera{vSceneView.m_SceneViewCamera}
{
}

void CSceneView::initializeGL()
{
    initializeOpenGLFunctions();
    CModel vModel("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/resources/objects/mary/Marry.obj");
    this->loadGameObject(vModel);
}

void CSceneView::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void CSceneView::paintGL()
{
    CShader vShader("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/src/shaders/model.vs",
                    "D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/src/shaders/model.fs");
    // CModel vModel("D:/Master_Learning_Qiuhuidi/CG/GAMES-Renderer/GAMES-Renderer/resources/objects/mary/Marry.obj"); //这个模型贴图已经翻转过了
    vShader.use();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 Projection = __getProjectionMatrix();
    glm::mat4 View = m_SceneViewCamera.getViewMatrix();
    ///////////////////////////////////////////
    glm::mat4 Model = glm::mat4(1.0f); //暂时如此
    vShader.setUniformMat4("projection", Projection);
    vShader.setUniformMat4("view", View);
    vShader.setUniformMat4("model", Model);
    // vModel._drawV(vShader);
    // __draw(vShader);
    update();
}

void CSceneView::keyPressEvent(QKeyEvent *vEvent)
{
    qDebug() << "press";
    qDebug() << "position:" << m_SceneViewCamera.getPosition().x;
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
}

void CSceneView::keyReleaseEvent(QKeyEvent *vEvent)
{
    // qDebug() << "press";
}

void CSceneView::__draw(CShader vShader)
{
    for(std::vector<CGameObject>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it){
        it->drawV(vShader);
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
    // float DeltaTime = 1.0f / m_FPS;
    // float Velocity = m_MovementSpeed * DeltaTime;
    float Velocity = 1.0f;
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
    m_SceneViewCamera.setPosition(Position);
}

