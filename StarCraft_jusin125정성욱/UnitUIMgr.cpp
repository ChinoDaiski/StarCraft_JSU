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
	// ���� ��ġ			left, top				=> 204, 490		492, 590
	// ����/���� ����		Width, Height			=> 48, 50
	// ���� 6�� ���� 2��

	int	iLeft = 204;
	int	iTop = 490;
	int	iWidth = 48;
	int	iHeight = 50;

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 6; ++j) {
			// ���� ��ġ ����
			m_UnitWire[i * 6 + j].m_tInfo.fX = iLeft + (iWidth >> 1) + iWidth * j;
			m_UnitWire[i * 6 + j].m_tInfo.fY = iTop + (iHeight >> 1) + iHeight * i;

			// ���� ���� ���� ����
			m_UnitWire[i * 6 + j].m_tInfo.fCX = iWidth;
			m_UnitWire[i * 6 + j].m_tInfo.fCY = iHeight;

			// Update_Rect ����
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
	// ������ ���ֵ��� ���� 1������ ���ٸ�, ������ ������ ���̹Ƿ�, ������ �ִ� ������ �����Ѵ�.
	list<CObj*> lst = CUser::Get_Instance()->Get_SelectObjArr();

	// ������ ���ֵ��� ���� 1������ ���ٸ�
	if (lst.size() > 1) {
		// ���ֵ��� ������ �����Ѵ�.
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
	// ���õ� ������ ���� DC�� ���� ������ Ư�� ��ġ�� ����Ѵ�.

	list<CObj*> lst = CUser::Get_Instance()->Get_SelectObjArr();

	// ������ ������ ������ 1���� Ŭ ���
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

			// ���� Small Wire ��ó�� �� �׸���
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
