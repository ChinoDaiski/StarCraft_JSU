#include "stdafx.h"
#include "Unit.h"
#include "FindPath.h"
#include "TileMgr.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "User.h"
#include "EffectMgr.h"

CUnit::CUnit()
	: m_iDir(8)
{
	m_eRelation = RELATION::END;
	m_eType = OBJ_TYPE::UNIT;


	m_tBuildInfo.m_eBuild = BUILD::END;
}

CUnit::~CUnit()
{
}

void CUnit::Move(float _fX, float _fY)
{
	m_bUnitMove = true;

	// 현재 물체의 사각형 판정범위와 목표로하는 지점이 충돌하지 않을 경우
	// 목표로 이동한다.

	// 직선 이동법
	POINT	pt;
	pt.x = _fX;
	pt.y = _fY;
	if (!PtInRect(&m_tRect, pt)) {
		// 현재 위치와 목표의 위치간의 관계에서 각도를 추출한다.
		// 각도에 맞는 프레임을 찾아 랜더링
		// 이동은 해당 방향으로 speed값 만큼 이동

		float	fWidth = _fX - m_tInfo.fX;
		float	fHeight = _fY - m_tInfo.fY;

		float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acosf(fWidth / fDistance);

		m_fAngle = fRadian * (180.f / PI);

		if (_fY > m_tInfo.fY) {
			m_fAngle *= -1.f;
			m_fAngle += 360.f;
		}
		
		// m_fAngle을 0 ~ 360 로 맞춘다.
		while (!(0.f <= m_fAngle && m_fAngle <= 360.f))
		{
			if (0.f > m_fAngle)
				m_fAngle += 360.f;
			else if (360.f < m_fAngle)
				m_fAngle -= 360.f;
		}

		// 각도로 부터 유닛이 움직이는 방향을 구한다.
		// 총 16움직임. 22.5도씩 점유하고 있는 이미지를 사용.

		// 각도에 따른 이동 모션을 바꾼다.
		m_iDir = (int)(m_fAngle / 22.5);

		// 현재 이동 위치가 목표지점과 다르다면 이동한다.
		if ((m_tDstPos.x != m_tInfo.fX) && (m_tDstPos.y != m_tInfo.fY)) {
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
		}

		if (!(m_tUnitInfo.eUnitName == UNIT_NAME::Probe ||
			m_tUnitInfo.eUnitName == UNIT_NAME::Zealot ||
			m_tUnitInfo.eUnitName == UNIT_NAME::Dark_Templar ||
			m_tUnitInfo.eUnitName == UNIT_NAME::Carrier)) {
			if (nullptr != m_pTarget) {
				if (m_tUnitInfo.iRange < Get_Distance(m_pTarget)) {
					// 목적지를 현재 위치로 한다.
					m_tDstPos.x = m_tInfo.fX;
					m_tDstPos.y = m_tInfo.fY;
					m_eUnitState = UNIT_STATE::Attack;
				}
			}
		}
	}
	else {
		m_eUnitState = UNIT_STATE::Stop;
	}




	/*POINT	ptCurr, ptEnd;
	ptCurr.x = (LONG)m_tInfo.fX;
	ptCurr.y = (LONG)m_tInfo.fY;
	ptEnd.x = (LONG)_fX;
	ptEnd.y = (LONG)_fY;

	CFindPath FindPath;
	CTile* start = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Find_Tile(ptCurr));
	CTile* end = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Find_Tile(ptEnd));
	m_lstTile = FindPath.GetPath(start, end);*/
}

void CUnit::Move(const POINT& _tPos)
{
	Move(_tPos.x, _tPos.y);
}

void CUnit::Stop(void)
{
	Set_DstPos(m_tInfo.fX, m_tInfo.fY);
}

void CUnit::Hold(void)
{
}

void CUnit::Patrol(void)
{
}

void CUnit::Set_Damage(int _iDamage)
{
	// 데미지를 받은 상황이라고 상태를 바꿈.
	m_eUnitState = UNIT_STATE::beAttacked;

	if (m_tUnitInfo.m_iShield > 0) {
		m_tUnitInfo.m_iShield -= _iDamage;

		if (m_tUnitInfo.m_iShield < 0)
			m_tUnitInfo.m_iShield = 0;
	}
	else if (m_tUnitInfo.iHP > 0) {
		m_tUnitInfo.iHP -= _iDamage;
		if (m_tUnitInfo.iHP < 0) {
			m_tUnitInfo.iHP = 0;
		}
	}
	
	if (m_tUnitInfo.m_iShield == 0 && m_tUnitInfo.iHP == 0)
		m_bDead = true;
}

