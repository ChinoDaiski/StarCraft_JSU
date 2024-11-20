#pragma once

#include "Obj.h"
#include "Tile.h"
#include "UnitButton.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

typedef struct _tagAStar {

	// 시작점을 A, 도착점을 B라고 한다.
	//int		iG;		// 시작점(A)으로부터 현재 지점까지 경로를 따라 이동하는데 소요되는 비용
	//int		iH;		// 현재 사각형에서 목적지(B)까지의 예상 이동 비용
	//int		iF;		// 현재까지 이동하는데 걸린 비용과 예상 비용을 합친 총 비용 ( iG + iH )

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
	// 모든 유닛이 가지고 있는 공통적인 명령어
	void				Move(float _fX, float _fY);
	void				Move(const POINT& _tPos);
	void				Stop(void);
	void				Hold(void);
	void				Patrol(void);
	virtual void		Attack(CObj* _pObj) = 0;

public:
	// 피해를 입으면 불리는 함수
	void		Set_Damage(int _iDamage);

	// Hp가 0이하가 되면 불리는 함수, 죽었으니 오브젝트가 사라지고, 죽는 이펙트를 이펙트 매니저에서 부른다..
	void		Dead(void);

protected:
	// 움직이는 모션이 1개인 유닛
	void		DrawUnit(HDC hDC);

	// 움직이는 모션이 여러개인 유닛
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
	// 유닛의 이름을 인자로 받아 해당하는 유닛의 모든 정보를 설정하는 함수
	void Set_UnitInfo(UNIT_NAME _eUnitName);

	// 유닛의 이름을 인자로 받아 해당하는 유닛의 스테이터스 정보를 설정하는 함수
	void Set_UnitStatus(UNIT_NAME _eUnitName);

	// 데미지 정보로 그려지는 WireFrame의 정보를 바꾸는 함수
	// 데미지를 받는 함수와 연관되어 있다. 단, 이 함수는 말그대로 이미지의 정보만 세팅하는 함수
	// 데미지의 이미지를 크게 7가지로 나누어 관리한다.
	void	Set_WireFrameInfo(UNIT_NAME _eUnitName);

	// 유닛의 상태을 인자로 받아 해당하는 유닛 상태 정보를 설정하는 함수
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
	list<CTile*>		m_lstTile;			// 유닛이 움직이는 타일의 정보(A* 사용시 사용)

	int					m_iDir;				// 유닛이 움직이는 방향, 22.5도씩 16장을 사용, 총 360도를 점유한다.

	POINT				m_tDstPos;			// 유닛의 도착지점

	// 현재 유닛의 상태, 상태에 따라 유닛의 행동이 바뀐다. (FSM적용)
	UNIT_STATE			m_eUnitState;

	// 홀드 상태를 나타내는 변수
	bool				m_bHold;

	// 현재 움직이고 있는지 아닌지 나타내는 변수, 움직이고 있다면 true 아니라면 false값을 가진다.
	bool				m_bUnitMove;
};