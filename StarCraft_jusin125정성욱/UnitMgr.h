#pragma once

#include "Singleton.h"
#include "Enum.h"

class CUnitMgr : public CSingleton<CUnitMgr> {
public:
	CUnitMgr();
	~CUnitMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// ���� �ҷ����⸦ Ư�� ������ ó��
	void Save_UnitInfo(const TCHAR* strFilePath, SCENEID _eID);
	void Load_UnitInfo(const TCHAR* strFilePath, SCENEID _eID);

public:
	void	Create_Unit(UNIT_NAME _eUnit, float _fX, float _fY, SCENEID _eSceneID);
	void	Create_EnemyUnit(UNIT_NAME _eUnit, float _fX, float _fY, SCENEID _eSceneID);


private:
	// �ε�ġ�� ������ ������ �ٲٴ� �簢�� 
	RECT	m_tRectMove[4];
};

