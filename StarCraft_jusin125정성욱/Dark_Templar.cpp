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
	// 유닛의 정보 - Probe로 설정
	Set_UnitInfo(UNIT_NAME::Dark_Templar);

	// 유닛의 관계 설정 - 동맹으로 설정
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// 홀드 설정, 처음에는 홀드가 되지 않는다.
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
	// 유닛 그리는 순서 : 그림자 -> 와이어 -> 유닛 -> 상태바 순으로 그리기
	// 유저에게 선택을 당했다면
	// 와이어와 상태바를 출력한다.

	// 그림자
	DrawShad(hDC);

	// 와이어
	if (m_bSelected)
		DrawWire(hDC);

	// 유닛
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

	// 상태바
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
		// 이동 상태 - 홀드가 아니라면 이동한다.
		if (m_tUnitInfo.tMoveFrame.iFrameEnd != 9) {
			m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
			m_tUnitInfo.tMoveFrame.iFrameStart = 0;
			m_tUnitInfo.tMoveFrame.iFrameEnd = 9;
			m_tUnitInfo.tMoveFrame.dwFrameSpeed = 40;
		}

		// 홀드가 걸려 있다면 이동하지 않는다.
		if (m_bHold)
			return;

		// 홀드가 아니라면, 목표지점으로 이동한다.
		Move(m_tDstPos);
		break;

	case UNIT_STATE::Stop:
		// 멈춤 상태 - 현재 유닛이 위치한 곳이 최종적으로 이동할 위치로 바뀐다.
		m_tUnitInfo.tMoveFrame.iFrameStart = 4;
		m_tUnitInfo.tMoveFrame.iFrameEnd = 4;

		m_tDstPos.x = m_tInfo.fX;
		m_tDstPos.y = m_tInfo.fY;

		m_bUnitMove = false;
		break;

	case UNIT_STATE::Hold:
		// 홀드 상태 - 홀드 상태에선 이동하지 않는다.
		m_bHold = true;

		m_bUnitMove = false;
		break;

	case UNIT_STATE::Attack:
		// 공격 상태 - 공격할 대상이 사정거리 내에 없다면 대상으로 이동하고, 사거리 내에 들어오면 공격한다.
		//			  홀드 상태일 경우 움직이지 않는다.

		// 타겟이 존재할 경우
		if (nullptr != m_pTarget) {

			// 타겟과 해당 유닛의 거리가 사정거리보다 멀 경우 타겟을 향해 이동한다.
			if (m_tUnitInfo.iRange < Get_Distance(m_pTarget)) {
				// 목적지를 상대의 위치로 한다.
				m_tDstPos = m_pTarget->Get_Pos();
			}
			// 타겟과 해당 유닛의 거리가 사정거리 이내면 공격한다.
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
