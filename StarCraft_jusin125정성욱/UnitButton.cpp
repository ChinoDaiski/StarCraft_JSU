#include "stdafx.h"
#include "UnitButton.h"
#include "BitmapMgr.h"
#include "UIButtonMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"


CUnitButton::CUnitButton()
{
	Initialize();
}

CUnitButton::CUnitButton(BUTTON_UNIT _eButtonInfo)
	: m_eButtonInfo(_eButtonInfo)
{
	Initialize();
}

CUnitButton::~CUnitButton()
{
}

void CUnitButton::Initialize(void)
{
	m_DC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit");
}

int CUnitButton::Update(void)
{
	if (PtInRect(&m_tRect, CMouse::Get_Instance()->Get_Pos())) {

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			Click();
		}
	}
	return 0;
}

int CUnitButton::Late_Update(void)
{
	return 0;
}

void CUnitButton::Render(HDC hDC)
{
	StretchBlt(hDC,									// ������� dc, ���������� �׸��� �׸� dc

		m_tRect.left,								// ���� ���� ��ġ x��ǥ
		m_tRect.top,								// ���� ���� ��ġ y��ǥ

		(int)m_tInfo.fCX,							// ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,							// ���� ���� �̹����� ���� ������

		m_DC,										// ���� ��Ʈ�� �̹����� ������ �ִ� dc

		(int)m_tFrame.iWidth * m_iDrawID,			// ��Ʈ���� ����� ���� ��ǥ
		(int)m_tFrame.iHeight * (int)m_eButtonInfo,

		(int)m_tFrame.iWidth,						// ������ ��Ʈ���� ����, ���� ������
		(int)m_tFrame.iHeight,

		SRCCOPY);
}

void CUnitButton::Release(void)
{
}

void CUnitButton::Click(void)
{
	m_iDrawID = 1;
	CUIButtonMgr::Get_Instance()->ClickButton(m_eButtonInfo);
}