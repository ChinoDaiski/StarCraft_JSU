#include "stdafx.h"
#include "EditorUI.h"
#include "BitmapMgr.h"
#include "MyButton.h"
#include "EditorButton.h"
#include "AbstractFactory.h"
#include "User.h"
#include "Mouse.h"

CEditorUI::CEditorUI()
{
}


CEditorUI::~CEditorUI()
{
}

void CEditorUI::Initialize(void)
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = (WINCY >> 2) + 20;

	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY - (WINCY >> 3) - 10;

	Update_Rect();

	m_bitmapDC = CBitmapMgr::Get_Instance()->Find_Image(L"Editor_UI");

	// 타일 버튼
	//===========================================================================================
	int iGap = BUTTON_SIZE + 3;
	int iLeft = m_tRect.left + 190;
	int iTop = m_tRect.top + 40;
	CObj* pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft, iTop, L"Editor_Tile_Dirt");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(60, 58);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(TERRAIN::DIRT);
	pObj->Initialize();

	m_vecButton[(int)KIND::Tile].push_back(pObj);

	CUser::Get_Instance()->Set_BInfo(dynamic_cast<CEditorButton*>(pObj)->Get_BInfo());

	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap, iTop, L"Editor_Tile_Water");
	pObj->Initialize();
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(60, 58);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(TERRAIN::WATER);
	m_vecButton[(int)KIND::Tile].push_back(pObj);

	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 2, iTop, L"Editor_Tile_Creep");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(60, 58);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(TERRAIN::CREEP);
	pObj->Initialize();
	m_vecButton[(int)KIND::Tile].push_back(pObj);
	//===========================================================================================

	// 유닛 버튼
	//===========================================================================================
	// 프로브 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 4, iTop, L"Editor_Unit_Probe");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Probe);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 아비터 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 5, iTop, L"Editor_Unit_Arbiter");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Arbiter);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 스카웃 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 6, iTop, L"Editor_Unit_Scout");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Scout);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 캐리어 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 7, iTop, L"Editor_Unit_Carrier");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Carrier);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 커세어 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 8, iTop, L"Editor_Unit_Corsair");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Corsair);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 커세어 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 9, iTop, L"Editor_Unit_Zealot");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Zealot);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 드라군 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 10, iTop, L"Editor_Unit_Dragon");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Dragon);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 하이템플러 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 11, iTop, L"Editor_Unit_HighTemplar");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::High_Templar);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);


	// 다크템플러 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 12, iTop, L"Editor_Unit_DarkTemplar");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Dark_Templar);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 리버 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 13, iTop, L"Editor_Unit_Reaver");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Reaver);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 아콘 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 14, iTop, L"Editor_Unit_Archon");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Archon);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 다크 아콘 버튼
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 15, iTop, L"Editor_Unit_DarkArchon");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(UNIT_NAME::Dark_Archon);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	// 건물 버튼
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 4, iTop + iGap * 2 + 5, L"Editor_Build_Nexus");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Nexus);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 5, iTop + iGap * 2 + 5, L"Editor_Build_Robotics_Facility");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Robotics_Facility);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 6, iTop + iGap * 2 + 5, L"Editor_Build_Pylon");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Pylon);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 7, iTop + iGap * 2 + 5, L"Editor_Build_Assimilator");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Assimilator);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 8, iTop + iGap * 2 + 5, L"Editor_Build_Observatory");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Observatory);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 9, iTop + iGap * 2 + 5, L"Editor_Build_Gateway");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Gateway);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 10, iTop + iGap * 2 + 5, L"Editor_Build_Photon_Cannon");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Photon_Cannon);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 11, iTop + iGap * 2 + 5, L"Editor_Build_Citadel_of_Adun");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Citadel_of_Adun);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 12, iTop + iGap * 2 + 5, L"Editor_Build_Cybernetics_Core");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Cybernetics_Core);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 13, iTop + iGap * 2 + 5, L"Editor_Build_Tempar_Archives");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Tempar_Archives);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 14, iTop + iGap * 2 + 5, L"Editor_Build_Forge");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Forge);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 15, iTop + iGap * 2 + 5, L"Editor_Build_Stargate");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Stargate);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 16, iTop + iGap * 2 + 5, L"Editor_Build_Fleet_Beacon");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Fleet_Beacon);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 17, iTop + iGap * 2 + 5, L"Editor_Build_Arbiter_Tribunal");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Arbiter_Tribunal);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 18, iTop + iGap * 2 + 5, L"Editor_Build_Robotics_Support_Bay");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Robotics_Support_Bay);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================

	// 넥서스
	//===========================================================================================
	pObj = CAbstractFactory<CEditorButton>::
		Create(iLeft + iGap * 19, iTop + iGap * 2 + 5, L"Editor_Build_Shield_Battery");
	dynamic_cast<CEditorButton*>(pObj)->Set_Size(33, 34);
	dynamic_cast<CEditorButton*>(pObj)->Set_Tile(BUILD::Shield_Battery);
	pObj->Initialize();
	m_vecButton[(int)KIND::Protoss].push_back(pObj);
	//===========================================================================================


	CMouse::Get_Instance()->Set_LbuttonDown();
}

int CEditorUI::Update(void)
{
	for (int i = 0; i < (int)KIND::End; ++i) {
		for (auto& button : m_vecButton[i]) {
			button->Update();
		}
	}

	return 0;
}

void CEditorUI::Late_Update(void)
{
	for (int i = 0; i < (int)KIND::End; ++i) {
		for (auto& button : m_vecButton[i]) {
			button->Late_Update();
		}
	}
}

void CEditorUI::Render(HDC hDC)
{
	BitBlt(
		hDC, m_tRect.left, m_tRect.top,
		m_tInfo.fCX, m_tInfo.fCY,
		m_bitmapDC,
		0, 0,
		SRCCOPY);

	LPCWSTR str = L"Terrain";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, m_tRect.left + 180, m_tRect.top + 10, str, lstrlen(str));

	str = L"Protoss";
	TextOut(hDC, m_tRect.left + 290, m_tRect.top + 10, str, lstrlen(str));

	str = L"Build";
	TextOut(hDC, m_tRect.left + 290, m_tRect.top + 70, str, lstrlen(str));

	for (int i = 0; i < (int)KIND::End; ++i) {
		for (auto& button : m_vecButton[i]) {
			Rectangle(hDC, button->Get_Rect().left, button->Get_Rect().top, button->Get_Rect().right, button->Get_Rect().bottom);
			button->Render(hDC);
		}
	}

	CUser::Get_Instance()->Render(hDC);
}

void CEditorUI::Release(void)
{
}

void CEditorUI::Update_Rect(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}