#ifndef CSCENEVIEW_H
#define CSCENEVIEW_H

#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>
#include <QOpenGLWidget>
#include <QKeyEvent>

#include <engine/cshader.h>
#include <engine/ccamera.h>
#include <engine/cscene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <engine/cmodel.h>

enum ESceneViewMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class CSceneView : public QOpenGLWidget,QOpenGLFunctions_3_3_Core, CScene
{
    Q_OBJECT
public:
    explicit CSceneView(QWidget *parent = nullptr);
    CSceneView(const CSceneView &vSceneView);
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
protected:
    virtual void keyPressEvent(QKeyEvent *vEvent) override;
    virtual void keyReleaseEvent(QKeyEvent *vEvent) override;
private:
    // QOpenGLContext *m_Context;
    CShader m_SceneViewShader; //渲染该视图的渲染器
    CCamera m_SceneViewCamera;
    float m_MovementSpeed = 2.5f; //移动速度
    float m_MouseSensitivity = 0.1f; //灵敏度

    void __draw(CShader vShader); //绘制出当前视点的画面
    glm::mat4 __getProjectionMatrix() const; //生成projection matrix

    void __shakeSceneView(float vXOffset, float vYOffset, GLboolean vConstrainPitch); //看不同方向
    void __zoomSceneView(float vYOffset); //变焦
    void __moveSceneView(ESceneViewMovement vDirection); //wasd移动
    // public slots:
    //     void getKey(QKeyEvent *vEvent); //监听键盘
};

#endif // CSCENEVIEW_H
