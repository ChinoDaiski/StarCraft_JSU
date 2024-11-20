#include "stdafx.h"
#include "UIMgr.h"
#include "Mouse.h"
#include "MiniMap.h"
#include "EditorUI.h"
#include "SceneMgr.h"
#include "User.h"
#include "SinglePlayUI.h"
#include "BuildMgr.h"
#include "EffectMgr.h"

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize(void)
{
	// 에디터 UI
	CEditorUI::Get_Instance()->Initialize();

	// 싱글플레이 UI
	CSinglePlayUI::Get_Instance()->Initialize();

	// 미니맵
	CMiniMap::Get_Instance()->Initialize();

	// 유저
	CUser::Get_Instance()->Initialize();

	// 마우스
	CMouse::Get_Instance()->Initialize();

	// 마우스 버튼 - 건물
	CBuildMgr::Get_Instance()->Initialize();
}

int CUIMgr::Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR)
		// 에디터 UI
		CEditorUI::Get_Instance()->Update();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY)
		// 싱글 플레이 UI
		CSinglePlayUI::Get_Instance()->Update();

	// 미니맵
	CMiniMap::Get_Instance()->Update();

	// 유저
	CUser::Get_Instance()->Update();

	// 마우스
	CMouse::Get_Instance()->Update();

	// 마우스 버튼 - 건물
	CBuildMgr::Get_Instance()->Update();

	return 0;
}

void CUIMgr::Late_Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR)
		// 에디터 UI
		CEditorUI::Get_Instance()->Late_Update();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY)
		// 싱글 플레이 UI
		CSinglePlayUI::Get_Instance()->Late_Update();

	// 미니맵
	CMiniMap::Get_Instance()->Late_Update();

	// 유저
	CUser::Get_Instance()->Late_Update();

	// 마우스
	CMouse::Get_Instance()->Late_Update();

	// 마우스 버튼 - 건물
	CBuildMgr::Get_Instance()->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		// 싱글 플레이 UI
		CMouse::Get_Instance()->Draw_DragRect(hDC);
		CSinglePlayUI::Get_Instance()->Render(hDC);
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR)
		// 에디터 UI
		CEditorUI::Get_Instance()->Render(hDC);

	// 미니맵
	CMiniMap::Get_Instance()->Render(hDC);

	// 유저
	CUser::Get_Instance()->Render(hDC);

	// 마우스 버튼 - 건물
	CBuildMgr::Get_Instance()->Render(hDC);

	// 마우스
	CMouse::Get_Instance()->Render(hDC);
}

void CUIMgr::Release(void)
{
}
