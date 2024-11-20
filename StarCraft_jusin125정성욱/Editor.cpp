#include "stdafx.h"
#include "Editor.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"
#include "User.h"
#include "MiniMap.h"
#include "TileMgr.h"
#include "EditorUI.h"
#include "UnitMgr.h"
#include "BuildMgr.h"
#include "SaveLoadMgr.h"
#include "SceneMgr.h"

CEditor::CEditor()
	:CScene(SCENEID::EDITOR)
{
}


CEditor::~CEditor()
{
}

void CEditor::Initialize(void)
{
	CMouse::Get_Instance()->Set_InGame(true);
	CMiniMap::Get_Instance()->Set_InGame(true);
	CTileMgr::Get_Instance()->Initialize();
	CUnitMgr::Get_Instance()->Initialize();
	CBuildMgr::Get_Instance()->Initialize();

	CScrollMgr::Get_Instance()->Set_Scroll((MAPCX >> 1) - 300, (MAPCY >> 1) - 300);
	CSaveLoadMgr::Get_Instance()->Load(L"../Data", SCENEID::EDITOR);
}

void CEditor::Update(void)
{
	// 키 관련 처리
	Key_Input();

	CScrollMgr::Get_Instance()->Scroll_Lock(MAPCX, MAPCY);

	CTileMgr::Get_Instance()->Update();

	CEditorUI::Get_Instance()->Update();

	CUnitMgr::Get_Instance()->Update();

	CBuildMgr::Get_Instance()->Update();
}

void CEditor::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();

	CUnitMgr::Get_Instance()->Late_Update();
}

void CEditor::Render(HDC _DC)
{
	// 맵 이미지
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Image(L"Single_Map");

	StretchBlt(
		_DC, 0, 0,
		WINCX, WINCY,
		hMemDC,
		(int)CScrollMgr::Get_Instance()->Get_ScrollX(),
		(int)CScrollMgr::Get_Instance()->Get_ScrollY(),
		WINCX, WINCY,
		SRCCOPY);

	CTileMgr::Get_Instance()->Render(_DC);
	CEditorUI::Get_Instance()->Render(_DC);
	CUnitMgr::Get_Instance()->Render(_DC);
}

void CEditor::Release(void)
{
	CTileMgr::Get_Instance()->Release(); 
	CUnitMgr::Get_Instance()->Release();
	CBuildMgr::Get_Instance()->Release();
}										

void CEditor::Key_Input(void)
{
	// 이동 관련 키
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		CScrollMgr::Get_Instance()->Set_ScrollX(-CUser::Get_Instance()->Get_Speed());
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		CScrollMgr::Get_Instance()->Set_ScrollX(CUser::Get_Instance()->Get_Speed());
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
		CScrollMgr::Get_Instance()->Set_ScrollY(-CUser::Get_Instance()->Get_Speed());
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
		CScrollMgr::Get_Instance()->Set_ScrollY(CUser::Get_Instance()->Get_Speed());
	}

	// save load 관련 키
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL)) {
		if (CKeyMgr::Get_Instance()->Key_Down('S'))
			CSaveLoadMgr::Get_Instance()->Save(L"../Data", SCENEID::EDITOR);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL)) {
		if (CKeyMgr::Get_Instance()->Key_Down('L'))
			CSaveLoadMgr::Get_Instance()->Load(L"../Data", SCENEID::EDITOR);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE)) {
		CMiniMap::Get_Instance()->Set_InGame(false);
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::MAINGAME);
	}

}