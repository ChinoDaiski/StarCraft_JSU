#include "stdafx.h"
#include "SinglePlayUI.h"
#include "BitmapMgr.h"
#include "UIButtonMgr.h"
#include "UnitUIMgr.h"

CSinglePlayUI::CSinglePlayUI()
{
}


CSinglePlayUI::~CSinglePlayUI()
{
}

void CSinglePlayUI::Initialize(void)
{
	CUIButtonMgr::Get_Instance()->Initialize();
	UnitUIMgr::Get_Instance()->Initialize();

	m_bitmapDC = CBitmapMgr::Get_Instance()->Find_Image(L"MainUI");

	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY - 400;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY - m_tInfo.fCY * 0.5;

	m_iLevel = 1;

	Update_Rect();
}

int CSinglePlayUI::Update(void)
{
	CUIButtonMgr::Get_Instance()->Update();
	UnitUIMgr::Get_Instance()->Update();

	return 0;
}

void CSinglePlayUI::Late_Update(void)
{
	CUIButtonMgr::Get_Instance()->Late_Update();
	UnitUIMgr::Get_Instance()->Late_Update();
}

void CSinglePlayUI::Render(HDC hDC)
{
	// MainUI
	TransparentBlt(
		hDC, 0, 0,
		WINCX, WINCY,
		m_bitmapDC,
		0, 0,
		800, 600,
		RGB(255, 255, 255));

	CUIButtonMgr::Get_Instance()->Render(hDC);
	UnitUIMgr::Get_Instance()->Render(hDC);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(10, 10, 10));

	CUser::Get_Instance()->PrintText(hDC, 0, 0, L"적 유닛 30마리 넘으면 패배!", 30);

	TCHAR strStage[32];
	swprintf_s(strStage, L"현재 스테이지 : %d", m_iLevel);
	CUser::Get_Instance()->PrintText(hDC, 0, 50, strStage, 30);

	TCHAR strUnitCnt[32];
	swprintf_s(strUnitCnt, L"전체 적 유닛수 : %d", CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::ENEMY)->size());
	CUser::Get_Instance()->PrintText(hDC, 0, 100, strUnitCnt, 30);

	TCHAR strDestroyUnit[32];
	swprintf_s(strDestroyUnit, L"파괴한 유닛 수 : %d", 1);
	CUser::Get_Instance()->PrintText(hDC, 0, 150, strDestroyUnit, 30);
}

void CSinglePlayUI::Release(void)
{
}

void CSinglePlayUI::Update_Rect(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}
