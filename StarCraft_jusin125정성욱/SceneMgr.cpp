
#include "stdafx.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MainTitle.h"
#include "SinglePlay.h"
#include "ObjMgr.h"
#include "Exit.h"
#include "Editor.h"
#include "SoundMgr.h"
#include "Win.h"
#include "Lose.h"

CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Push(SCENEID eID)
{

	switch (eID)
	{
	case SCENEID::LOGO:
		m_stScene.push(new CLogo);
		break;

	case SCENEID::MAINGAME:
		m_stScene.push(new CMainTitle);
		break;

	case SCENEID::SINGLEPLAY:
		m_stScene.push(new CSinglePlay);
		break;

	case SCENEID::EDITOR:
		m_stScene.push(new CEditor);
		break;

	case SCENEID::EXIT:
		m_stScene.push(new CExit);
		break;

	case SCENEID::WIN:
		m_stScene.push(new CWin);
		break;

	case SCENEID::LOSE:
		m_stScene.push(new CLose);
		break;
	}

	CObjMgr::Get_Instance()->Set_SceneID(eID);
	m_stScene.top()->Initialize();
}

void CSceneMgr::Scene_Pop()
{
	CObjMgr::Get_Instance()->Delete_SceneObj(m_stScene.top()->Get_ID());

	m_stScene.top()->Release();
	m_stScene.pop();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"button.wav", CHANNELID::UI, UNIT_SOUND);
	if (m_stScene.top()->Get_ID() != eID) {
		Scene_Pop();
		Scene_Push(eID);
	}
}

void CSceneMgr::Initialize(void)
{
	Scene_Push(SCENEID::LOGO);
	m_stScene.top()->Initialize();
}

int CSceneMgr::Update(void)
{
	m_stScene.top()->Update();
	return 0;
}

void CSceneMgr::Late_Update(void)
{
	m_stScene.top()->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_stScene.top()->Render(_DC);
}

void CSceneMgr::Release(void)
{
	while (!m_stScene.empty()) {
		m_stScene.top()->Release();
		m_stScene.pop();
	}

	DestroyWindow(g_hWnd);
}
