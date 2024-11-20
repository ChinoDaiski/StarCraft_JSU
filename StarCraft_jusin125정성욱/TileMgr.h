#pragma once

#include "Singleton.h"
#include "Obj.h"
#include "SceneMgr.h"

class CTileMgr : public CSingleton<CTileMgr> {
public:
	CTileMgr();
	~CTileMgr();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	CObj* Picking_Tile_Terrain(const POINT& pt, TERRAIN _eTerrain);
	CObj* Picking_Tile_Enable(const POINT& pt, bool _bEnable);

	void	Picking_Tile(const POINT& pt);
	CObj*	Find_Tile(const POINT& pt);
	CObj*	Find_Tile_Dir(const POINT& pt, DIR _eDir);	// 좌표의 타일 바로 근처 방향에 있는 타일의 정보를 return하는 함수

public:
	void Set_showEnable(void) {
		m_bShowEnable = !m_bShowEnable;
	}
	vector<CObj*>	Get_vecTile(void) const { return m_vecTile[(int)CSceneMgr::Get_Instance()->Get_SceneID()]; }
	void			Set_vecTile(vector<CObj*>& _vecTile, SCENEID _eID) { m_vecTile[(int)_eID] = _vecTile; }

public:
	void Save_TileInfo(const TCHAR* strFilePath, SCENEID _eID);
	void Load_TileInfo(const TCHAR* strFilePath, SCENEID _eID);

private:
	vector<CObj*>			m_vecTile[(int)SCENEID::END];
	TERRAIN					m_eSelectTerrain;

	bool					m_bShowEnable;

	CObj*					m_pickingTile;
};	

