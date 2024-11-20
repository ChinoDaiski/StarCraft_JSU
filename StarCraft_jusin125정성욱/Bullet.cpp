#include "stdafx.h"
#include "Bullet.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_bulletDC = CBitmapMgr::Get_Instance()->Find_Image(L"Bullet");
	m_tbulletFrame.dwFrameSpeed = 10;
	m_tbulletFrame.iFrameStart = 0;
	m_tbulletFrame.iFrameCurr = 0;
	m_tbulletFrame.iFrameEnd = 5;
	m_tbulletFrame.iWidth = 32;
	m_tbulletFrame.iHeight = 32;
	m_tbulletFrame.dwFrameTime = GetTickCount();
	m_fSpeed = 10.f;
	m_bDead = false;

	CSoundMgr::Get_Instance()->PlaySoundW(L"dragbull.wav", CHANNELID::EFFECT, UNIT_SOUND);
}

int CBullet::Update(void)
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

int CBullet::Late_Update(void)
{
	POINT pt;
	pt.x = m_pTarget->Get_Pos().x;
	pt.y = m_pTarget->Get_Pos().y;

	if (PtInRect(&m_tRect, pt)) {
		m_bDead = true;
		dynamic_cast<CUnit*>(m_pTarget)->Set_Damage(200);
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::BALL_EXPLO, pt.x, pt.y, 30.f, 30.f);
		CSoundMgr::Get_Instance()->PlaySoundW(L"psahit00.wav", CHANNELID::Bullet, UNIT_SOUND);
	}

	return 0;
}

void CBullet::Render(HDC hDC)
{
	// РЏДж
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),

		m_tInfo.fCX,
		m_tInfo.fCY,

		m_bulletDC,

		m_tbulletFrame.iWidth * m_tbulletFrame.iFrameCurr + 6,
		6,

		22,
		20,

		RGB(255, 255, 255));
}

void CBullet::Release(void)
{
}

void CBullet::moveTarget()
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

	if (m_pTarget->Get_Dead())
		m_bDead = true;
}
