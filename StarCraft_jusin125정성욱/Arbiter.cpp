#include "stdafx.h"
#include "Arbiter.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"

CArbiter::CArbiter()
{
}


CArbiter::~CArbiter()
{
}

void CArbiter::Initialize(void)
{
	m_iSize = 0;

	dwFrameTime = 0;
	dwFrameSpeed = 2000;

	// ������ ���� - Probe�� ����
	Set_UnitInfo(UNIT_NAME::Arbiter);

	// ������ ���� ���� - �������� ����
	Set_Relation(RELATION::Alliance);

	m_eUnitState = UNIT_STATE::END;

	// Ȧ�� ����, ó������ Ȧ�尡 ���� �ʴ´�.
	m_bHold = false;

	m_bUp = true;
	m_iSize = 0;
	m_bMove = false;

	Update();
}

int CArbiter::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Create_Effect(EFFECT::EXPLOSION_M, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY);

		CSoundMgr::Get_Instance()->PlaySoundW(L"pabDth00.wav", CHANNELID::Enemy, UNIT_SOUND);
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

int CArbiter::Late_Update(void)
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

void CArbiter::Render(HDC hDC)
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

void CArbiter::Release(void)
{
}

void CArbiter::Update_State(void)
{
	list<CObj*> lst;
	int fX, fY;
	switch (m_eUnitState)
	{
	case UNIT_STATE::IDLE:

		lst = *CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::ENEMY);

		m_pTarget = nullptr;

		fX = m_tInfo.fX;
		fY = m_tInfo.fY;
		if (!lst.empty()) {

			lst.sort([fX, fY](const auto& p1, const auto& p2) {
				POINT pt1 = p1->Get_Pos();
				POINT pt2 = p2->Get_Pos();
				return ((pt1.x - fX) * (pt1.x - fX) + (pt1.y - fY) * (pt1.y - fY)) < ((pt2.x - fX) * (pt2.x - fX) + (pt2.y - fY) * (pt2.y - fY));
			});

			if (Get_Distance(lst.front()) < m_tUnitInfo.iRange)
				m_pTarget = lst.front();
		}

		if (nullptr != m_pTarget)
			m_eUnitState = UNIT_STATE::Attack;

		break;

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

		m_bUnitMove = false;

		m_eUnitState = UNIT_STATE::IDLE;
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
		// Ÿ�ٰ� �ش� ������ �Ÿ��� �����Ÿ����� �� ��� Ÿ���� ���� �̵��Ѵ�.
		if (dwFrameTime + dwFrameSpeed < GetTickCount())
		{
			float _fX = m_pTarget->Get_Pos().x;
			float _fY = m_pTarget->Get_Pos().y;

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

			dwFrameTime = GetTickCount();
			CObjMgr::Get_Instance()->Create_Bullet(m_tInfo.fX, m_tInfo.fY, m_pTarget);
		}
		// Ÿ�ٰ� �ش� ������ �Ÿ��� �����Ÿ� �̳��� �����Ѵ�.
		else {
			m_eUnitState = UNIT_STATE::IDLE;
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

void CArbiter::Attack(CObj * _pObj)
{
}
