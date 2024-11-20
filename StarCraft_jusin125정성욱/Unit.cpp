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

	// ���� ��ü�� �簢�� ���������� ��ǥ���ϴ� ������ �浹���� ���� ���
	// ��ǥ�� �̵��Ѵ�.

	// ���� �̵���
	POINT	pt;
	pt.x = _fX;
	pt.y = _fY;
	if (!PtInRect(&m_tRect, pt)) {
		// ���� ��ġ�� ��ǥ�� ��ġ���� ���迡�� ������ �����Ѵ�.
		// ������ �´� �������� ã�� ������
		// �̵��� �ش� �������� speed�� ��ŭ �̵�

		float	fWidth = _fX - m_tInfo.fX;
		float	fHeight = _fY - m_tInfo.fY;

		float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acosf(fWidth / fDistance);

		m_fAngle = fRadian * (180.f / PI);

		if (_fY > m_tInfo.fY) {
			m_fAngle *= -1.f;
			m_fAngle += 360.f;
		}
		
		// m_fAngle�� 0 ~ 360 �� �����.
		while (!(0.f <= m_fAngle && m_fAngle <= 360.f))
		{
			if (0.f > m_fAngle)
				m_fAngle += 360.f;
			else if (360.f < m_fAngle)
				m_fAngle -= 360.f;
		}

		// ������ ���� ������ �����̴� ������ ���Ѵ�.
		// �� 16������. 22.5���� �����ϰ� �ִ� �̹����� ���.

		// ������ ���� �̵� ����� �ٲ۴�.
		m_iDir = (int)(m_fAngle / 22.5);

		// ���� �̵� ��ġ�� ��ǥ������ �ٸ��ٸ� �̵��Ѵ�.
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
					// �������� ���� ��ġ�� �Ѵ�.
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
	// �������� ���� ��Ȳ�̶�� ���¸� �ٲ�.
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
	// ������ �̸�
	m_tUnitInfo.eUnitName = _eUnitName;

	// ������ �ʻ�ȭ ����
	Set_Portrait(_eUnitName);

	// ������ ���̾� ������ ����
	Set_WireFrameInfo(_eUnitName);

	// ������ ����â ���� ����
	Set_UnitStatus(_eUnitName);

	m_tBuildInfo.m_eBuild == BUILD::END;

	switch (_eUnitName)
	{
	case UNIT_NAME::Probe:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Probe_Move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �̹����� ����/���� ����
		m_tUnitInfo.tMoveFrame.iWidth = 32;
		m_tUnitInfo.tMoveFrame.iHeight = 32;

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 30;
		m_tInfo.fCY = 30;

		// ������ �̵� ���ǵ�
		m_fSpeed = 5.f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(1);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Zealot:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Zealot_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 5;

		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �̹����� ����/���� ����
		m_tUnitInfo.tMoveFrame.iWidth = 128;
		m_tUnitInfo.tMoveFrame.iHeight = 128;

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 40;
		m_tInfo.fCY = 40;

		// ������ �̵� ���ǵ�
		m_fSpeed = 4.f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(1);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Dark_Templar:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Dark_Templar_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 9;

		m_tUnitInfo.tMoveFrame.iWidth = 64;
		m_tUnitInfo.tMoveFrame.iHeight = 64;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 40;
		m_tInfo.fCY = 40;

		// ������ �̵� ���ǵ�
		m_fSpeed = 3.5f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(1);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Dragon:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 400;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Dragon_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 10;

		m_tUnitInfo.tMoveFrame.iWidth = 96;
		m_tUnitInfo.tMoveFrame.iHeight = 96;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 50;
		m_tInfo.fCY = 50;

		// ������ �̵� ���ǵ�
		m_fSpeed = 2.5f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(1);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Reaver:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Reaver_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 100;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 9;

		m_tUnitInfo.tMoveFrame.iWidth = 84;
		m_tUnitInfo.tMoveFrame.iHeight = 84;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;

		// ������ �̵� ���ǵ�
		m_fSpeed = 0.8f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(3);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(2);
		break;
	}

	case UNIT_NAME::Shuttle:
		break;

	case UNIT_NAME::Scout:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 150;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 100;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 2;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Scout_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �̹����� ����/���� ����
		m_tUnitInfo.tMoveFrame.iWidth = 72;
		m_tUnitInfo.tMoveFrame.iHeight = 72;

		// �ΰ��ӿ��� ����/���� ����
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;

		// ������ �̵� ���ǵ�
		m_fSpeed = 3.2f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(2);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(4);
	}
	break;

	case UNIT_NAME::Arbiter:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 100;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 150;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 4;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Arbiter_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �̹����� ����/���� ����
		m_tUnitInfo.tMoveFrame.iWidth = 76;
		m_tUnitInfo.tMoveFrame.iHeight = 76;

		// �ΰ��ӿ��� ����/���� ����
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;

		// ������ �̵� ���ǵ�
		m_fSpeed = 2.7f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(3);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(4);
	}
	break;

	case UNIT_NAME::Archon:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Archon_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 100;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 4;

		m_tUnitInfo.tMoveFrame.iWidth = 120;
		m_tUnitInfo.tMoveFrame.iHeight = 120;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 120;
		m_tInfo.fCY = 120;

		// ������ �̵� ���ǵ�
		m_fSpeed = 3.0f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(4);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(4);
		break;
	}

	case UNIT_NAME::Dark_Archon:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Dark_Archon_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 100;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 4;

		m_tUnitInfo.tMoveFrame.iWidth = 120;
		m_tUnitInfo.tMoveFrame.iHeight = 120;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 120;
		m_tInfo.fCY = 120;

		// ������ �̵� ���ǵ�
		m_fSpeed = 3.0f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(4);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(4);
		break;
	}

	case UNIT_NAME::Observer:
		break;

	case UNIT_NAME::Carrier:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 500;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 100;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 150;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 4;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Carrier_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �̹����� ����/���� ����
		m_tUnitInfo.tMoveFrame.iWidth = 128;
		m_tUnitInfo.tMoveFrame.iHeight = 128;

		// �ΰ��ӿ��� ����/���� ����
		m_tInfo.fCX = 128;
		m_tInfo.fCY = 128;

		// ������ �̵� ���ǵ�
		m_fSpeed = 2.6f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(5);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(5);
	}
	break;

	case UNIT_NAME::Interceptor:
		break;

	case UNIT_NAME::Corsair:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 200;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 100;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 150;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 4;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Air;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_Corsair_move";
		//m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �̹����� ����/���� ����
		m_tUnitInfo.tMoveFrame.iWidth = 60;
		m_tUnitInfo.tMoveFrame.iHeight = 60;

		// �ΰ��ӿ��� ����/���� ����
		m_tInfo.fCX = 60;
		m_tInfo.fCY = 60;

		// ������ �̵� ���ǵ�
		m_fSpeed = 4.f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(2);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
		Set_StatusFrame(3);
	}
	break;

	case UNIT_NAME::High_Templar:
	{
		// ���ݷ�/����
		m_tUnitInfo.iAttack = 5;
		m_tUnitInfo.iArmor = 0;

		// ���� ���� 500
		m_tUnitInfo.iRange = 300;

		// 1�ʿ� 1�� ����
		m_tUnitInfo.dwOffense = 1000;

		m_tUnitInfo.iMaxHP = 20;
		m_tUnitInfo.iHP = m_tUnitInfo.iMaxHP;
		m_tUnitInfo.m_iMaxShield = 20;
		m_tUnitInfo.m_iShield = m_tUnitInfo.m_iMaxShield;

		// �α��� 1
		m_tUnitInfo.iPopulation = 1;

		// ������ ��ü/���� Ÿ��
		m_tUnitInfo.eType = UNIT_TYPE::Ground;
		m_tUnitInfo.eAttType = UNIT_ATTACK_TYPE::Ground;

		// ������ ������ Ű
		m_tUnitInfo.m_MoveFrameKey = L"Unit_High_Templar_move";
		m_tUnitInfo.m_AttackFrameKey = L"Unit_Probe_Attack";

		// ������ DC
		m_tUnitInfo.m_MoveDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_MoveFrameKey);
		m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		m_tUnitInfo.tMoveFrame.dwFrameTime = GetTickCount();
		m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
		m_tUnitInfo.tMoveFrame.iFrameStart = 0;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 12;

		m_tUnitInfo.tMoveFrame.iWidth = 128;
		m_tUnitInfo.tMoveFrame.iHeight = 128;
		//m_tUnitInfo.m_AttackDC = CBitmapMgr::Get_Instance()->Find_Image(m_tUnitInfo.m_AttackFrameKey);

		// �ΰ��ӿ��� ���κ� ����/���� ����
		m_tInfo.fCX = 35;
		m_tInfo.fCY = 35;

		// ������ �̵� ���ǵ�
		m_fSpeed = 2.f;

		// ������ �Ʒ� ��Ÿ���� ���׶� ���̾�
		Set_Wire(1);

		// ������ ü�°� ���带 ��Ÿ���� ���ȹ�
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
