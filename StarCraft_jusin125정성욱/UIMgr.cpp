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
	// ������ UI
	CEditorUI::Get_Instance()->Initialize();

	// �̱��÷��� UI
	CSinglePlayUI::Get_Instance()->Initialize();

	// �̴ϸ�
	CMiniMap::Get_Instance()->Initialize();

	// ����
	CUser::Get_Instance()->Initialize();

	// ���콺
	CMouse::Get_Instance()->Initialize();

	// ���콺 ��ư - �ǹ�
	CBuildMgr::Get_Instance()->Initialize();
}

int CUIMgr::Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR)
		// ������ UI
		CEditorUI::Get_Instance()->Update();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY)
		// �̱� �÷��� UI
		CSinglePlayUI::Get_Instance()->Update();

	// �̴ϸ�
	CMiniMap::Get_Instance()->Update();

	// ����
	CUser::Get_Instance()->Update();

	// ���콺
	CMouse::Get_Instance()->Update();

	// ���콺 ��ư - �ǹ�
	CBuildMgr::Get_Instance()->Update();

	return 0;
}

void CUIMgr::Late_Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR)
		// ������ UI
		CEditorUI::Get_Instance()->Late_Update();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY)
		// �̱� �÷��� UI
		CSinglePlayUI::Get_Instance()->Late_Update();

	// �̴ϸ�
	CMiniMap::Get_Instance()->Late_Update();

	// ����
	CUser::Get_Instance()->Late_Update();

	// ���콺
	CMouse::Get_Instance()->Late_Update();

	// ���콺 ��ư - �ǹ�
	CBuildMgr::Get_Instance()->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		// �̱� �÷��� UI
		CMouse::Get_Instance()->Draw_DragRect(hDC);
		CSinglePlayUI::Get_Instance()->Render(hDC);
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR)
		// ������ UI
		CEditorUI::Get_Instance()->Render(hDC);

	// �̴ϸ�
	CMiniMap::Get_Instance()->Render(hDC);

	// ����
	CUser::Get_Instance()->Render(hDC);

	// ���콺 ��ư - �ǹ�
	CBuildMgr::Get_Instance()->Render(hDC);

	// ���콺
	CMouse::Get_Instance()->Render(hDC);
}

void CUIMgr::Release(void)
{
}
