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

	m_lFont.lfHeight = TEXT_SIZE;		// 글씨 세로 길이
	m_lFont.lfWidth = 0;				// 글씨 가로 길이지만, 0일경우 세로길이에 맞춰서 자동으로 변경
	m_lFont.lfEscapement = 0;
	m_lFont.lfOrientation = 0;
	m_lFont.lfWeight = 1000;			// 글씨 굵기
	m_lFont.lfItalic = 0;
	m_lFont.lfUnderline = 0;
	m_lFont.lfStrikeOut = 0;
	m_lFont.lfCharSet = HANGEUL_CHARSET;	// 한글형식 글꼴 사용
	m_lFont.lfOutPrecision = 0;
	m_lFont.lfClipPrecision = 0;
	m_lFont.lfQuality = 0;
	m_lFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(m_lFont.lfFaceName, TEXT("한컴 고딕"));
}

CUser::~CUser()
{
}

void CUser::Initialize(void)
{
}

int CUser::Update(void)
{
	// 마우스와 충돌 되는 물체가 있을 경우 해당 물체 선택
	if (!m_pArrDragedObj.empty()) {
		// 선택된 물체는 물체의 정보와 역할을 UI에 띄운다.
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
	// Editor에서 에디트 버튼을 선택했을 경우 해당 버튼에 frame 녹색으로 칠하는 것
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

	// 싱글 플레이에서 오브젝트를 선택했을 경우
	if (SCENEID::SINGLEPLAY == CSceneMgr::Get_Instance()->Get_SceneID()) {
		// 오브젝트를 1개 선택했을 경우 해당 오브젝트가 단일로 할 수 있는 일을 보여준다.
		if (m_pArrDragedObj.size() == 1) {
			// 오브젝트의 설명이 ui가운데 뜨고, 
			// 오브젝트의 가능 행동이 오른쪽 박스에 뜬다.
			m_pArrDragedObj.front()->DrawPortrait(_DC);
			m_pArrDragedObj.front()->DrawStatusInfo(_DC);
		}

		// 유닛을 여러개 선택했을 경우 공통적으로 할 수 있는 일을 보여준다.
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

	// 기존에 있던 배열 정보가 비어있지 않다면
	if (!m_pArrDragedObj.empty()) {
		// 모든 배열 내의 정보를 선택하지 않은 것으로 한다.
		for (auto& iter : m_pArrDragedObj)
			iter->Select_Unit_byUser(false);
	}
	// 기존 정보는 초기화
	m_pArrDragedObj.clear();

	// 새로운 정보를 받는다.
	m_pArrDragedObj = _pArrObj;

	// 만약 들어온 정보가 1개 밖에 없다면
	if (m_pArrDragedObj.size() == 1) {
		// 해당 오브젝트의 버튼 정보를 세팅한다.
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
	// 만약 들어온 정보가 2개 이상이라면
	else if (m_pArrDragedObj.size() > 1) {
		// 여러 정보를 출력하는 창을 출력한다.
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
