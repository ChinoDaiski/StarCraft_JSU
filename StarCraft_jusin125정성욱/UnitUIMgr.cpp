#include "stdafx.h"
#include "UnitUIMgr.h"
#include "User.h"
#include "Unit.h"

UnitUIMgr::UnitUIMgr()
{
}


UnitUIMgr::~UnitUIMgr()
{
}

void UnitUIMgr::Initialize(void)
{
	// 시작 위치			left, top				=> 204, 490		492, 590
	// 가로/세로 길이		Width, Height			=> 48, 50
	// 가로 6개 세로 2개

	int	iLeft = 204;
	int	iTop = 490;
	int	iWidth = 48;
	int	iHeight = 50;

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 6; ++j) {
			// 중점 위치 설정
			m_UnitWire[i * 6 + j].m_tInfo.fX = iLeft + (iWidth >> 1) + iWidth * j;
			m_UnitWire[i * 6 + j].m_tInfo.fY = iTop + (iHeight >> 1) + iHeight * i;

			// 가로 세로 길이 설정
			m_UnitWire[i * 6 + j].m_tInfo.fCX = iWidth;
			m_UnitWire[i * 6 + j].m_tInfo.fCY = iHeight;

			// Update_Rect 설정
			m_UnitWire[i * 6 + j].m_tRect.left = LONG(m_UnitWire[i * 6 + j].m_tInfo.fX - (m_UnitWire[i * 6 + j].m_tInfo.fCX / 2.f));
			m_UnitWire[i * 6 + j].m_tRect.top = LONG(m_UnitWire[i * 6 + j].m_tInfo.fY - (m_UnitWire[i * 6 + j].m_tInfo.fCY / 2.f));
			m_UnitWire[i * 6 + j].m_tRect.right = LONG(m_UnitWire[i * 6 + j].m_tInfo.fX + (m_UnitWire[i * 6 + j].m_tInfo.fCX / 2.f));
			m_UnitWire[i * 6 + j].m_tRect.bottom = LONG(m_UnitWire[i * 6 + j].m_tInfo.fY + (m_UnitWire[i * 6 + j].m_tInfo.fCY / 2.f));
		}
	}

	int a = 10;
}

int UnitUIMgr::Update(void)
{
	// 선택한 유닛들의 수가 1개보다 많다면, 여럿을 선택한 것이므로, 가지고 있는 정보를 설정한다.
	list<CObj*> lst = CUser::Get_Instance()->Get_SelectObjArr();

	// 선택한 유닛들의 수가 1개보다 많다면
	if (lst.size() > 1) {
		// 유닛들의 정보를 세팅한다.
		int i = 0;
		for (auto& iter = lst.begin(); iter != lst.end(); ++iter) {
			if (i < 12) {
				if ((*iter)->Get_Type() == OBJ_TYPE::UNIT)
					m_UnitWire[i++].m_smallDC = dynamic_cast<CUnit*>(*iter)->Get_WireFrameInfo().m_SmallWireDC;
				else
					continue;
			}
		}

	}



	return 0;
}

void UnitUIMgr::Late_Update(void)
{
}

void UnitUIMgr::Render(HDC hDC)
{
	// 세팅된 유닛의 작은 DC에 대한 정보를 특정 위치에 출력한다.

	list<CObj*> lst = CUser::Get_Instance()->Get_SelectObjArr();

	// 선택한 유닛의 갯수가 1보다 클 경우
	if (lst.size() > 1) {

		HPEN MyPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN OldPen = (HPEN)SelectObject(hDC, MyPen);

		for (int i = 0; i < lst.size(); ++i) {

			StretchBlt(
				hDC,
				m_UnitWire[i].m_tRect.left,
				m_UnitWire[i].m_tRect.top,
				m_UnitWire[i].m_tInfo.fCX,
				m_UnitWire[i].m_tInfo.fCY,
				m_UnitWire[i].m_smallDC,
				0, 0,
				32, 32,
				SRCCOPY
			);

			// 유닛 Small Wire 근처에 선 그리기
			MoveToEx(hDC, m_UnitWire[i].m_tRect.left, m_UnitWire[i].m_tRect.top, nullptr);
			LineTo(hDC, m_UnitWire[i].m_tRect.left, m_UnitWire[i].m_tRect.bottom);
			LineTo(hDC, m_UnitWire[i].m_tRect.right, m_UnitWire[i].m_tRect.bottom);
			LineTo(hDC, m_UnitWire[i].m_tRect.right, m_UnitWire[i].m_tRect.top);
			LineTo(hDC, m_UnitWire[i].m_tRect.left, m_UnitWire[i].m_tRect.top);
		}

		SelectObject(hDC, OldPen);
		DeleteObject(MyPen);
	}


}

void UnitUIMgr::Release(void)
{
}
