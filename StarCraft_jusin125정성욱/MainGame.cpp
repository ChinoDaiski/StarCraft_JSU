
#include "stdafx.h"
#include "MainGame.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "BitmapMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "MiniMap.h"
#include "UIMgr.h"

CMainGame::CMainGame()	
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	// 장면
	CSceneMgr::Get_Instance()->Initialize();

	// 오브젝트
	CObjMgr::Get_Instance()->Initialize();

	// UI - 미니맵, 마우스, 다른 UI등등
	CUIMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	// 장면
	CSceneMgr::Get_Instance()->Update();

	// 오브젝트
	CObjMgr::Get_Instance()->Update();

	// UI - 미니맵, 마우스, 다른 UI등등
	CUIMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	// 장면
	CSceneMgr::Get_Instance()->Late_Update();

	// 오브젝트
	CObjMgr::Get_Instance()->Late_Update();

	// UI - 미니맵, 마우스, 다른 UI등등
	CUIMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	TCHAR		szBuff[128] = L"", szFPS[32] = L"", szMousePos[32] = L"", szBulletCnt[32] = L"";

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(szFPS, L"FPS : %d", m_iFPS);

		POINT pt = CMouse::Get_Instance()->Get_Pos();
		swprintf_s(szMousePos, L", Mouse : %d, %d", pt.x, pt.y);
		swprintf_s(szBulletCnt, L", Bullet : %d", CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::BULLET)->size());



		lstrcpy(szBuff, szFPS);
		lstrcat(szBuff, szMousePos);
		lstrcat(szBuff, szBulletCnt);

		SetWindowText(g_hWnd, szBuff);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}


	HDC		hBackBufferDC = CBitmapMgr::Get_Instance()->Find_Image(L"Back");

	// 장면
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);

	// 오브젝트
	CObjMgr::Get_Instance()->Render(hBackBufferDC);

	// UI - 미니맵, 마우스, 다른 UI등등
	CUIMgr::Get_Instance()->Render(hBackBufferDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	// 사용이 끝난 dc를 소멸
	ReleaseDC(g_hWnd, m_DC);

	// 장면
	CSceneMgr::Get_Instance()->Release();

	// 오브젝트
	CObjMgr::Get_Instance()->Release();

	// UI - 미니맵, 마우스, 다른 UI등등
	CUIMgr::Get_Instance()->Release();
}
