
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

	// ���
	CSceneMgr::Get_Instance()->Initialize();

	// ������Ʈ
	CObjMgr::Get_Instance()->Initialize();

	// UI - �̴ϸ�, ���콺, �ٸ� UI���
	CUIMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	// ���
	CSceneMgr::Get_Instance()->Update();

	// ������Ʈ
	CObjMgr::Get_Instance()->Update();

	// UI - �̴ϸ�, ���콺, �ٸ� UI���
	CUIMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	// ���
	CSceneMgr::Get_Instance()->Late_Update();

	// ������Ʈ
	CObjMgr::Get_Instance()->Late_Update();

	// UI - �̴ϸ�, ���콺, �ٸ� UI���
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

	// ���
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);

	// ������Ʈ
	CObjMgr::Get_Instance()->Render(hBackBufferDC);

	// UI - �̴ϸ�, ���콺, �ٸ� UI���
	CUIMgr::Get_Instance()->Render(hBackBufferDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	// ����� ���� dc�� �Ҹ�
	ReleaseDC(g_hWnd, m_DC);

	// ���
	CSceneMgr::Get_Instance()->Release();

	// ������Ʈ
	CObjMgr::Get_Instance()->Release();

	// UI - �̴ϸ�, ���콺, �ٸ� UI���
	CUIMgr::Get_Instance()->Release();
}
