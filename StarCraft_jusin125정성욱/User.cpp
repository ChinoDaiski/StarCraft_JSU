#include "stdafx.h"
#include "User.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Unit.h"
#include "UIButtonMgr.h"
#include "Build.h"

#define TEXT_SIZE 12

CUser::CUser()
	:m_fSpeed(10.f)
{
	ZeroMemory(&m_tBInfo, sizeof(ButtonInfo));

	m_lFont.lfHeight = TEXT_SIZE;		// �۾� ���� ����
	m_lFont.lfWidth = 0;				// �۾� ���� ��������, 0�ϰ�� ���α��̿� ���缭 �ڵ����� ����
	m_lFont.lfEscapement = 0;
	m_lFont.lfOrientation = 0;
	m_lFont.lfWeight = 1000;			// �۾� ����
	m_lFont.lfItalic = 0;
	m_lFont.lfUnderline = 0;
	m_lFont.lfStrikeOut = 0;
	m_lFont.lfCharSet = HANGEUL_CHARSET;	// �ѱ����� �۲� ���
	m_lFont.lfOutPrecision = 0;
	m_lFont.lfClipPrecision = 0;
	m_lFont.lfQuality = 0;
	m_lFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(m_lFont.lfFaceName, TEXT("���� ���"));
}

CUser::~CUser()
{
}

void CUser::Initialize(void)
{
}

int CUser::Update(void)
{
	// ���콺�� �浹 �Ǵ� ��ü�� ���� ��� �ش� ��ü ����
	if (!m_pArrDragedObj.empty()) {
		// ���õ� ��ü�� ��ü�� ������ ������ UI�� ����.
		for (auto& iter : m_pArrDragedObj) {
			iter->Select_Unit_byUser(true);
		}
	}

	return 0;
}

void CUser::Late_Update(void)
{
}

void CUser::Render(HDC _DC)
{
	// Editor���� ����Ʈ ��ư�� �������� ��� �ش� ��ư�� frame ������� ĥ�ϴ� ��
	if (SCENEID::EDITOR == CSceneMgr::Get_Instance()->Get_SceneID()) {
		MyPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		OldPen = (HPEN)SelectObject(_DC, MyPen);

		MoveToEx(_DC, m_tBInfo.rt.left, m_tBInfo.rt.top, nullptr);
		LineTo(_DC, m_tBInfo.rt.left, m_tBInfo.rt.bottom);
		LineTo(_DC, m_tBInfo.rt.right, m_tBInfo.rt.bottom);
		LineTo(_DC, m_tBInfo.rt.right, m_tBInfo.rt.top);
		LineTo(_DC, m_tBInfo.rt.left, m_tBInfo.rt.top);

		SelectObject(_DC, OldPen);
		DeleteObject(MyPen);
	}

	// �̱� �÷��̿��� ������Ʈ�� �������� ���
	if (SCENEID::SINGLEPLAY == CSceneMgr::Get_Instance()->Get_SceneID()) {
		// ������Ʈ�� 1�� �������� ��� �ش� ������Ʈ�� ���Ϸ� �� �� �ִ� ���� �����ش�.
		if (m_pArrDragedObj.size() == 1) {
			// ������Ʈ�� ������ ui��� �߰�, 
			// ������Ʈ�� ���� �ൿ�� ������ �ڽ��� ���.
			m_pArrDragedObj.front()->DrawPortrait(_DC);
			m_pArrDragedObj.front()->DrawStatusInfo(_DC);
		}

		// ������ ������ �������� ��� ���������� �� �� �ִ� ���� �����ش�.
		else {

		}
	}
}

void CUser::Release(void)
{
}


void CUser::Set_SelectObj(list<CObj*> _pArrObj)
{
	CUIButtonMgr::Get_Instance()->Clear_ButtonInfo();

	// ������ �ִ� �迭 ������ ������� �ʴٸ�
	if (!m_pArrDragedObj.empty()) {
		// ��� �迭 ���� ������ �������� ���� ������ �Ѵ�.
		for (auto& iter : m_pArrDragedObj)
			iter->Select_Unit_byUser(false);
	}
	// ���� ������ �ʱ�ȭ
	m_pArrDragedObj.clear();

	// ���ο� ������ �޴´�.
	m_pArrDragedObj = _pArrObj;

	// ���� ���� ������ 1�� �ۿ� ���ٸ�
	if (m_pArrDragedObj.size() == 1) {
		// �ش� ������Ʈ�� ��ư ������ �����Ѵ�.
		switch (m_pArrDragedObj.front()->Get_Type())
		{
		case OBJ_TYPE::BUILD:
			CUIButtonMgr::Get_Instance()->ClickObject(dynamic_cast<CBuild*>(m_pArrDragedObj.front())->Get_BuildInfo().m_eBuild);
			break;

		case OBJ_TYPE::UNIT:
			
			CUIButtonMgr::Get_Instance()->ClickObject(dynamic_cast<CUnit*>(m_pArrDragedObj.front())->Get_UnitInfo().eUnitName);
			break;

		case OBJ_TYPE::END:
			break;
		}
	}
	// ���� ���� ������ 2�� �̻��̶��
	else if (m_pArrDragedObj.size() > 1) {
		// ���� ������ ����ϴ� â�� ����Ѵ�.
		;
	}
}

void CUser::PrintText(HDC hDC, int _iX, int _iY, TCHAR* _strText)
{
	PAINTSTRUCT ps;
	HFONT hFont, saveFont;

	hFont = CreateFontIndirect(&m_lFont);
	saveFont = (HFONT)SelectObject(hDC, hFont);

	TextOut(hDC, _iX, _iY, _strText, lstrlen(_strText));

	DeleteObject(SelectObject(hDC, saveFont));
}

void CUser::PrintText(HDC hDC, int _iX, int _iY, TCHAR* _strText, int _iSize)
{
	PAINTSTRUCT ps;
	HFONT hFont, saveFont;

	m_lFont.lfHeight = _iSize;
	hFont = CreateFontIndirect(&m_lFont);
	saveFont = (HFONT)SelectObject(hDC, hFont);

	TextOut(hDC, _iX, _iY, _strText, lstrlen(_strText));

	m_lFont.lfHeight = TEXT_SIZE;

	DeleteObject(SelectObject(hDC, saveFont));
}
