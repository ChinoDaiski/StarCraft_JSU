#include "stdafx.h"
#include "Scarab.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"

CScarab::CScarab()
{
}


CScarab::~CScarab()
{
}

void CScarab::Initialize(void)
{
	m_bulletDC = CBitmapMgr::Get_Instance()->Find_Image(L"Scarab");
	m_bulletMoveDC = CBitmapMgr::Get_Instance()->Find_Image(L"Scarab_move");
	m_tbulletFrame.dwFrameSpeed = 10;
	m_tbulletFrame.iFrameStart = 0;
	m_tbulletFrame.iFrameCurr = 0;
	m_tbulletFrame.iFrameEnd = 8;
	m_tbulletFrame.iWidth = 84;
	m_tbulletFrame.iHeight = 84;
	m_tbulletFrame.dwFrameTime = GetTickCount();
	m_fSpeed = 10.f;
	m_bDead = false;
}

int CScarab::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	if (m_tbulletFrame.dwFrameTime + m_tbulletFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tbulletFrame.iFrameCurr;
		m_tbulletFrame.dwFrameTime = GetTickCount();

		if (m_tbulletFrame.iFrameCurr >= m_tbulletFrame.iFrameEnd)
			m_tbulletFrame.iFrameCurr = m_tbulletFrame.iFrameStart;
	}

	moveTarget();

	return OBJ_NOEVENT;
}

int CScarab::Late_Update(void)
{
	POINT pt;
	pt.x = m_pTarget->Get_Pos().x;
	pt.y = m_pTarget->Get_Pos().y;

	if (PtInRect(&m_tRect, pt)) {
		m_bDead = true;
		dynamic_cast<CUnit*>(m_pTarget)->Set_Damage(400);
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::SCARAB_EXPLO, pt.x, pt.y, 100.f, 100.f);
		CSoundMgr::Get_Instance()->PlaySoundW(L"psahit00.wav", CHANNELID::Bullet, UNIT_SOUND);

	}

	return 0;
}

void CScarab::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 스캐럽
	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),

		m_tInfo.fCX,
		m_tInfo.fCY,

		m_bulletDC,

		0,
		0,

		20,
		20,

		RGB(255, 255, 255));

	// 움직임
	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),

		m_tInfo.fCX,
		m_tInfo.fCY,

		m_bulletMoveDC,

		m_tbulletFrame.iWidth * m_tbulletFrame.iFrameCurr + 27,
		23,

		34,
		38,

		RGB(255, 255, 255));
}

void CScarab::Release(void)
{
}

void CScarab::moveTarget()
{
	if (nullptr != m_pTarget) {
		float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acosf(fWidth / fDistance);

		m_fAngle = fRadian * (180.f / PI);

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}

	if (nullptr == dynamic_cast<CUnit*>(m_pTarget))
		m_bDead = true;
}
