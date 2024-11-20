#include "stdafx.h"
#include "Lose.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CLose::CLose()
	: CScene(SCENEID::LOSE)
{
}


CLose::~CLose()
{
}

void CLose::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySoundW(L"prescue.wav", CHANNELID::UI, BGM_SOUND);
}

void CLose::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::EXIT);
	}
}

void CLose::Late_Update(void)
{
}

void CLose::Render(HDC _DC)
{
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Image(L"Lose");

	StretchBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 800, 600, SRCCOPY);
}

void CLose::Release(void)
{
}

void CLose::Key_Input(void)
{
}
