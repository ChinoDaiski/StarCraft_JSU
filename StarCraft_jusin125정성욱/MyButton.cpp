#include "stdafx.h"
#include "MyButton.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "SoundMgr.h"


CMyButton::CMyButton()
	: m_iDrawID(0)
{
}


CMyButton::~CMyButton()
{
}

void CMyButton::Initialize(void)
{

}

int CMyButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CMyButton::Late_Update(void)
{
	POINT	pt = CMouse::Get_Instance()->Get_Pos();

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"button.wav", CHANNELID::Button, UNIT_SOUND);
			CSceneMgr::Get_Instance()->Scene_Change(m_moveScene);

			return OBJ_CHANGE;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;

	return OBJ_NOEVENT;
}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBitmapMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,								// ������� dc, ���������� �׸��� �׸� dc
		m_tRealRect.left + m_tFrame.iAdditionalWidth,	// ���� ���� ��ġ x��ǥ
		m_tRealRect.top + m_tFrame.iAdditionalHeight,	// ���� ���� ��ġ y��ǥ
		m_tRealRect.right - m_tRealRect.left,			// ���� ���� �̹����� ���� ������
		m_tRealRect.bottom - m_tRealRect.top,			// ���� ���� �̹����� ���� ������
		hMemDC,										// ���� ��Ʈ�� �̹����� ������ �ִ� dc
		m_tFrame.iWidth * m_iDrawID,				// ��Ʈ���� ����� ���� ��ǥ
		0,
		m_tFrame.iWidth,							// ������ ��Ʈ���� ����, ���� ������
		m_tFrame.iHeight,
		RGB(0, 4, 0));						// �����ϰ����ϴ� ����
}

void CMyButton::Release(void)
{
	
}