void CUnit::Dead(void)
{
	m_bDead = true;

	CEffectMgr::Get_Instance();
}

void CUnit::DrawUnit(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_tUnitInfo.m_MoveDC,
		0, m_tUnitInfo.tMoveFrame.iHeight * m_iDir,
		m_tUnitInfo.tMoveFrame.iWidth,
		m_tUnitInfo.tMoveFrame.iHeight,
		RGB(255, 255, 255));
}

void CUnit::DrawMultiMoveUnit(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		m_tUnitInfo.m_MoveDC,

		m_tUnitInfo.tMoveFrame.iWidth * m_tUnitInfo.tMoveFrame.iFrameCurr,
		m_tUnitInfo.tMoveFrame.iHeight * m_iDir,

		m_tUnitInfo.tMoveFrame.iWidth,
		m_tUnitInfo.tMoveFrame.iHeight,
		RGB(255, 255, 255));
}

void CUnit::Update_Frame(FRAME & _tFrame)
{
	if (_tFrame.dwFrameTime + _tFrame.dwFrameSpeed < GetTickCount())
	{
		++_tFrame.iFrameCurr;
		_tFrame.dwFrameTime = GetTickCount();

		if (_tFrame.iFrameCurr >= _tFrame.iFrameEnd)
			_tFrame.iFrameCurr = _tFrame.iFrameStart;
	}
}

void CUnit::Set_UnitInfo(
	UNIT_NAME _eUnitName,
	int _iAttack, int _iArmor,
	int _iRange, int _iOffense,
	int _iHp,
	int _iPopulation,
	UNIT_TYPE _eType, UNIT_ATTACK_TYPE _eAttType,
	const TCHAR * _MoveFrameKey, TCHAR * _AttackFrameKey,
	int _iShield) {

	m_tUnitInfo.eUnitName = _eUnitName;

	m_tUnitInfo.iAttack = _iAttack;
	m_tUnitInfo.iArmor = _iArmor;

	m_tUnitInfo.iRange = _iRange;
	m_tUnitInfo.dwOffense = _iOffense;

	m_tUnitInfo.iMaxHP = _iHp;
	m_tUnitInfo.iHP = _iHp;

	m_tUnitInfo.m_iShield = _iShield;

	m_tUnitInfo.iPopulation = _iPopulation;

	m_tUnitInfo.eType = _eType;
	m_tUnitInfo.eAttType = _eAttType;

	lstrcpy(m_tUnitInfo.m_MoveFrameKey, _MoveFrameKey);
	lstrcpy(m_tUnitInfo.m_AttackFrameKey, _AttackFrameKey);

	m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(_MoveFrameKey);
	m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(_AttackFrameKey);
}

void CUnit::Set_DstPos(const POINT& _pt)
{
	Set_DstPos(_pt.x, _pt.y);
}

void CUnit::Set_DstPos(float _x, float _y)
{
	m_tDstPos.x = _x;
	m_tDstPos.y = _y;
}

