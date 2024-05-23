#ifndef CSCENE_H
#define CSCENE_H

#include <engine/cgameobject.h>
#include <engine/cmodel.h>
#include <vector>

class CScene
{
public:
    CScene();
    void loadGameObject(CGameObject vGameObject); //加载GameObject
    void loadGameObject(std::string const& vPath, bool vGamma = false);
protected:
    std::vector<CGameObject> m_GameObjects; //场景中的物体集合
    std::vector<CShader> m_SceneViewShaders; //场景中的渲染器集合
signals:
};


#endif // CSCENE_H
