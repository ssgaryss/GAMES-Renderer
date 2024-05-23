#include <engine/cscene.h>



CScene::CScene()
{
}

void CScene::loadGameObject(CGameObject vGameObject)
{
    this->m_GameObjects.push_back(vGameObject);
}

void CScene::loadGameObject(const std::string &vPath, bool vGamma)
{
    CModel Model(vPath, vGamma);
    this->m_GameObjects.push_back(Model);
}
