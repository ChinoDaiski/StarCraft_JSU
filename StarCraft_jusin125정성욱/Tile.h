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
	// Ÿ���� ������ ������ �ִ�. 


	bool			m_bEnable;			// �̵��� ������ Ÿ������ �ƴ����� ���� ����, true�� �̵�����, false�� �̵� �Ұ���
	bool			m_bShowEnable;		// �̵��� ������ Ÿ������ �ƴ����� ���� ������ ���,
										// true�� ���, false�� ������� ����.

	TERRAIN			m_eTerrainInfo;		// Ÿ���� ����, ��µǴ� �̹����� �޶�����.

	HDC				m_bitmapDC;			// Ÿ��(Terrain)�� DC
};