#include "stdafx.h"
#include "EditorButton.h"
#include "BitmapMgr.h"
#include "User.h"
#include "Mouse.h"
#include "KeyMgr.h"


CEditorButton::CEditorButton()
{
	
}

CEditorButton::~CEditorButton()
{
}

void CEditorButton::Initialize(void)
{
	m_DC = CBitmapMgr::Get_Instance()->Find_Image(m_pFrameKey);

	m_tInfo.fCX = BUTTON_SIZE;
	m_tInfo.fCY = BUTTON_SIZE;

	Update_Rect();
	m_tBInfo.rt = m_tRect;
}

int CEditorButton::Update(void)
{
	POINT	pt = CMouse::Get_Instance()->Get_Pos();
	if (PtInRect(&m_tRect, pt)) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			CUser::Get_Instance()->Set_BInfo(m_tBInfo);
	}

	return OBJ_NOEVENT;
}

int CEditorButton::Late_Update(void)
{
	return 0;
}

void CEditorButton::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	StretchBlt(hDC,				
		m_tRect.left,			
		m_tRect.top,			
		m_tInfo.fCX,			
		m_tInfo.fCY,
		m_DC,					
		0, 0,
		m_iWidth, m_iHeight,
		SRCCOPY);

	MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
	LineTo(hDC, m_tRect.left, m_tRect.bottom);
	LineTo(hDC, m_tRect.right, m_tRect.bottom);
	LineTo(hDC, m_tRect.right, m_tRect.top);
	LineTo(hDC, m_tRect.left, m_tRect.top);
}

void CEditorButton::Release(void)
{
}
