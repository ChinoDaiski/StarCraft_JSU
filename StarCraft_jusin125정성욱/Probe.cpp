#include "stdafx.h"
#include "Probe.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "BuildMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"

CProbe::CProbe()
{
}

CProbe::~CProbe()
{
}

void CProbe::Initialize(void)
{
	// 유닛의 정보 - Probe로 설정
	Set_UnitInfo(UNIT_NAME::Probe);

	// 유닛의 관계 설정 - 동맹으로 설정
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// 홀드 설정, 처음에는 홀드가 되지 않는다.
	m_bHold = false;

	m_PlgDC = CBitmapMgr::Get_Instance()->Find_Image(L"Probe_Plg");
	m_ResetDC = CBitmapMgr::Get_Instance()->Find_Image(L"Probe_Reset");

	Update();
}

int CProbe::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::EXPLOSION_S, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY);

		CSoundMgr::Get_Instance()->PlaySoundW(L"pprdth00.wav", CHANNELID::Enemy, UNIT_SOUND);
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


	return 0;
}

int CProbe::Late_Update(void)
{
	return 0;
}

void CProbe::Render(HDC hDC)
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
	DrawUnit(hDC);

	// 상태바
	if (m_bSelected)
		DrawStatusBar(hDC);
}

void CProbe::Release(void)
{
}

void CProbe::Create_Build(BUILD _eBuild, POINT _tPos)
{
	// 유닛의 현재 상태 - 건물짓기로 바꿈
	m_eUnitState = UNIT_STATE::Build;
	
	// 지을 건물의 정보 설정
	m_eBuild = _eBuild;

	// 생성할 건물의 위치 설정
	_tPos.x += CScrollMgr::Get_Instance()->Get_ScrollX();
	_tPos.y += CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tBuildPos = _tPos;
}

void CProbe::Update_State(void)
{
	switch (m_eUnitState)
	{
	case UNIT_STATE::Move:
		// 이동 상태 - 홀드가 아니라면 이동한다.

		// 홀드가 걸려 있다면 이동하지 않는다.
		if (m_bHold)
			return;

		m_bUnitMove = true;

		// 홀드가 아니라면, 목표지점으로 이동한다.
		Move(m_tDstPos);
		break;

	case UNIT_STATE::Stop:
		// 멈춤 상태 - 현재 유닛이 위치한 곳이 최종적으로 이동할 위치로 바뀐다.
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

	case UNIT_STATE::Mining:
		break;
	case UNIT_STATE::Build:
	{
		// 생성할 건물과 유닛의 거리
		float fNearDistance = 100.f;

		// 생성할 건물과 유닛의 현재 거리 
		float fCurrDistance = sqrt(pow(m_tInfo.fX - m_tBuildPos.x, 2.f) + pow(m_tInfo.fY - m_tBuildPos.y, 2.f));

		// 건물 생성 상태 - 건물을 지을 근처까지 간 다음 해당하는 위치에 건물을 생성한다.

		// 생성할 건물과 유닛의 거리가 근처 이동 거리보다 멀 경우
		if (fNearDistance < fCurrDistance) {
			m_tDstPos = m_tBuildPos;

			// 이동한다.
			Move(m_tBuildPos);
		}
		// 사정거리 안으로 들어올 경우
		else {
			// 생성 위치에 건물을 생성한다.
			CBuildMgr::Get_Instance()->create_Build(m_eBuild, m_tBuildPos, SCENEID::SINGLEPLAY);
			Set_UnitState(UNIT_STATE::Stop);
		}

	}
	break;
	
	case UNIT_STATE::END:
		break;
	default:
		break;
	}

}

void CProbe::Attack(CObj* _pObj)
{
	// 이미 사정거리 내로 들어왔으니 공격 이펙트만 보여준다.
	// 현재 유닛의 위치와 타겟의 위치를 비교하여 각도를 구한후, 해당 각도에 맞게 이미지 회전 함수를 사용하여 이미지를 조정한다.

	INFO info = _pObj->Get_Info();
	float	fWidth = m_tInfo.fX - info.fX;
	float	fHeight = m_tInfo.fY - info.fY;

	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadian = acosf(fWidth / fDistance);

	float	m_fAngle = fRadian * (180.f / PI);

	// 타겟이 더 아래에 있을 경우
	if (info.fY > m_tInfo.fY) {
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
	float m_iDir = (int)(m_fAngle / 22.5);

}
