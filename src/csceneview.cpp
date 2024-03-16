#include <engine/csceneview.h>


CSceneView::CSceneView(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void CSceneView::initializeGL()
{
    initializeOpenGLFunctions();
}

void CSceneView::resizeGL(int w, int h)
{

}

void CSceneView::paintGL()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
