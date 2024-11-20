#include "stdafx.h"
#include "SaveLoadMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "UnitMgr.h"

CSaveLoadMgr::CSaveLoadMgr()
{
}

CSaveLoadMgr::~CSaveLoadMgr()
{
}

void CSaveLoadMgr::Initialize(void)
{
}

int CSaveLoadMgr::Update(void)
{
	return 0;
}

void CSaveLoadMgr::Late_Update(void)
{
}

void CSaveLoadMgr::Render(HDC hDC)
{
}

void CSaveLoadMgr::Release(void)
{
}

void CSaveLoadMgr::Save(const TCHAR* strFilePath, SCENEID _eID)
{
	TCHAR pathTile[64], pathUnit[64];
	lstrcpy(pathTile, strFilePath);
	lstrcat(pathTile, L"/Tile.dat");

	lstrcpy(pathUnit, strFilePath);
	lstrcat(pathUnit, L"/Unit.dat");

	CTileMgr::Get_Instance()->Save_TileInfo(pathTile, _eID);
	CUnitMgr::Get_Instance()->Save_UnitInfo(pathUnit, _eID);


	//MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OK);
}

void CSaveLoadMgr::Load(const TCHAR* strFilePath, SCENEID _eID)
{
	TCHAR pathTile[64], pathUnit[64];
	lstrcpy(pathTile, strFilePath);
	lstrcat(pathTile, L"/Tile.dat");

	lstrcpy(pathUnit, strFilePath);
	lstrcat(pathUnit, L"/Unit.dat");

	CTileMgr::Get_Instance()->Load_TileInfo(pathTile, _eID);
	CUnitMgr::Get_Instance()->Load_UnitInfo(pathUnit, _eID);
	//MessageBox(g_hWnd, _T("Load 완료"), _T("Success"), MB_OK);
}
