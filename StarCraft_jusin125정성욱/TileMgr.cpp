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
	int	iCullEndX = iCullX + (WINCX / TILECX) + 2; // (+2�� �ϴ� ������ Ÿ�� ������ Ư���� �� 800, 600���� �������� �ʱ� ������ �� ��ĭ �� �����ְ� ����ؼ� �ڿ������� ���̱� ����)
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
	HANDLE	hFile = CreateFile(strFilePath,	// ������ ��� �� �̸� ���	
		GENERIC_WRITE,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		CREATE_ALWAYS,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{
		MessageBox(g_hWnd, _T("SaveFail"), _T("Fail"), MB_OK);
		// 1���� : �ڵ�, � ���μ����� �޼����� ��� ������ �����ϱ� ���� �ڵ�
		// 2���� : �޼����� ���� ����ϴ� ���ڿ�
		// 3���� : �˾� â�� �̸� ���ڿ�
		// 4���� : OK ��ư
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_vecTile[(int)_eID])
	{
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_TerrainInfo()), sizeof(TERRAIN), &dwByte, nullptr);
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}

	// ���� �Ҹ�
	CloseHandle(hFile);
}

void CTileMgr::Load_TileInfo(const TCHAR* strFilePath, SCENEID _eID)
{
	// �̹� Ÿ���� �����Ѵٸ� ���� �����ϱ�
	if (!m_vecTile[(int)_eID].empty()) {
		Release();
	}

	HANDLE	hFile = CreateFile(strFilePath,	// ������ ��� �� �̸� ���
		GENERIC_READ,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		OPEN_EXISTING,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{
		MessageBox(g_hWnd, _T("LoadFail"), _T("Fail"), MB_OK);
		// 1���� : �ڵ�, � ���μ����� �޼����� ��� ������ �����ϱ� ���� �ڵ�
		// 2���� : �޼����� ���� ����ϴ� ���ڿ�
		// 3���� : �˾� â�� �̸� ���ڿ�
		// 4���� : OK ��ư
		return;
	}

	DWORD		dwByte = 0;
	TERRAIN		eTerrain = TERRAIN::END;
	INFO		tInfo{};

	CObj* pObj = nullptr;

	// Ÿ�� ����
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

	// ���� �Ҹ�
	CloseHandle(hFile);
}
