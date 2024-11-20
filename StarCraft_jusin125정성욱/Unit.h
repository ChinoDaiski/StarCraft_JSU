#pragma once

#include "Obj.h"
#include "Tile.h"
#include "UnitButton.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

typedef struct _tagAStar {

	// �������� A, �������� B��� �Ѵ�.
	//int		iG;		// ������(A)���κ��� ���� �������� ��θ� ���� �̵��ϴµ� �ҿ�Ǵ� ���
	//int		iH;		// ���� �簢������ ������(B)������ ���� �̵� ���
	//int		iF;		// ������� �̵��ϴµ� �ɸ� ���� ���� ����� ��ģ �� ��� ( iG + iH )

}AStar, *PAStar;


enum class UNIT_STATE { Move, Stop, Hold, Attack, beAttacked, Mining, Build, IDLE, END };


class CUnit : public CObj {
public:
	CUnit();
	virtual ~CUnit();

public:
	virtual void		Initialize(void) = 0;
	virtual int			Update(void) = 0;
	virtual int			Late_Update(void) = 0;
	virtual void		Render(HDC hDC) = 0;
	virtual void		Release(void) = 0;

public:
	// ��� ������ ������ �ִ� �������� ��ɾ�
	void				Move(float _fX, float _fY);
	void				Move(const POINT& _tPos);
	void				Stop(void);
	void				Hold(void);
	void				Patrol(void);
	virtual void		Attack(CObj* _pObj) = 0;

public:
	// ���ظ� ������ �Ҹ��� �Լ�
	void		Set_Damage(int _iDamage);

	// Hp�� 0���ϰ� �Ǹ� �Ҹ��� �Լ�, �׾����� ������Ʈ�� �������, �״� ����Ʈ�� ����Ʈ �Ŵ������� �θ���..
	void		Dead(void);

protected:
	// �����̴� ����� 1���� ����
	void		DrawUnit(HDC hDC);

	// �����̴� ����� �������� ����
	void		DrawMultiMoveUnit(HDC hDC);

protected:
	void	Update_Frame(FRAME& _tFrame);

public:
	void	Set_UnitInfo(const UNITInfo& _tUnitInfo) {
		m_tUnitInfo = _tUnitInfo;
	}
	void	Set_UnitInfo(UNIT_NAME _eUnitName, int _iAttack, int _iArmor, int _iRange, int _iOffense, int _iHp, int _iPopulation,
		UNIT_TYPE _eType, UNIT_ATTACK_TYPE _eAttType, const TCHAR* _MoveFrameKey, TCHAR* _AttackFrameKey, int _iShield);

	const UNITInfo&	Get_UnitInfo(void) const {
		return m_tUnitInfo;
	}

public:
	// ������ �̸��� ���ڷ� �޾� �ش��ϴ� ������ ��� ������ �����ϴ� �Լ�
	void Set_UnitInfo(UNIT_NAME _eUnitName);

	// ������ �̸��� ���ڷ� �޾� �ش��ϴ� ������ �������ͽ� ������ �����ϴ� �Լ�
	void Set_UnitStatus(UNIT_NAME _eUnitName);

	// ������ ������ �׷����� WireFrame�� ������ �ٲٴ� �Լ�
	// �������� �޴� �Լ��� �����Ǿ� �ִ�. ��, �� �Լ��� ���״�� �̹����� ������ �����ϴ� �Լ�
	// �������� �̹����� ũ�� 7������ ������ �����Ѵ�.
	void	Set_WireFrameInfo(UNIT_NAME _eUnitName);

	// ������ ������ ���ڷ� �޾� �ش��ϴ� ���� ���� ������ �����ϴ� �Լ�
	void Set_UnitState(UNIT_STATE _eUnitState);

public:
	virtual void Update_State(void) = 0;

public:
	void Set_DstPos(const POINT& _pt);
	void Set_DstPos(float _x, float _y);

public:
	WireFrameInfo		Get_WireFrameInfo(void) const { return m_tWireFrameInfo; }

public:
	void Set_Hold(bool _bHold) { m_bHold = _bHold; }

public:
	bool Get_UnitMove(void) const { return m_bUnitMove; }

protected:	
	list<CTile*>		m_lstTile;			// ������ �����̴� Ÿ���� ����(A* ���� ���)

	int					m_iDir;				// ������ �����̴� ����, 22.5���� 16���� ���, �� 360���� �����Ѵ�.

	POINT				m_tDstPos;			// ������ ��������

	// ���� ������ ����, ���¿� ���� ������ �ൿ�� �ٲ��. (FSM����)
	UNIT_STATE			m_eUnitState;

	// Ȧ�� ���¸� ��Ÿ���� ����
	bool				m_bHold;

	// ���� �����̰� �ִ��� �ƴ��� ��Ÿ���� ����, �����̰� �ִٸ� true �ƴ϶�� false���� ������.
	bool				m_bUnitMove;
};