#ifndef CSCENEVIEW_H
#define CSCENEVIEW_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

#include <engine/cshader.h>
#include <glm/glm.hpp>

class CSceneView : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
public:
    explicit CSceneView(QWidget *parent = nullptr);
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
};

#endif // CSCENEVIEW_H
