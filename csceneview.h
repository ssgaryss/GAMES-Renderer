#ifndef CSCENEVIEW_H
#define CSCENEVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class CSceneView:public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
public:
    explicit CSceneView(QWidget *parent = nullptr);
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
};

#endif // CSCENEVIEW_H
