#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "AbstractFactory.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "EditorUI.h"
#include "User.h"

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY ||
		CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR) {

		for (int i = 0; i < MAPCX / TILECX; ++i)
		{
			for (int j = 0; j < MAPCX / TILECY; ++j)
			{
				float fX = float((TILECX * j) + (TILECX >> 1));
				float fY = float((TILECY * i) + (TILECY >> 1));

				m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].push_back(CAbstractFactory<CTile>::Create(fX, fY));
			}
		}
	}

	m_eSelectTerrain = TERRAIN::DIRT;
	m_bShowEnable = false;
}

int CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()])
		iter->Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON)) {

		RECT rt = CEditorUI::Get_Instance()->Get_Rect();
		POINT pt = CMouse::Get_Instance()->Get_Pos();
		if (pt.y < rt.top - 20) {
			Picking_Tile(pt);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('1')) {
		for (auto& iter : m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()])
			dynamic_cast<CTile*>(iter)->Set_showEnable();

		//m_bShowEnable = !m_bShowEnable;
	}

	return OBJ_NOEVENT;
}

void CTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()])
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	//	200 / 64 = 3
	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	//	3 + 12.
	int	iCullEndX = iCullX + (WINCX / TILECX) + 2; // (+2를 하는 이유는 타일 사이즈 특성상 딱 800, 600으로 떨어지지 않기 때문에 한 두칸 더 여유있게 출력해서 자연스럽게 보이기 위함)
	int	iCullEndY = iCullY + (WINCY / TILECY) + 2;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int	iIndex = i * (MAPCX / TILECX) + j;

			if (0 > iIndex || m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].size() <= (size_t)iIndex)
				continue;

			CObj* pObj = m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].at(iIndex);
			pObj->Render(hDC);
		}
	}
}

void CTileMgr::Release(void)
{
	for_each(
		m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].begin(),
		m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].end(),
		Safe_Delete<CObj*>);
	m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].clear();
}

CObj* CTileMgr::Picking_Tile_Terrain(const POINT & pt, TERRAIN _eTerrain)
{
	int		iX = (pt.x + CScrollMgr::Get_Instance()->Get_ScrollX()) / TILECX;
	int		iY = (pt.y + CScrollMgr::Get_Instance()->Get_ScrollY()) / TILECY;

	int		iIndex = iY * (MAPCX / TILECX) + iX;

	if (0 > iIndex || m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].size() <= (size_t)iIndex)
		return nullptr;

	dynamic_cast<CTile*>(m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex])->Set_TerrainInfo(_eTerrain);

	return m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex];
}

CObj* CTileMgr::Picking_Tile_Enable(const POINT& pt, bool _bEnable)
{
	int		iX = (pt.x + CScrollMgr::Get_Instance()->Get_ScrollX()) / TILECX;
	int		iY = (pt.y + CScrollMgr::Get_Instance()->Get_ScrollY()) / TILECY;

	int		iIndex = iY * (MAPCX / TILECX) + iX;

	if (0 > iIndex || m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].size() <= (size_t)iIndex)
		return nullptr;

	dynamic_cast<CTile*>(m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex])->Set_Enable(_bEnable);

	return m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex];
}

void CTileMgr::Picking_Tile(const POINT & pt)
{
	int		iX = (pt.x + CScrollMgr::Get_Instance()->Get_ScrollX()) / TILECX;
	int		iY = (pt.y + CScrollMgr::Get_Instance()->Get_ScrollY()) / TILECY;

	int		iIndex = iY * (MAPCX / TILECX) + iX;

	if (0 > iIndex || m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].size() <= (size_t)iIndex)
		return;

	ButtonInfo tBInfo = CUser::Get_Instance()->Get_BInfo();
	
	switch (tBInfo.Terrain)
	{
	case TERRAIN::DIRT:
		dynamic_cast<CTile*>(m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex])->Set_TerrainInfo(TERRAIN::DIRT);
		break;
	case TERRAIN::WATER:
		dynamic_cast<CTile*>(m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex])->Set_TerrainInfo(TERRAIN::WATER);
		break;
	case TERRAIN::CREEP:
		dynamic_cast<CTile*>(m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex])->Set_TerrainInfo(TERRAIN::CREEP);
		break;
	case TERRAIN::END:
		break;
	}
}

CObj* CTileMgr::Find_Tile(const POINT& pt)
{
	int		iX = (pt.x + CScrollMgr::Get_Instance()->Get_ScrollX()) / TILECX;
	int		iY = (pt.y + CScrollMgr::Get_Instance()->Get_ScrollY()) / TILECY;

	int		iIndex = iY * (MAPCX / TILECX) + iX;

	if (0 > iIndex || m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].size() <= (size_t)iIndex)
		return nullptr;

	return m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex];
}

CObj* CTileMgr::Find_Tile_Dir(const POINT &pt, DIR _eDir)
{
	int		iX = (pt.x + CScrollMgr::Get_Instance()->Get_ScrollX()) / TILECX;
	int		iY = (pt.y + CScrollMgr::Get_Instance()->Get_ScrollY()) / TILECY;

	int		iIndex = iY * (MAPCX / TILECX) + iX;

	switch (_eDir)
	{
	case DIR::RIGHT:
		++iIndex;
		break;
	case DIR::TOP_RIGHT:
		iIndex -= iY;
		++iIndex;
		break;
	case DIR::TOP:
		iIndex -= iY;
		break;
	case DIR::TOP_LEFT:
		iIndex -= iY;
		--iIndex;
		break;
	case DIR::LEFT:
		--iIndex;
		break;
	case DIR::BOTTOM_LEFT:
		iIndex += iY;
		--iIndex;
		break;
	case DIR::BOTTOM:
		iIndex += iY;
		break;
	case DIR::BOTTOM_RIGHT:
		iIndex += iY;
		++iIndex;
		break;
	case DIR::END:
		break;
	default:
		break;
	}

	if (0 > iIndex || m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()].size() <= (size_t)iIndex)
		return nullptr;

	return m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()][iIndex];
}

void CTileMgr::Save_TileInfo(const TCHAR* strFilePath, SCENEID _eID)
{
	HANDLE	hFile = CreateFile(strFilePath,	// 파일의 경로 및 이름 명시	
		GENERIC_WRITE,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		CREATE_ALWAYS,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		MessageBox(g_hWnd, _T("SaveFail"), _T("Fail"), MB_OK);
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_vecTile[(int)_eID])
	{
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_TerrainInfo()), sizeof(TERRAIN), &dwByte, nullptr);
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}

	// 파일 소멸
	CloseHandle(hFile);
}

void CTileMgr::Load_TileInfo(const TCHAR* strFilePath, SCENEID _eID)
{
	// 이미 타일이 존재한다면 전부 삭제하기
	if (!m_vecTile[(int)_eID].empty()) {
		Release();
	}

	HANDLE	hFile = CreateFile(strFilePath,	// 파일의 경로 및 이름 명시
		GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		MessageBox(g_hWnd, _T("LoadFail"), _T("Fail"), MB_OK);
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;
	TERRAIN		eTerrain = TERRAIN::END;
	INFO		tInfo{};

	CObj* pObj = nullptr;

	// 타일 저장
	while (true)
	{
		ReadFile(hFile, &eTerrain, sizeof(TERRAIN), &dwByte, nullptr);
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		pObj = new CTile(eTerrain);
		pObj->Set_Info(tInfo);
		pObj->Initialize();

		m_vecTile[(int)_eID].push_back(pObj);
	}

	// 파일 소멸
	CloseHandle(hFile);
}