void CUnit::Set_UnitInfo(UNIT_NAME _eUnitName)
{
	// 유닛의 이름
	m_tUnitInfo.eUnitName = _eUnitName;

	// 유닛의 초상화 설정
	Set_Portrait(_eUnitName);

	// 유닛의 와이어 프레임 설정
	Set_WireFrameInfo(_eUnitName);

	// 유닛의 스탯창 정보 설정
	Set_UnitStatus(_eUnitName);

	m_tBuildInfo.m_eBuild == BUILD::END;

	switch (_eUnitName)
	{
	case UNIT_NAME::Probe:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Probe_Move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 이미지의 가로/세로 길이
		m_tUnitInfo.tMoveFrame.iWidth = 32;
		m_tUnitInfo.tMoveFrame.iHeight = 32;

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 30;
		m_tInfo.fCY = 30;

		// 유닛의 이동 스피드
		m_fSpeed = 5.f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(1);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Zealot:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Zealot_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 5;

		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 이미지의 가로/세로 길이
		m_tUnitInfo.tMoveFrame.iWidth = 128;
		m_tUnitInfo.tMoveFrame.iHeight = 128;

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 40;
		m_tInfo.fCY = 40;

		// 유닛의 이동 스피드
		m_fSpeed = 4.f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(1);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Dark_Templar:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Dark_Templar_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 9;

		m_tUnitInfo.tMoveFrame.iWidth = 64;
		m_tUnitInfo.tMoveFrame.iHeight = 64;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 40;
		m_tInfo.fCY = 40;

		// 유닛의 이동 스피드
		m_fSpeed = 3.5f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(1);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Dragon:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 400;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Dragon_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 10;

		m_tUnitInfo.tMoveFrame.iWidth = 96;
		m_tUnitInfo.tMoveFrame.iHeight = 96;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 50;
		m_tInfo.fCY = 50;

		// 유닛의 이동 스피드
		m_fSpeed = 2.5f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(1);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Reaver:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Reaver_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 100;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 9;

		m_tUnitInfo.tMoveFrame.iWidth = 84;
		m_tUnitInfo.tMoveFrame.iHeight = 84;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;

		// 유닛의 이동 스피드
		m_fSpeed = 0.8f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(3);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Shuttle:
		break;

	case UNIT_NAME::Scout:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 150;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 100;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 2;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Scout_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 이미지의 가로/세로 길이
		m_tUnitInfo.tMoveFrame.iWidth = 72;
		m_tUnitInfo.tMoveFrame.iHeight = 72;

		// 인게임에서 가로/세로 길이
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;

		// 유닛의 이동 스피드
		m_fSpeed = 3.2f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(2);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(4);
	}
	break;

	case UNIT_NAME::Arbiter:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 100;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 150;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 4;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Arbiter_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 이미지의 가로/세로 길이
		m_tUnitInfo.tMoveFrame.iWidth = 76;
		m_tUnitInfo.tMoveFrame.iHeight = 76;

		// 인게임에서 가로/세로 길이
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;

		// 유닛의 이동 스피드
		m_fSpeed = 2.7f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(3);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(4);
	}
	break;

	case UNIT_NAME::Archon:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Archon_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 100;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 4;

		m_tUnitInfo.tMoveFrame.iWidth = 120;
		m_tUnitInfo.tMoveFrame.iHeight = 120;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 120;
		m_tInfo.fCY = 120;

		// 유닛의 이동 스피드
		m_fSpeed = 3.0f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(4);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(4);
		break;
	}

	case UNIT_NAME::Dark_Archon:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Dark_Archon_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 100;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 4;

		m_tUnitInfo.tMoveFrame.iWidth = 120;
		m_tUnitInfo.tMoveFrame.iHeight = 120;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 120;
		m_tInfo.fCY = 120;

		// 유닛의 이동 스피드
		m_fSpeed = 3.0f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(4);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(4);
		break;
	}

	case UNIT_NAME::Observer:
		break;

	case UNIT_NAME::Carrier:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 500;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 100;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 150;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 4;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Carrier_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 이미지의 가로/세로 길이
		m_tUnitInfo.tMoveFrame.iWidth = 128;
		m_tUnitInfo.tMoveFrame.iHeight = 128;

		// 인게임에서 가로/세로 길이
		m_tInfo.fCX = 128;
		m_tInfo.fCY = 128;

		// 유닛의 이동 스피드
		m_fSpeed = 2.6f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(5);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(5);
	}
	break;

	case UNIT_NAME::Interceptor:
		break;

	case UNIT_NAME::Corsair:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 200;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 100;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 150;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 4;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Corsair_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 이미지의 가로/세로 길이
		m_tUnitInfo.tMoveFrame.iWidth = 60;
		m_tUnitInfo.tMoveFrame.iHeight = 60;

		// 인게임에서 가로/세로 길이
		m_tInfo.fCX = 60;
		m_tInfo.fCY = 60;

		// 유닛의 이동 스피드
		m_fSpeed = 4.f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(2);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(3);
	}
	break;

	case UNIT_NAME::High_Templar:
	{
		// 공격력/방어력
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// 공격 범위 500
		m_tUnitInfo.iRange = 300;

		// 1초에 1번 공격
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// 인구수 1
		m_tUnitInfo.iPopulation = 1;

		// 유닛의 자체/공격 타입
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// 유닛의 프레임 키
		m_tUnitInfo.m_MoveFrameKey = L"Unit_High_Templar_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// 유닛의 DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 12;

		m_tUnitInfo.tMoveFrame.iWidth = 128;
		m_tUnitInfo.tMoveFrame.iHeight = 128;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// 인게임에서 프로브 가로/세로 길이
		m_tInfo.fCX = 35;
		m_tInfo.fCY = 35;

		// 유닛의 이동 스피드
		m_fSpeed = 2.f;

		// 유닛의 아래 나타나는 동그란 와이어
		Set_Wire(1);

		// 유닛의 체력과 쉴드를 나타내는 스탯바
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::END:
		break;
	default:
		break;
	}
}

