#include "stdafx.h"
#include "Carrier.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"

CCarrier::CCarrier()
{
}


CCarrier::~CCarrier()
{
}

void CCarrier::Initialize(void)
{
	m_iSize = 0;

	// ������ ���� - Probe�� ����
	Set_UnitInfo(UNIT_NAME::Carrier);

	// ������ ���� ���� - �������� ����
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// Ȧ�� ����, ó������ Ȧ�尡 ���� �ʴ´�.
	m_bHold = false;

	Update();
}

int CCarrier::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::EXPLOSION_L, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY);

		CSoundMgr::Get_Instance()->PlaySoundW(L"PCaDth00.wav", CHANNELID::Enemy, UNIT_SOUND);
		return OBJ_DEAD;
		return OBJ_DEAD;
	}

	if (m_tDstPos.x == -1 && m_tDstPos.y == -1) {
		switch (m_eDir)
		{
		case DIR::LEFT:
			m_tInfo.fX -= m_fSpeed;
			m_iDir = 8;
			break;
		case DIR::TOP:
			m_tInfo.fY -= m_fSpeed;
			m_iDir = 4;
			break;
		case DIR::RIGHT:
			m_tInfo.fX += m_fSpeed;
			m_iDir = 0;
			break;
		case DIR::BOTTOM:
			m_tInfo.fY += m_fSpeed;
			m_iDir = 12;
			break;
		case DIR::END:
			break;
		default:
			break;
		}
	}
	else {
		Update_State();
	}
	Update_Rect();
	Update_Wire();
	Update_StatusBar();
	Update_Shadow();
	Update_Portrait();

	return 0;
}

int CCarrier::Late_Update(void)
{
	if (!m_bMove) {
		if (m_bUp) {
			m_iSize += 1;
			if (m_iSize > 50)
				m_bUp = false;
		}
		else {
			m_iSize -= 1;
			if (m_iSize < -50)
				m_bUp = true;
		}
	}

	return 0;
}

void CCarrier::Render(HDC hDC)
{
	// ���� �׸��� ���� : �׸��� -> ���̾� -> ���� -> ���¹� ������ �׸���
	// �������� ������ ���ߴٸ�
	// ���̾�� ���¹ٸ� ����Ѵ�.

	// �׸���
	DrawShad(hDC);

	// ���̾�
	if (m_bSelected)
		DrawWire(hDC);

	// ����
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY - m_iSize * 0.1),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_tUnitInfo.m_MoveDC,
		0, m_tUnitInfo.tMoveFrame.iHeight * m_iDir,
		m_tUnitInfo.tMoveFrame.iWidth,
		m_tUnitInfo.tMoveFrame.iHeight,
		RGB(255, 255, 255));

	// ���¹�
	if (m_bSelected)
		DrawStatusBar(hDC);
}

void CCarrier::Release(void)
{
}

void CCarrier::Update_State(void)
{
	switch (m_eUnitState)
	{
	case UNIT_STATE::Move:
		// �̵� ���� - Ȧ�尡 �ƴ϶�� �̵��Ѵ�.
		m_bMove = true;

		// Ȧ�尡 �ɷ� �ִٸ� �̵����� �ʴ´�.
		if (m_bHold)
			return;

		// Ȧ�尡 �ƴ϶��, ��ǥ�������� �̵��Ѵ�.
		Move(m_tDstPos);
		break;

	case UNIT_STATE::Stop:
		// ���� ���� - ���� ������ ��ġ�� ���� ���������� �̵��� ��ġ�� �ٲ��.
		m_tDstPos.x = m_tInfo.fX;
		m_tDstPos.y = m_tInfo.fY;
		m_bMove = false;

		break;

	case UNIT_STATE::Hold:
		// Ȧ�� ���� - Ȧ�� ���¿��� �̵����� �ʴ´�.
		m_bHold = true;
		m_bMove = false;
		break;

	case UNIT_STATE::Attack:
		// ���� ���� - ������ ����� �����Ÿ� ���� ���ٸ� ������� �̵��ϰ�, ��Ÿ� ���� ������ �����Ѵ�.
		//			  Ȧ�� ������ ��� �������� �ʴ´�.
		m_pTarget = CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::ENEMY)->front();

		// Ÿ���� ������ ���
		if (nullptr != m_pTarget) {
			// Ÿ�ٰ� �ش� ������ �Ÿ��� �����Ÿ����� �� ��� Ÿ���� ���� �̵��Ѵ�.
			if (m_tUnitInfo.iRange < Get_Distance(m_pTarget)) {
				// �������� ����� ��ġ�� �Ѵ�.
				m_tDstPos = m_pTarget->Get_Pos();
			}
			// Ÿ�ٰ� �ش� ������ �Ÿ��� �����Ÿ� �̳��� �����Ѵ�.
			else {
				CObjMgr::Get_Instance()->Create_Bullet(m_tInfo.fX, m_tInfo.fX, m_pTarget);
			}
		}



		break;

	case UNIT_STATE::beAttacked:
		break;

	case UNIT_STATE::END:
		break;
	default:
		break;
	}
}

void CCarrier::Attack(CObj * _pObj)
{
}
