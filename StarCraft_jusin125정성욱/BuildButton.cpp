#include "stdafx.h"
#include "BuildButton.h"
#include "BitmapMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "UIButtonMgr.h"

CBuildButton::CBuildButton()
{
	Initialize();
}

CBuildButton::CBuildButton(BUTTON_BUILD _eButtonInfo)
	: m_eButtonInfo(_eButtonInfo)
{
	Initialize();
}

CBuildButton::~CBuildButton()
{
}

void CBuildButton::Initialize(void)
{
	m_DC = CBitmapMgr::Get_Instance()->Find_Image(L"Build");
}

int CBuildButton::Update(void)
{
	if (PtInRect(&m_tRect, CMouse::Get_Instance()->Get_Pos())) {

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			Click();
		}
	}

	return 0;
}

int CBuildButton::Late_Update(void)
{
	return 0;
}

void CBuildButton::Render(HDC hDC)
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

void CBuildButton::Release(void)
{
}

void CBuildButton::Click(void)
{
	m_iDrawID = 1;
	CUIButtonMgr::Get_Instance()->ClickButton(m_eButtonInfo);
}