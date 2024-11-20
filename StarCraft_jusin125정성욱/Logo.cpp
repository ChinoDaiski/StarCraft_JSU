#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "Mouse.h"

CLogo::CLogo()
	: CScene(SCENEID::LOGO)
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"MainBack.wav", CHANNELID::BGM, UNIT_SOUND);
	CResourceMgr::Get_Instance()->Load_Logo();
	CResourceMgr::Get_Instance()->Load_All();
	CSoundMgr::Get_Instance()->Initialize();
}

void CLogo::Update(void)
{
	Key_Input();
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		RECT rt;
		rt.left = 0;
		rt.top = 0;
		rt.right = 800;
		rt.bottom = 600;
		if (PtInRect(&rt, CMouse::Get_Instance()->Get_Pos()))
			CSceneMgr::Get_Instance()->Scene_Change(SCENEID::MAINGAME);
	}
}

void CLogo::Late_Update(void)
{

}

void CLogo::Render(HDC _DC)
{
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Image(L"Logo_Title");

	StretchBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 800, 600, SRCCOPY);
}

void CLogo::Release(void)
{

}

void CLogo::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE)) {
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::EXIT);
	}
}
