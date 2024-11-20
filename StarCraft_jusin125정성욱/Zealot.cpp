#include "stdafx.h"
#include "Zealot.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"

CZealot::CZealot()
{
}


CZealot::~CZealot()
{
}

void CZealot::Initialize(void)
{
	// ������ ���� - Probe�� ����
	Set_UnitInfo(UNIT_NAME::Zealot);

	// ������ ���� ���� - �������� ����
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// Ȧ�� ����, ó������ Ȧ�尡 ���� �ʴ´�.
	m_bHold = false;

	Update();
}

int CZealot::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::ZEALOT_DEAD, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY);

		CSoundMgr::Get_Instance()->PlaySoundW(L"pzeDth00.wav", CHANNELID::Enemy, UNIT_SOUND);
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
		m_pTarget = nullptr;
		Update_State();
	}
	Update_Rect();
	Update_Wire();
	Update_StatusBar();
	Update_Shadow();
	Update_Portrait();
	Update_Frame(m_tUnitInfo.tMoveFrame);

	return 0;
}

int CZealot::Late_Update(void)
{
	return 0;
}

void CZealot::Render(HDC hDC)
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
		int(m_tRect.top - iScrollY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		// 50 50 -> 86 86
		m_tUnitInfo.m_MoveDC,
		m_tUnitInfo.tMoveFrame.iWidth * m_tUnitInfo.tMoveFrame.iFrameCurr + 48,
		m_tUnitInfo.tMoveFrame.iHeight * m_iDir + 48,

		36,
		36,
		RGB(255, 255, 255));

	// ���¹�
	if (m_bSelected)
		DrawStatusBar(hDC);
}

void CZealot::Release(void)
{
}

void CZealot::Update_State(void)
{
	switch (m_eUnitState)
	{
	case UNIT_STATE::Move:
		// �̵� ���� - Ȧ�尡 �ƴ϶�� �̵��Ѵ�.

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
		m_tUnitInfo.tMoveFrame.iFrameCurr = 4;
		m_bUnitMove = false;
		break;

	case UNIT_STATE::Hold:
		// Ȧ�� ���� - Ȧ�� ���¿��� �̵����� �ʴ´�.
		m_bHold = true;
		m_bUnitMove = false;
		m_tUnitInfo.tMoveFrame.iFrameCurr = 4;
		break;

	case UNIT_STATE::Attack:
		// ���� ���� - ������ ����� �����Ÿ� ���� ���ٸ� ������� �̵��ϰ�, ��Ÿ� ���� ������ �����Ѵ�.
		//			  Ȧ�� ������ ��� �������� �ʴ´�.

		// Ÿ���� ������ ���
		if (nullptr != m_pTarget) {

			// Ÿ�ٰ� �ش� ������ �Ÿ��� �����Ÿ����� �� ��� Ÿ���� ���� �̵��Ѵ�.
			if (m_tUnitInfo.iRange < Get_Distance(m_pTarget)) {
				// �������� ����� ��ġ�� �Ѵ�.
				m_tDstPos = m_pTarget->Get_Pos();
			}
			// Ÿ�ٰ� �ش� ������ �Ÿ��� �����Ÿ� �̳��� �����Ѵ�.
			else {
				//Attack();
			}

		}

		m_tUnitInfo.tMoveFrame.iFrameCurr = 4;

		break;

	case UNIT_STATE::beAttacked:
		break;

	case UNIT_STATE::END:
		break;
	default:
		break;
	}

}

void CZealot::Attack(CObj * _pObj)
{
}
