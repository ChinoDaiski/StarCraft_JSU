#include "stdafx.h"
#include "ActionButton.h"
#include "BitmapMgr.h"
#include "Mouse.h"
#include "UIButtonMgr.h"
#include "KeyMgr.h"

CActionButton::CActionButton()
	: CUIButton()
{
	Initialize();
}

CActionButton::CActionButton(BUTTON_ACTION _eButtonInfo)
	: CUIButton(), m_eButtonInfo(_eButtonInfo)
{
	Initialize();
}


CActionButton::~CActionButton()
{
}

void CActionButton::Initialize(void)
{
	m_DC = CBitmapMgr::Get_Instance()->Find_Image(L"Action");
}

int CActionButton::Update(void)
{
	if (PtInRect(&m_tRect, CMouse::Get_Instance()->Get_Pos())) {

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			Click();
		}

	}

	return 0;
}

int CActionButton::Late_Update(void)
{
	return 0;
}

void CActionButton::Render(HDC hDC)
{
	StretchBlt(hDC,									// 복사받을 dc, 최종적으로 그림을 그릴 dc

		m_tRect.left,								// 복사 받을 위치 x좌표
		m_tRect.top,								// 복사 받을 위치 y좌표

		(int)m_tInfo.fCX,							// 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,							// 복사 받을 이미지의 세로 사이즈

		m_DC,										// 현재 비트맵 이미지를 가지고 있는 dc

		(int)m_tFrame.iWidth * m_iDrawID,			// 비트맵을 출력할 시작 좌표
		(int)m_tFrame.iHeight * (int)m_eButtonInfo,

		(int)m_tFrame.iWidth,						// 복사할 비트맵의 가로, 세로 사이즈
		(int)m_tFrame.iHeight,

		SRCCOPY);
}

void CActionButton::Release(void)
{
}

void CActionButton::Click(void)
{
	m_iDrawID = 1;
	CUIButtonMgr::Get_Instance()->ClickButton(m_eButtonInfo);
}