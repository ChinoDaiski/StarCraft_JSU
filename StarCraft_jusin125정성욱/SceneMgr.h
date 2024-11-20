#pragma once

#include "Include.h"
#include "Scene.h"

class CSceneMgr : public CSingleton<CSceneMgr>
{
public:
	CSceneMgr();
	virtual ~CSceneMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Scene_Push(SCENEID eID);
	void	Scene_Pop();
	void	Scene_Change(SCENEID eID);

public:
	SCENEID		Get_SceneID(void) const {
		return m_stScene.top()->Get_ID();
	}

private:
	stack<CScene*>						m_stScene;
};

