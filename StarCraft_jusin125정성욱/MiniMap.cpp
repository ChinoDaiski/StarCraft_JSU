#include "stdafx.h"
#include "MiniMap.h"
#include "BitmapMgr.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"

CMiniMap::CMiniMap()
{
}


CMiniMap::~CMiniMap()
{
}

void CMiniMap::Initialize(void)
{
	m_tStartPos.x = 8;
	m_tStartPos.y = 435;

	m_iWidth = 160;
	m_iHeight = 160;

	m_tInfo.fCX = WINCX * m_iWidth / MAPCX;
	m_tInfo.fCY = WINCY * m_iHeight / MAPCY;

	m_bInGame = false;

	m_tMinimapRect.left = m_tStartPos.x;
	m_tMinimapRect.top = m_tStartPos.y;
	m_tMinimapRect.right = m_tStartPos.x + m_iWidth;
	m_tMinimapRect.bottom = m_tStartPos.y + m_iHeight;
}

int CMiniMap::Update(void)
{
	if (m_bInGame) {
		m_tInfo.fX = (CScrollMgr::Get_Instance()->Get_ScrollX() + WINCX * 0.5)* m_iWidth / MAPCX + m_tStartPos.x;
		m_tInfo.fY = (CScrollMgr::Get_Instance()->Get_ScrollY() + WINCY * 0.5) * m_iHeight / MAPCY + m_tStartPos.y;

		Update_MiniMap();

		RECT rt = { m_tStartPos.x, m_tStartPos.y, m_tStartPos.x + m_iWidth, m_tStartPos.y + m_iHeight };
		POINT pt = CMouse::Get_Instance()->Get_Pos();

		// 만약 마우스의 위치가 미니맵 안에 있을 경우
		if (m_tStartPos.x <= pt.x && pt.x <= (m_tStartPos.x + m_iWidth) &&
			m_tStartPos.y <= pt.y && pt.y <= (m_tStartPos.y + m_iHeight) &&
			CMouse::Get_Instance()->Get_Status() != MOUSE_STATUS::DRAG) {

			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON)) {
				m_tInfo.fX = pt.x;
				m_tInfo.fY = pt.y;

				if (m_tInfo.fX < (m_tStartPos.x + m_tInfo.fCX * 0.5))
					m_tInfo.fX = m_tStartPos.x + m_tInfo.fCX * 0.5;
				if (m_tInfo.fX > (m_tStartPos.x + m_iWidth - m_tInfo.fCX * 0.5))
					m_tInfo.fX = m_tStartPos.x + m_iWidth - m_tInfo.fCX * 0.5;

				if (m_tInfo.fY < (m_tStartPos.y + m_tInfo.fCY * 0.5))
					m_tInfo.fY = m_tStartPos.y + m_tInfo.fCY * 0.5;
				if (m_tInfo.fY > (m_tStartPos.y + m_iHeight - m_tInfo.fCY * 0.5))
					m_tInfo.fY = m_tStartPos.y + m_iHeight - m_tInfo.fCY * 0.5;

				CScrollMgr::Get_Instance()->Set_Scroll(
					(m_tInfo.fX - m_tStartPos.x) * MAPCX / m_iWidth - WINCX * 0.5,
					(m_tInfo.fY - m_tStartPos.y) * MAPCY / m_iHeight - WINCY * 0.5
				);
			}
		}
	}

	return 0;
}

void CMiniMap::Late_Update(void)
{
	if (m_bInGame) {
	
	}
	return;
}

void CMiniMap::Render(HDC _DC)
{
	if (m_bInGame) {

		HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Image(L"Single_Mini_Map");

		StretchBlt(
			_DC,
			m_tStartPos.x,
			m_tStartPos.y,
			160, 160,
			hMemDC,
			0,
			0,
			m_iWidth, m_iHeight,
			SRCCOPY);

		//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
		HPEN oldPen = (HPEN)SelectObject(_DC, myPen);

		MoveToEx(_DC, m_tRect.left, m_tRect.top, nullptr);
		LineTo(_DC, m_tRect.left, m_tRect.bottom);
		LineTo(_DC, m_tRect.right, m_tRect.bottom);
		LineTo(_DC, m_tRect.right, m_tRect.top);
		LineTo(_DC, m_tRect.left, m_tRect.top);

		SelectObject(_DC, oldPen);
		DeleteObject(myPen);
	}
}

void CMiniMap::Release(void)
{
}

void CMiniMap::Update_MiniMap(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}