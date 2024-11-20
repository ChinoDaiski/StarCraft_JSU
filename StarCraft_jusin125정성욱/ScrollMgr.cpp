#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Initialize(void)
{
}

int CScrollMgr::Update(void)
{
	return 0;
}

void CScrollMgr::Late_Update(void)
{
}

void CScrollMgr::Render(HDC hDC)
{
}

void CScrollMgr::Release(void)
{
}

void CScrollMgr::Scroll_Lock(int _iCX, int _iCY)
{
	if (0.f > m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f > m_fScrollY)
		m_fScrollY = 0.f;

	if (m_fScrollX + WINCX > _iCX)
		m_fScrollX = int(_iCX - WINCX);

	if (m_fScrollY + WINCY > _iCY)
		m_fScrollY = int(_iCY - WINCY);
}
