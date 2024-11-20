#include "stdafx.h"
#include "UIButton.h"
#include "KeyMgr.h"
#include "BitmapMgr.h"


CUIButton::CUIButton()
	: CObj(), m_iDrawID(0)
{
	m_tInfo.fCX = UNIT_BUTTON_WIDTH;
	m_tInfo.fCY = UNIT_BUTTON_HEIGHT;

	m_tFrame.iWidth = 35;
	m_tFrame.iHeight = 35;
}

CUIButton::~CUIButton()
{
}
//
//void CUIButton::Initialize(void)
//{
//
//}
//
//int CUIButton::Update(void)
//{
//}
//
//int CUIButton::Late_Update(void)
//{
//	//POINT	Pt{};
//
//	//GetCursorPos(&Pt);
//	//ScreenToClient(g_hWnd, &Pt);
//
//	//if (PtInRect(&m_tRect, Pt))
//	//{
//	//	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
//	//	{
//	//		Click(true);
//	//	}
//
//	//	m_iDrawID = 1;
//	//}
//	//else
//	//	m_iDrawID = 0;
//
//	return 0;
//}
//
//void CUIButton::Render(HDC hDC)
//{
//
//}
//
//void CUIButton::Release(void)
//{
//}