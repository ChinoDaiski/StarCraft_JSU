#include "stdafx.h"
#include "Dark_Templar.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"

CDark_Templar::CDark_Templar()
{
}


CDark_Templar::~CDark_Templar()
{
}

void CDark_Templar::Initialize(void)
{
	// ������ ���� - Probe�� ����
	Set_UnitInfo(UNIT_NAME::Dark_Templar);

	// ������ ���� ���� - �������� ����
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// Ȧ�� ����, ó������ Ȧ�尡 ���� �ʴ´�.
	m_bHold = false;

	Update();
}

int CDark_Templar::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::DARK_TEMPLAR_DEAD, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY);

		CSoundMgr::Get_Instance()->PlaySoundW(L"PDTDth00.wav", CHANNELID::Enemy, UNIT_SOUND);
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
	Update_Frame(m_tUnitInfo.tMoveFrame);

	return 0;
}

int CDark_Templar::Late_Update(void)
{
	return 0;
}

void CDark_Templar::Render(HDC hDC)
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

		// 07 19 -> 53 58
		m_tUnitInfo.m_MoveDC,
		m_tUnitInfo.tMoveFrame.iWidth * m_tUnitInfo.tMoveFrame.iFrameCurr + 7,
		m_tUnitInfo.tMoveFrame.iHeight * m_iDir + 19,

		46,
		38,
		RGB(255, 255, 255));

	// ���¹�
	if (m_bSelected)
		DrawStatusBar(hDC);
}

void CDark_Templar::Release(void)
{
}

void CDark_Templar::Update_State(void)
{
	switch (m_eUnitState)
	{
	case UNIT_STATE::Move:
		// �̵� ���� - Ȧ�尡 �ƴ϶�� �̵��Ѵ�.
		if (m_tUnitInfo.tMoveFrame.iFrameEnd != 9) {
			m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
			m_tUnitInfo.tMoveFrame.iFrameStart = 0;
			m_tUnitInfo.tMoveFrame.iFrameEnd = 9;
			m_tUnitInfo.tMoveFrame.dwFrameSpeed = 40;
		}

		// Ȧ�尡 �ɷ� �ִٸ� �̵����� �ʴ´�.
		if (m_bHold)
			return;

		// Ȧ�尡 �ƴ϶��, ��ǥ�������� �̵��Ѵ�.
		Move(m_tDstPos);
		break;

	case UNIT_STATE::Stop:
		// ���� ���� - ���� ������ ��ġ�� ���� ���������� �̵��� ��ġ�� �ٲ��.
		m_tUnitInfo.tMoveFrame.iFrameStart = 4;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 4;

		m_tDstPos.x = m_tInfo.fX;
		m_tDstPos.y = m_tInfo.fY;

		m_bUnitMove = false;
		break;

	case UNIT_STATE::Hold:
		// Ȧ�� ���� - Ȧ�� ���¿��� �̵����� �ʴ´�.
		m_bHold = true;

		m_bUnitMove = false;
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



		break;

	case UNIT_STATE::beAttacked:
		break;

	case UNIT_STATE::END:
		m_eUnitState = UNIT_STATE::Stop;
		break;
	default:
		break;
	}
}

void CDark_Templar::Attack(CObj * _pObj)
{
}
