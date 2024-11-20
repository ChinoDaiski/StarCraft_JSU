#include "stdafx.h"
#include "Timer.h"

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
	Release();
}

void CTimer::Initialize(void)
{
	m_dwTimer = 0;
}

int CTimer::Update(void)
{
	++m_dwTimer;

	return 0;
}

void CTimer::Late_Update(void)
{
	m_dwTimer %= MAXDWORD;
}

void CTimer::Render(HDC hDC)
{
}

void CTimer::Release(void)
{
}
