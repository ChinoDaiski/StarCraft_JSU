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

	GdiTransparentBlt(hDC,								// 복사받을 dc, 최종적으로 그림을 그릴 dc
		m_tRealRect.left + m_tFrame.iAdditionalWidth,	// 복사 받을 위치 x좌표
		m_tRealRect.top + m_tFrame.iAdditionalHeight,	// 복사 받을 위치 y좌표
		m_tRealRect.right - m_tRealRect.left,			// 복사 받을 이미지의 가로 사이즈
		m_tRealRect.bottom - m_tRealRect.top,			// 복사 받을 이미지의 세로 사이즈
		hMemDC,										// 현재 비트맵 이미지를 가지고 있는 dc
		m_tFrame.iWidth * m_iDrawID,				// 비트맵을 출력할 시작 좌표
		0,
		m_tFrame.iWidth,							// 복사할 비트맵의 가로, 세로 사이즈
		m_tFrame.iHeight,
		RGB(0, 4, 0));						// 제거하고자하는 색상
}

void CMyButton::Release(void)
{
	
}
