#pragma once

#include "Obj.h"
#include "BitmapMgr.h"

class CTile : public CObj {
public:
	CTile(TERRAIN _eTerrainInfo = TERRAIN::END);
	virtual ~CTile();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Enable(bool _bEnable) { m_bEnable = _bEnable; }
	void		Set_showEnable() { m_bShowEnable = !m_bShowEnable; }
	void		Set_TerrainInfo(TERRAIN _eTerrainInfo);
	const TERRAIN&	Get_TerrainInfo(void) const {
		return m_eTerrainInfo;
	};

	bool		Get_showEnable() { return m_bShowEnable; }

private:
	// 타일의 정보를 가지고 있다. 


	bool			m_bEnable;			// 이동이 가능한 타일인지 아닌지에 대한 정보, true면 이동가능, false면 이동 불가능
	bool			m_bShowEnable;		// 이동이 가능한 타일인지 아닌지에 대한 정보를 출력,
										// true면 출력, false면 출력하지 않음.

	TERRAIN			m_eTerrainInfo;		// 타일의 정보, 출력되는 이미지가 달라진다.

	HDC				m_bitmapDC;			// 타일(Terrain)의 DC
};