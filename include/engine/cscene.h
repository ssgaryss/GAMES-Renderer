#ifndef CSCENE_H
#define CSCENE_H

#include <engine/cgameobject.h>
#include <vector>

class CScene
{
public:
    CScene();
    void loadGameObject(CGameObject &vGameObject); //加载GameObject
protected:
    std::vector<CGameObject> m_GameObjects; //场景中的物体
signals:
};


#endif // CSCENE_H
