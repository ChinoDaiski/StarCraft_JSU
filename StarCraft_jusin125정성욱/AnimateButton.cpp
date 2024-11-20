#include "stdafx.h"
#include "AnimateButton.h"
#include "SceneMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "BitmapMgr.h"


CAnimateButton::CAnimateButton()
{
}


CAnimateButton::~CAnimateButton()
{
	Release(); 
}

void CAnimateButton::Initialize(void)
{
	m_moveScene = SCENEID::END;
	m_bLock = false;
}

int CAnimateButton::Update(void)
{
	// 활성화가 되지 않았다면, 넘긴다.
	if (m_bLock)
		return OBJ_NOEVENT;

	Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

int CAnimateButton::Late_Update(void)
{
	// 활성화가 되지 않았다면, 넘긴다.
	if (m_bLock)
		return OBJ_NOEVENT;

}

void CAnimateButton::Render(HDC hDC)
{
	// 활성화가 되지 않았다면, 넘긴다.
	if (m_bLock)
		return;

	HDC	hMemDC = m_BitMap_Base->Get_MemDC();

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,

		m_tRect.right - m_tRect.left,
		m_tRect.bottom - m_tRect.top,

		hMemDC,

		m_tFrame.iWidth * m_tFrame.iFrameCurr,
		m_tFrame.iHeight * (int)m_tFrame.iFrameScene,

		m_tFrame.iWidth,
		m_tFrame.iHeight,

		RGB(255, 255, 255));


	// 마우스와 버튼이 충돌했을 경우
	POINT pt = CMouse::Get_Instance()->Get_Pos();

	if (PtInRect(&m_tRect, pt)) {

		hMemDC = m_BitMap_Additional->Get_MemDC();

		GdiTransparentBlt(hDC,
			m_tRect.left + m_tFrameAdditional.iAdditionalWidth,
			m_tRect.top + m_tFrameAdditional.iAdditionalHeight,

			m_tRect.right - m_tRect.left,
			m_tRect.bottom - m_tRect.top,

			hMemDC,

			m_tFrameAdditional.iWidth * m_tFrameAdditional.iFrameCurr,
			m_tFrameAdditional.iHeight * (int)m_tFrameAdditional.iFrameScene,

			m_tFrameAdditional.iWidth,
			m_tFrameAdditional.iHeight,

			RGB(255, 255, 255));

		Move_AdditionalFrame();
	}

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//GdiTransparentBlt(hDC,				// 복사받을 dc, 최종적으로 그림을 그릴 dc
	//	m_tRect.left,					// 복사 받을 위치 x좌표
	//	m_tRect.top,					// 복사 받을 위치 y좌표
	//	(int)m_tInfo.fCX,				// 복사 받을 이미지의 가로 사이즈
	//	(int)m_tInfo.fCY,				// 복사 받을 이미지의 세로 사이즈
	//	hMemDC,							// 현재 비트맵 이미지를 가지고 있는 dc
	//	(int)m_tInfo.fCX * m_bCollision,	// 비트맵을 출력할 시작 좌표
	//	0,
	//	(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 사이즈
	//	(int)m_tInfo.fCY,
	//	RGB(255, 255, 255));			// 제거하고자하는 색상
}

void CAnimateButton::Release(void)
{

}

void CAnimateButton::Move_AdditionalFrame(void)
{
	if (m_tFrameAdditional.dwFrameTime + m_tFrameAdditional.dwFrameSpeed < GetTickCount())
	{
		++m_tFrameAdditional.iFrameCurr;
		m_tFrameAdditional.dwFrameTime = GetTickCount();

		if (m_tFrameAdditional.iFrameCurr >= m_tFrameAdditional.iFrameEnd)
			m_tFrameAdditional.iFrameCurr = 0;
	}
}
