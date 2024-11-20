#include "stdafx.h"
#include "UpgradeButton.h"
#include "BitmapMgr.h"
#include "UIButtonMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"

CUpgradeButton::CUpgradeButton()
{
	Initialize();
}

CUpgradeButton::CUpgradeButton(BUTTON_UPGRADE _eButtonInfo)
	: m_eButtonInfo(_eButtonInfo)
{
	Initialize();
}


CUpgradeButton::~CUpgradeButton()
{
}

void CUpgradeButton::Initialize(void)
{
	m_DC = CBitmapMgr::Get_Instance()->Find_Image(L"Upgrade");
}

int CUpgradeButton::Update(void)
{
	if (PtInRect(&m_tRect, CMouse::Get_Instance()->Get_Pos())) {

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			Click();
		}
	}
	return 0;
}

int CUpgradeButton::Late_Update(void)
{
	return 0;
}

void CUpgradeButton::Render(HDC hDC)
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

void CUpgradeButton::Release(void)
{
}

void CUpgradeButton::Click(void)
{
	m_iDrawID = 1;
	CUIButtonMgr::Get_Instance()->ClickButton(m_eButtonInfo);
}