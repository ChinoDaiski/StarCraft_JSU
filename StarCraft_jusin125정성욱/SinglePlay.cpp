#include "stdafx.h"
#include "SinglePlay.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "User.h"
#include "MiniMap.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "MiniMap.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "SaveLoadMgr.h"
#include "TileMgr.h"
#include "BuildMgr.h"
#include "UIButtonMgr.h"
#include "UnitMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"
#include "SinglePlayUI.h"

CSinglePlay::CSinglePlay()
	:CScene(SCENEID::SINGLEPLAY)
{
}

CSinglePlay::~CSinglePlay()
{
}

void CSinglePlay::Initialize(void)
{
	m_bWin = false;
	dwWinTime = GetTickCount();
	dwWinSpeed = 180000;
	//dwWinSpeed = 10000;

	m_bLose = false;
	dwLoseSpeed = 3000;

	m_iLevel = 1;
	dwLevelTime = GetTickCount();
	dwLevelSpeed = 30000;


	CSoundMgr::Get_Instance()->PlaySoundW(L"protoss.wav", CHANNELID::BGM, BGM_SOUND);

	for (int i = 0; i < (int)UNIT_NAME::END; ++i)
		dwFrameTime[i] = GetTickCount();
	for (int i = 0; i < (int)UNIT_NAME::END; ++i)
		dwFrameSpeed[i] = rand() % 60000 + 10000;

	CUnitMgr::Get_Instance()->Initialize();
	CEffectMgr::Get_Instance()->Initialize();

	// 맵의 중앙으로 스크롤을 적용
	CScrollMgr::Get_Instance()->Set_Scroll((MAPCX >> 1) - 400, (MAPCY >> 1) - 500);

	CMouse::Get_Instance()->Set_InGame(true);
	CMiniMap::Get_Instance()->Set_InGame(true);
	CTileMgr::Get_Instance()->Initialize();

	CSaveLoadMgr::Get_Instance()->Load(L"../Data", SCENEID::SINGLEPLAY);
}

void CSinglePlay::Update(void)
{
	Key_Input();

	CScrollMgr::Get_Instance()->Scroll_Lock(MAPCX, MAPCY);

	for (int i = 0; i < (int)UNIT_NAME::END; ++i) {
		if (dwFrameTime[i] + dwFrameSpeed[i] < GetTickCount())
		{
			dwFrameTime[i] = GetTickCount();

			int iX = (MAPCX >> 1) - 420;
			int iY = (MAPCY >> 1) - 440;

			if (CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::ENEMY)->size() <= 30)
				if (!m_bLose)
					CUnitMgr::Get_Instance()->Create_EnemyUnit(UNIT_NAME(i), iX, iY, SCENEID::SINGLEPLAY);
		}
	}


	if (dwLevelTime + dwLevelSpeed < GetTickCount())
	{
		dwLevelTime = GetTickCount();
		++m_iLevel;

		for (int i = 0; i < (int)UNIT_NAME::END; ++i)
			dwFrameSpeed[i] = rand() % (30000 - m_iLevel * 3000) + 5000;
	}

	CSinglePlayUI::Get_Instance()->Set_Level(m_iLevel);

	CUnitMgr::Get_Instance()->Update();

	if (CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::ENEMY)->size() > 30) {
		CObjMgr::Get_Instance()->DeadAll(SCENEID::SINGLEPLAY, OBJID::ENEMY);
		m_bLose = true;
		dwLoseTime = GetTickCount();
	}

	if (m_bLose) {
		if (dwLoseTime + dwLoseSpeed < GetTickCount()) {
			CMiniMap::Get_Instance()->Set_InGame(false);
			CSceneMgr::Get_Instance()->Scene_Change(SCENEID::LOSE);
		}
	}


	if (dwWinTime + dwWinSpeed < GetTickCount())
		m_bWin = true;

	if (m_bWin) {
		CMiniMap::Get_Instance()->Set_InGame(false);
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::WIN);
	}
}

void CSinglePlay::Late_Update(void)
{
}

void CSinglePlay::Render(HDC _DC)
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

	CUnitMgr::Get_Instance()->Render(_DC);


	TCHAR strDestroyUnit[32];
	swprintf_s(strDestroyUnit, L"남은 시간 : %.2f", 1.f * (dwWinSpeed - (GetTickCount() - dwWinTime)) / 1000.f);
	CUser::Get_Instance()->PrintText(_DC, 0, 200, strDestroyUnit, 30);
}

void CSinglePlay::Release(void)
{
	CUser::Destroy_Instance();
}

void CSinglePlay::Key_Input(void)
{
	// 이동 관련 키 처리
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
			CSaveLoadMgr::Get_Instance()->Save(L"../Data", SCENEID::SINGLEPLAY);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL)) {
		if (CKeyMgr::Get_Instance()->Key_Down('L'))
			; // CSaveLoadMgr::Get_Instance()->Load(L"../Data", SCENEID::SINGLEPLAY);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE)) {
		CBuildMgr::Get_Instance()->Set_CurrBuild(BUILD::END);
		CUIButtonMgr::Get_Instance()->Clear_ButtonInfo();

		CMiniMap::Get_Instance()->Set_InGame(false);
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::MAINGAME);
	}
}
