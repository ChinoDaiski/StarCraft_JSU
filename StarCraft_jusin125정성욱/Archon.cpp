#include "stdafx.h"
#include "Archon.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"
#include "EffectMgr.h"

CArchon::CArchon()
{
}

CArchon::~CArchon()
{
}

void CArchon::Initialize(void)
{
	// 유닛의 정보 - Probe로 설정
	Set_UnitInfo(UNIT_NAME::Archon);

	// 유닛의 관계 설정 - 동맹으로 설정
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// 홀드 설정, 처음에는 홀드가 되지 않는다.
	m_bHold = false;

	Update();

	m_bodyDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Archon_body");
	m_tbodyFrame.iFrameStart = 0;
	m_tbodyFrame.iFrameCurr = 0;
	m_tbodyFrame.iFrameEnd = 10;
	m_tbodyFrame.iWidth = 120;
	m_tbodyFrame.iHeight = 120;
	m_tbodyFrame.dwFrameSpeed = 50;
	m_tbodyFrame.dwFrameTime = GetTickCount();

	m_auloraDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Archon_aulora");
	m_tauloraFrame.iFrameStart = 0;
	m_tauloraFrame.iFrameCurr = 0;
	m_tauloraFrame.iFrameEnd = 15;
	m_tauloraFrame.iWidth = 120;
	m_tauloraFrame.iHeight = 120;
	m_tauloraFrame.dwFrameSpeed = 30;
	m_tauloraFrame.dwFrameTime = GetTickCount();

}

int CArchon::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::ZEALOT_DEAD, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY);
		CSoundMgr::Get_Instance()->PlaySoundW(L"PScDth00.wav", CHANNELID::Alliance, UNIT_SOUND);
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
	Update_Frame(m_tbodyFrame);
	Update_Frame(m_tauloraFrame);

	return 0;
}

int CArchon::Late_Update(void)
{
	return 0;
}

void CArchon::Render(HDC hDC)
{
	// 유닛 그리는 순서 : 그림자 -> 와이어 -> 유닛 -> 상태바 순으로 그리기
	// 유저에게 선택을 당했다면
	// 와이어와 상태바를 출력한다.

	// 그림자
	DrawShad(hDC);

	// 와이어
	if (m_bSelected)
		DrawWire(hDC);

	// 유닛 - 아콘은 몸체 -> 움직임 -> 오로라 순으로 그린다.
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 몸체
	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		m_bodyDC,
		m_tbodyFrame.iWidth * m_tbodyFrame.iFrameCurr,
		0,

		m_tbodyFrame.iWidth,
		m_tbodyFrame.iHeight,
		RGB(255, 255, 255));

	// 움직임
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

	// 오로라
	TransparentBlt(hDC,
		int(m_tRect.left - iScrollX),
		int(m_tRect.top - iScrollY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		m_auloraDC,
		m_tauloraFrame.iWidth * m_tauloraFrame.iFrameCurr,
		0,

		m_tauloraFrame.iWidth,
		m_tauloraFrame.iHeight,
		RGB(255, 255, 255));

	// 상태바
	if (m_bSelected)
		DrawStatusBar(hDC);

	// 판정 rect 그리기
	//HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	//MoveToEx(hDC, m_tRect.left - iScrollX, m_tRect.top - iScrollY, nullptr);
	//LineTo(hDC, m_tRect.left - iScrollX, m_tRect.bottom - iScrollY);
	//LineTo(hDC, m_tRect.right - iScrollX, m_tRect.bottom - iScrollY);
	//LineTo(hDC, m_tRect.right - iScrollX, m_tRect.top - iScrollY);
	//LineTo(hDC, m_tRect.left - iScrollX, m_tRect.top - iScrollY);

	//SelectObject(hDC, oldPen);
	//DeleteObject(myPen);
}

void CArchon::Release(void)
{
}

void CArchon::Update_State(void)
{
	switch (m_eUnitState)
	{
	case UNIT_STATE::Move:
		// 이동 상태 - 홀드가 아니라면 이동한다.
		if (m_tUnitInfo.tMoveFrame.iFrameEnd != 4) {
			m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
			m_tUnitInfo.tMoveFrame.iFrameStart = 0;
			m_tUnitInfo.tMoveFrame.iFrameEnd = 4;
			m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		}

		// 홀드가 걸려 있다면 이동하지 않는다.
		if (m_bHold)
			return;

		// 홀드가 아니라면, 목표지점으로 이동한다.
		Move(m_tDstPos);
		break;

	case UNIT_STATE::Stop:
		// 멈춤 상태 - 현재 유닛이 위치한 곳이 최종적으로 이동할 위치로 바뀐다.
		if (m_tUnitInfo.tMoveFrame.iFrameEnd != 4) {
			m_tUnitInfo.tMoveFrame.iFrameCurr = 0;
			m_tUnitInfo.tMoveFrame.iFrameStart = 0;
			m_tUnitInfo.tMoveFrame.iFrameEnd = 4;
			m_tUnitInfo.tMoveFrame.dwFrameSpeed = 50;
		}

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

void CArchon::Attack(CObj * _pObj)
{
}
