#include "stdafx.h"
#include "Effect.h"
#include "ScrollMgr.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

void CEffect::Initialize(void)
{
	m_bDead = false;
	m_tEffectFrame.dwFrameTime = 0;
}

int CEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();


	return 0;
}

int CEffect::Late_Update(void)
{
	if (m_tEffectFrame.dwFrameTime + m_tEffectFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tEffectFrame.iFrameCurr;
		m_tEffectFrame.dwFrameTime = GetTickCount();

		if (m_tEffectFrame.iFrameCurr >= m_tEffectFrame.iFrameEnd)
			m_bDead = true;
	}

	return 0;
}

void CEffect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),

		m_tInfo.fCX,
		m_tInfo.fCY,

		m_EffectDC,

		m_tEffectFrame.iWidth * m_tEffectFrame.iFrameCurr,
		0,

		m_tEffectFrame.iWidth,
		m_tEffectFrame.iHeight,

		RGB(255, 255, 255));
}

void CEffect::Release(void)
{
}

void CEffect::Set_EffectInfo(HDC _EffectDC, const FRAME& _tEffectFrame)
{
	m_EffectDC = _EffectDC;
	m_tEffectFrame = _tEffectFrame;
}
