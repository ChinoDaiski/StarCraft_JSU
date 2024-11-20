#include "stdafx.h"
#include "MainTitle.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "AnimateButton.h"
#include "MyButton.h"
#include "BitmapMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMainTitle::CMainTitle()
	:CScene(SCENEID::MAINGAME)
{
}

CMainTitle::~CMainTitle()
{
}

void CMainTitle::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(CHANNELID::BGM);

	CMouse::Get_Instance()->Set_InGame(false);

	// 싱글 플레이 버튼
	CObj* pObj = CAbstractFactory<CAnimateButton>::Create(200.f, 100.f);
	pObj->Set_Size(250.f, 250.f);
	pObj->Set_FrameKey(L"Main_SinglePlay");
	pObj->Set_Frame(FRAME(0, 35, 0, 320, 116));

	dynamic_cast<CAnimateButton*>(pObj)->Set_moveScene(SCENEID::SINGLEPLAY);
	dynamic_cast<CAnimateButton*>(pObj)->Set_Bmp_Base(CBitmapMgr::Get_Instance()->Find_Bitmap(L"Main_SinglePlay"));
	dynamic_cast<CAnimateButton*>(pObj)->Set_Bmp_Additional(CBitmapMgr::Get_Instance()->Find_Bitmap(L"Main_SinglePlay_On"));
	dynamic_cast<CAnimateButton*>(pObj)->Set_AdditionalFrameInfo(FRAME(0, 60, 0, 252, 124, 0, 100, 80));
	CObjMgr::Get_Instance()->Add_Object(SCENEID::MAINGAME, OBJID::BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(200.f, 100.f);
	pObj->Set_Size(250.f, 250.f);
	pObj->Set_FrameKey(L"Main_SinglePlay_Button");
	pObj->Set_Frame(FRAME(0, 0, 0, 143, 22));
	RECT rt = { 120, 200, 280, 250 };
	dynamic_cast<CMyButton*>(pObj)->Set_moveScene(SCENEID::SINGLEPLAY);
	dynamic_cast<CMyButton*>(pObj)->Set_RealRect(rt);
	CObjMgr::Get_Instance()->Add_Object(SCENEID::MAINGAME, OBJID::BUTTON, pObj);


	// 에디터 버튼
	pObj = CAbstractFactory<CAnimateButton>::Create(550.f, 150.f);
	pObj->Set_Size(250.f, 250.f);
	pObj->Set_FrameKey(L"Main_Editor");
	pObj->Set_Frame(FRAME(0, 85, 0, 160, 140, 50));

	dynamic_cast<CAnimateButton*>(pObj)->Set_Bmp_Base(CBitmapMgr::Get_Instance()->Find_Bitmap(L"Main_Editor"));
	dynamic_cast<CAnimateButton*>(pObj)->Set_Bmp_Additional(CBitmapMgr::Get_Instance()->Find_Bitmap(L"Main_Editor_On"));
	dynamic_cast<CAnimateButton*>(pObj)->Set_AdditionalFrameInfo(FRAME(0, 20, 0, 204, 132, 50, 30, 80));
	CObjMgr::Get_Instance()->Add_Object(SCENEID::MAINGAME, OBJID::BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(550.f, 150.f);
	pObj->Set_Size(250.f, 250.f);
	pObj->Set_FrameKey(L"Main_Editor_Button");
	pObj->Set_Frame(FRAME(0, 0, 0, 187, 25));
	rt = { 450, 200, 650, 250 };
	dynamic_cast<CMyButton*>(pObj)->Set_moveScene(SCENEID::EDITOR);
	dynamic_cast<CMyButton*>(pObj)->Set_RealRect(rt);
	CObjMgr::Get_Instance()->Add_Object(SCENEID::MAINGAME, OBJID::BUTTON, pObj);


	//// 나가기 버튼
	pObj = CAbstractFactory<CAnimateButton>::Create(550.f, 400.f);
	pObj->Set_Size(250.f, 250.f);
	pObj->Set_FrameKey(L"Main_Editor");
	pObj->Set_Frame(FRAME(0, 50, 0, 184, 128));

	dynamic_cast<CAnimateButton*>(pObj)->Set_Bmp_Base(CBitmapMgr::Get_Instance()->Find_Bitmap(L"Main_Exit"));
	dynamic_cast<CAnimateButton*>(pObj)->Set_Bmp_Additional(CBitmapMgr::Get_Instance()->Find_Bitmap(L"Main_Exit_On"));
	dynamic_cast<CAnimateButton*>(pObj)->Set_AdditionalFrameInfo(FRAME(0, 30, 0, 216, 136, 30, 10, 80));
	CObjMgr::Get_Instance()->Add_Object(SCENEID::MAINGAME, OBJID::BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(550.f, 400.f);
	pObj->Set_Size(250.f, 250.f);
	pObj->Set_FrameKey(L"Main_Exit_Button");
	pObj->Set_Frame(FRAME(0, 0, 0, 49, 24));
	rt = { 500, 500, 550, 550 };
	dynamic_cast<CMyButton*>(pObj)->Set_moveScene(SCENEID::EXIT);
	dynamic_cast<CMyButton*>(pObj)->Set_RealRect(rt);
	CObjMgr::Get_Instance()->Add_Object(SCENEID::MAINGAME, OBJID::BUTTON, pObj);

}

void CMainTitle::Update(void)
{
	Key_Input();
}

void CMainTitle::Late_Update(void)
{


}

void CMainTitle::Render(HDC _DC)
{
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Image(L"Main_Title");

	StretchBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 800, 600, SRCCOPY);
}

void CMainTitle::Release(void)
{
}

void CMainTitle::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE)) {
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::EXIT);
	}
}
