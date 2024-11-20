#include "stdafx.h"
#include "Win.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CWin::CWin()
	: CScene(SCENEID::WIN)
{
}


CWin::~CWin()
{
}

void CWin::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"youwin.wav", BGM_SOUND);	
}

void CWin::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::EXIT);
	}
}

void CWin::Late_Update(void)
{
}

void CWin::Render(HDC _DC)
{
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Image(L"Win");

	StretchBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 800, 600, SRCCOPY);
}

void CWin::Release(void)
{
}

void CWin::Key_Input(void)
{
}