void CUnit::Set_UnitStatus(UNIT_NAME _eUnitName)
{
	ZeroMemory(&m_tStatusFrameInfo.m_tStatusFrame, sizeof(FRAME));

	m_tStatusFrameInfo.m_tStatusFrame.iWidth = 154;
	m_tStatusFrameInfo.m_tStatusFrame.iHeight = 84;

	switch (_eUnitName)
	{
	case UNIT_NAME::Probe:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Probe_Status");
		break;
	case UNIT_NAME::Zealot:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Zealot_Status");
		break;
	case UNIT_NAME::Dark_Templar:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Templar_Status");
		break;
	case UNIT_NAME::Dragon:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dragon_Status");
		break;
	case UNIT_NAME::Reaver:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Reaver_Status");
		break;
	case UNIT_NAME::Shuttle:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Shuttle_Status");
		break;
	case UNIT_NAME::Scout:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Scout_Status");
		break;
	case UNIT_NAME::Arbiter:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Arbiter_Status");
		break;
	case UNIT_NAME::Archon:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Archon_Status");
		break;
	case UNIT_NAME::Dark_Archon:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_DarkArchon_Status");
		break;
	case UNIT_NAME::Observer:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Arbiter_Status");
		break;
	case UNIT_NAME::Carrier:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Carrier_Status");
		break;
	case UNIT_NAME::Interceptor:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Interceptor_Status");
		break;
	case UNIT_NAME::Corsair:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Corsair_Status");
		break;
	case UNIT_NAME::High_Templar:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_High_Templar_Status");
		break;
	case UNIT_NAME::END:
		break;
	default:
		break;
	}

	m_tStatusFrameInfo.m_tStatusInfo.fCX = 180;
	m_tStatusFrameInfo.m_tStatusInfo.fCY = 90;
	m_tStatusFrameInfo.m_tStatusInfo.fX = 400;
	m_tStatusFrameInfo.m_tStatusInfo.fY = 540;

	Update_Rect(m_tStatusFrameInfo.m_tStatusInfo, m_tStatusFrameInfo.m_tStatusRect);
}

void CUnit::Set_WireFrameInfo(UNIT_NAME _eUnitName)
{
	// 205 490		300 570
	m_tWireFrameInfo.m_tBigWireInfo.fX = 255;
	m_tWireFrameInfo.m_tBigWireInfo.fY = 530;
	m_tWireFrameInfo.m_tBigWireInfo.fCX = 100;
	m_tWireFrameInfo.m_tBigWireInfo.fCY = 80;

	Update_Rect(m_tWireFrameInfo.m_tBigWireInfo, m_tWireFrameInfo.m_tBigWireRect);

	m_tWireFrameInfo.m_tBigWireFrame.iFrameScene = 0;
	m_tWireFrameInfo.m_tBigWireFrame.iFrameCurr = 0;
	m_tWireFrameInfo.m_tBigWireFrame.iFrameStart = 0;
	m_tWireFrameInfo.m_tBigWireFrame.iFrameEnd = 6;

	m_tWireFrameInfo.m_tBigWireFrame.iWidth = 64;
	m_tWireFrameInfo.m_tBigWireFrame.iHeight = 64;

	m_tWireFrameInfo.m_tSmallWireFrame.iWidth = 32;
	m_tWireFrameInfo.m_tSmallWireFrame.iHeight = 32;

	switch (_eUnitName)
	{
	case UNIT_NAME::Probe:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Probe_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Probe_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Zealot:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Zealot_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Zealot_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Dark_Templar:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Templar_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Templar_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Dragon:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dragon_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dragon_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Reaver:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Reaver_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Reaver_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Shuttle:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Shuttle_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Shuttle_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Scout:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Scout_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Scout_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Arbiter:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Arbiter_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Arbiter_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Archon:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Archon_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Archon_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Dark_Archon:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Archon_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Archon_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Observer:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Observer_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Observer_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Carrier:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Carrier_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Carrier_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Interceptor:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Interceptor_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Interceptor_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::Corsair:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Corsair_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Corsair_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::High_Templar:
		// BigWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_High_Templar_WireBig");
		//==================================================================================================

		// SmallWireFrame
		//==================================================================================================
		m_tWireFrameInfo.m_SmallWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_High_Templar_WireSmall");
		//==================================================================================================
		break;
	case UNIT_NAME::END:
		break;
	default:
		break;
	}
}

void CUnit::Set_UnitState(UNIT_STATE _eUnitState)
{
	m_eUnitState = _eUnitState;
}
