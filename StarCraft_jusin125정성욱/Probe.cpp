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
	// ������ ���� - Probe�� ����
	Set_UnitInfo(UNIT_NAME::Probe);

	// ������ ���� ���� - �������� ����
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// Ȧ�� ����, ó������ Ȧ�尡 ���� �ʴ´�.
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
	// ���� �׸��� ���� : �׸��� -> ���̾� -> ���� -> ���¹� ������ �׸���
	// �������� ������ ���ߴٸ�
	// ���̾�� ���¹ٸ� ����Ѵ�.

	// �׸���
	DrawShad(hDC);

	// ���̾�
	if (m_bSelected)
		DrawWire(hDC);
	
	// ����
	DrawUnit(hDC);

	// ���¹�
	if (m_bSelected)
		DrawStatusBar(hDC);
}

void CProbe::Release(void)
{
}

void CProbe::Create_Build(BUILD _eBuild, POINT _tPos)
{
	// ������ ���� ���� - �ǹ������ �ٲ�
	m_eUnitState = UNIT_STATE::Build;
	
	// ���� �ǹ��� ���� ����
	m_eBuild = _eBuild;

	// ������ �ǹ��� ��ġ ����
	_tPos.x += CScrollMgr::Get_Instance()->Get_ScrollX();
	_tPos.y += CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tBuildPos = _tPos;
}

void CProbe::Update_State(void)
{
	switch (m_eUnitState)
	{
	case UNIT_STATE::Move:
		// �̵� ���� - Ȧ�尡 �ƴ϶�� �̵��Ѵ�.

		// Ȧ�尡 �ɷ� �ִٸ� �̵����� �ʴ´�.
		if (m_bHold)
			return;

		m_bUnitMove = true;

		// Ȧ�尡 �ƴ϶��, ��ǥ�������� �̵��Ѵ�.
		Move(m_tDstPos);
		break;

	case UNIT_STATE::Stop:
		// ���� ���� - ���� ������ ��ġ�� ���� ���������� �̵��� ��ġ�� �ٲ��.
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

	case UNIT_STATE::Mining:
		break;
	case UNIT_STATE::Build:
	{
		// ������ �ǹ��� ������ �Ÿ�
		float fNearDistance = 100.f;

		// ������ �ǹ��� ������ ���� �Ÿ� 
		float fCurrDistance = sqrt(pow(m_tInfo.fX - m_tBuildPos.x, 2.f) + pow(m_tInfo.fY - m_tBuildPos.y, 2.f));

		// �ǹ� ���� ���� - �ǹ��� ���� ��ó���� �� ���� �ش��ϴ� ��ġ�� �ǹ��� �����Ѵ�.

		// ������ �ǹ��� ������ �Ÿ��� ��ó �̵� �Ÿ����� �� ���
		if (fNearDistance < fCurrDistance) {
			m_tDstPos = m_tBuildPos;

			// �̵��Ѵ�.
			Move(m_tBuildPos);
		}
		// �����Ÿ� ������ ���� ���
		else {
			// ���� ��ġ�� �ǹ��� �����Ѵ�.
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
	// �̹� �����Ÿ� ���� �������� ���� ����Ʈ�� �����ش�.
	// ���� ������ ��ġ�� Ÿ���� ��ġ�� ���Ͽ� ������ ������, �ش� ������ �°� �̹��� ȸ�� �Լ��� ����Ͽ� �̹����� �����Ѵ�.

	INFO info = _pObj->Get_Info();
	float	fWidth = m_tInfo.fX - info.fX;
	float	fHeight = m_tInfo.fY - info.fY;

	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadian = acosf(fWidth / fDistance);

	float	m_fAngle = fRadian * (180.f / PI);

	// Ÿ���� �� �Ʒ��� ���� ���
	if (info.fY > m_tInfo.fY) {
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
	float m_iDir = (int)(m_fAngle / 22.5);

}
