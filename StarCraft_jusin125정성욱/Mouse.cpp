#include "stdafx.h"
#include "Mouse.h"
#include "BitmapMgr.h"
#include "Timer.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Unit.h"
#include "User.h"
#include "SceneMgr.h"
#include "MiniMap.h"
#include "ObjMgr.h"
#include "SinglePlayUI.h"
#include "UnitMgr.h"
#include "BuildMgr.h"
#include "Probe.h"
#include "UIButtonMgr.h"
#include "SoundMgr.h"

#pragma comment(lib, "msimg32.lib")

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{

	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_tFrame.iHeight = 50;
	m_tFrame.iWidth = 50;

	Set_Status(MOUSE_STATUS::IDLE);
	m_hDC = CBitmapMgr::Get_Instance()->Find_Image(L"Mouse");
	m_tFrame.dwFrameTime = GetTickCount();

	m_bInGame = false;
	m_bClick = false;
	m_bClickMove = false;

	m_bDrag = false;

	ShowCursor(false);

	m_bDrawTargetCircle = false;

	m_bLbuttonDown = false;
}

int CMouse::Update(void)
{
	GetCursorPos(&m_tPos);	// ���� ������ ��ǥ�� �������� ���콺�� ��ġ�� ������ �Լ�
	ScreenToClient(g_hWnd, &m_tPos);

	m_tInfo.fX = (float)m_tPos.x;
	m_tInfo.fY = (float)m_tPos.y;

	// SinglePlay ���� ���
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {

		// ���콺�� ���� ���� ���� ���
		list<CObj*> pObj = CObjMgr::Get_Instance()->Get_SelectedObj();
		if (!pObj.empty()) {
			switch (pObj.front()->Get_Relation())
			{
			case RELATION::Alliance:
				Set_Status(MOUSE_STATUS::ON_ALLIE);
				break;
			case RELATION::Enemy:
				Set_Status(MOUSE_STATUS::ON_ENEMY);
				break;
			case RELATION::Netural:
				Set_Status(MOUSE_STATUS::ON_NEUTRAL);
				break;
			case RELATION::END:
				break;
			}
		}

		if (m_eStatus != MOUSE_STATUS::MOVE && pObj.empty())
			Set_Status(MOUSE_STATUS::IDLE);

		// Ŭ���� �� �����̰�, Ŭ���� ���� ���콺 ��ġ�� ���� ���콺 ��ġ�� �ٸ��� Ŭ���� ���·� �����ΰ��̴� drag�����̴�.
		if ((true == m_bClick) && (m_tClickPos.x != m_tPos.x) && (m_tClickPos.y != m_tPos.y) && (false == m_bClickMove)) {
			Set_Status(MOUSE_STATUS::DRAG);
		}

		// �巡�� ������ ���
		if (m_eStatus == MOUSE_STATUS::DRAG) {
			// dragRect update�ϱ�
			m_tDragRect.right = m_tInfo.fX;
			m_tDragRect.bottom = m_tInfo.fY;
		}


	}
	
	// Ư�� ���� �ƴ� ���
	else {
		Set_Status(MOUSE_STATUS::IDLE);
	}

	Move_Frame();
	Update_Rect();
	Update_Animation();
	Move_TargetFrame();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	if (m_bInGame) {
		float fSpeed = CUser::Get_Instance()->Get_Speed();

		// �밢��, ������ �����̴� ���ǵ尪�� �����ϱ� ���� �̷��� �ۼ�
		float Diagonal = fSpeed * 0.85f;

		// drag ���¶��, �������� �ʴ´�.
		if (m_eStatus != MOUSE_STATUS::DRAG) {
			switch (m_eDir)
			{
			case DIR::RIGHT:
				CScrollMgr::Get_Instance()->Set_ScrollX(fSpeed);
				break;
			case DIR::TOP_RIGHT:
				CScrollMgr::Get_Instance()->Set_ScrollX(Diagonal);
				CScrollMgr::Get_Instance()->Set_ScrollY(-Diagonal);
				break;
			case DIR::TOP:
				CScrollMgr::Get_Instance()->Set_ScrollY(-fSpeed);
				break;
			case DIR::TOP_LEFT:
				CScrollMgr::Get_Instance()->Set_ScrollX(-Diagonal);
				CScrollMgr::Get_Instance()->Set_ScrollY(-Diagonal);
				break;
			case DIR::LEFT:
				CScrollMgr::Get_Instance()->Set_ScrollX(-fSpeed);
				break;
			case DIR::BOTTOM_LEFT:
				CScrollMgr::Get_Instance()->Set_ScrollX(-Diagonal);
				CScrollMgr::Get_Instance()->Set_ScrollY(Diagonal);
				break;
			case DIR::BOTTOM:
				CScrollMgr::Get_Instance()->Set_ScrollY(fSpeed);
				break;
			case DIR::BOTTOM_RIGHT:
				CScrollMgr::Get_Instance()->Set_ScrollX(Diagonal);
				CScrollMgr::Get_Instance()->Set_ScrollY(Diagonal);
				break;
			case DIR::END:
				break;
			default:
				break;
			}
		}
		CScrollMgr::Get_Instance()->Scroll_Lock(MAPCX, MAPCY);
	}
}

void CMouse::Render(HDC hDC)
{
	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// �ΰ��ӿ����� rect ���
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		//// �巡�� ���� ���
		//Draw_DragRect(hDC);
	}

	int iFrameScene = (int)m_tFrame.iFrameScene;
	if (m_tFrame.iFrameScene == (int)MOUSE_STATUS::DRAG)
		iFrameScene = 0;

	TransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,

		m_tInfo.fCX,
		m_tInfo.fCY,

		m_hDC,

		m_tFrame.iWidth * m_tFrame.iFrameCurr,
		m_tFrame.iHeight * iFrameScene,

		m_tFrame.iWidth,
		m_tFrame.iHeight,

		RGB(255,255,255));

	// ������ ���콺�� ������ ���
	if (m_bDrawTargetCircle) {
		TransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,

			m_tInfo.fCX,
			m_tInfo.fCY,

			m_hDC,

			m_tFrame.iWidth * m_tFrame.iFrameCurr,
			m_tFrame.iHeight * 5,

			m_tFrame.iWidth,
			m_tFrame.iHeight,

			RGB(255, 255, 255));
	}
}

void CMouse::Release(void)
{
	
}

void CMouse::LButtonDown(void)
{
	CSoundMgr::Get_Instance()->StopSound(CHANNELID::Mouse);
	CSoundMgr::Get_Instance()->PlaySoundW(L"mousedown.wav", CHANNELID::Mouse, UNIT_SOUND);

	m_bLbuttonDown = true;

	// �̱� �÷��� ���� ���
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {

		// ���콺 ����
		//======================================================================
		// ���� ���콺�� ��ġ�� �̴ϸ� �簢���� ���̶�� �ѱ��.
		if (PtInRect(&CMiniMap::Get_Instance()->Get_MiniMapRect(), m_tPos)) {

		}

		// Ŭ�� ���� �ʾҴٸ�
		else {
			Set_Click(true);
		}
		//======================================================================
		
		// ���� �ǹ��� �����ϴ� ��ư�� ���� �ǹ� ǥ�ð� ���콺�� ����ٴϸ� ��µȴٸ�
		if (CBuildMgr::Get_Instance()->Get_CurrBuild() != BUILD::END) {
			// ���� ������ ������ ������ ���κ� 1���̹Ƿ�, �ش��ϴ� ������ ������ �ش� ��ġ�� � �ǹ��� �����϶�� ����� ������.
			POINT pt = CMouse::Get_Instance()->Get_Pos();
			list<CObj*> pObj = CUser::Get_Instance()->Get_SelectObjArr();
			dynamic_cast<CProbe*>(pObj.front())->Create_Build(CBuildMgr::Get_Instance()->Get_CurrBuild(), pt);

			// �ٽ� ���� ������ END�� �ٲ۴�.
			CBuildMgr::Get_Instance()->Set_CurrBuild(BUILD::END);
		}


		// ���� ����
		//======================================================================
		// ��� ���ֵ��� �˻��Ͽ� ���콺�� �浹�Ǵ��� Ȯ��
		list<CObj*> pObj = CObjMgr::Get_Instance()->Get_SelectedObj();

		// ������ Ŭ���Ѵٸ�, ��, 1���� ���
		if (!pObj.empty()){
			CObj* temp = pObj.front();
			pObj.clear();
			pObj.push_back(temp);
			CUser::Get_Instance()->Set_SelectObj(pObj);
		}
		// ������ Ŭ������ �ʴ´ٸ�
		else {
			// �Ѿ��

			//// ������ ������ ������ ������ ���´�.
			//pObj = CUser::Get_Instance()->Get_SelectObjArr();

			//// ������ ������ ������ ���� ���
			//if (!pObj.empty()) {
			//	
			//	// ���콺 y��ǥ�� ��ġ�� UI�� ���κк��� ���� ���
			//	if (m_tPos.y < CSinglePlayUI::Get_Instance()->Get_Rect().top) {
			//		// �ƹ��� ������ �������� �ʴ°����� �Ѵ�.
			//		//CUser::Get_Instance()->Set_SelectObj(nullptr);
			//	}
			//	// ���콺 y��ǥ�� ��ġ�� UI�� ���κк��� Ŭ ���
			//	else {
			//		// ������ �ൿ�� ���õ� ��ư�� ������.
			//	}
			//}
		}

		// ���콺 ���°� Drag�̸�, ���õ� ������Ʈ null�� �����
		/*if (MOUSE_STATUS::DRAG == CMouse::Get_Instance()->Get_Status())
			CUser::Get_Instance()->Set_SelectObj(nullptr);*/
		//======================================================================
	}
}

void CMouse::LButtonPressing(void)
{
}

void CMouse::LButtonUp(void)
{
	m_bLbuttonDown = false;

	// �̱� �÷��� ���� ���
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		
		// Drag ������ ���
		if (m_eStatus == MOUSE_STATUS::DRAG) {
			// DragRect�ȿ� �ִ� ������ ������ ã�� �ش��ϴ� ������ ������ �������� ������.
			list<CObj*> pObj = CObjMgr::Get_Instance()->Get_SelectedObj();
			CUser::Get_Instance()->Set_SelectObj(pObj);
		}

		// ���콺 ����
		//======================================================================
		Set_Click(false);
		//======================================================================

		CUIButtonMgr::Get_Instance()->ClickUp();
	}
}

void CMouse::RButtonDown(void)
{
	// �̱� �÷��� ���� ���
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		list<CObj*> pObj = CUser::Get_Instance()->Get_SelectObjArr();
		if (!pObj.empty()) {
			// ���콺�� ���� ��ǥ�� �̱� �÷��� UI�� �浹���� ���� ��� 
			if (!PtInRect(&CSinglePlayUI::Get_Instance()->Get_Rect(), m_tPos)) {
				// ���� ���콺�� ��ǥ�� ������ �̵��Ѵ�.
				POINT pt = m_tPos;
				pt.x += CScrollMgr::Get_Instance()->Get_ScrollX();
				pt.y += CScrollMgr::Get_Instance()->Get_ScrollY();

				for (auto& iter : pObj) {
					if (iter->Get_Type() == OBJ_TYPE::UNIT) {
						// �̵� ��ġ�� ����
						dynamic_cast<CUnit*>(iter)->Set_DstPos(pt);
						// Ȧ�� ���� ����
						dynamic_cast<CUnit*>(iter)->Set_Hold(false);
						// �̵� ���·� ��ȯ
						dynamic_cast<CUnit*>(iter)->Set_UnitState(UNIT_STATE::Move);
					}
				}
				Set_TargetFrame(TARGET::ALLIE);
			}
		}
	}

}

void CMouse::RButtonPressing(void)
{
}

void CMouse::RButtonUp(void)
{
}

void CMouse::Set_Status(MOUSE_STATUS _eMouseStatus)
{
	// ���ڷ� ���� ���°� �����̴� �����̰�, ���� ���°� drag���, ���¸� ��ȭ��Ű�� �ʴ´�.
	// �ֳ��ϸ� drag���¿��� ��ũ�� �̵��� �ϸ� �ȵǱ� �����̴�.
	if (_eMouseStatus == MOUSE_STATUS::MOVE && m_eStatus == MOUSE_STATUS::DRAG)
		return;
	else if (m_eStatus == MOUSE_STATUS::DRAG && m_bDrag)
		return;
	else if (_eMouseStatus == MOUSE_STATUS::MOVE)
		;
	else if (m_eStatus == _eMouseStatus)
		return;

	//// ���� ���°� IDLE ������ ��� ���ڷ� ���� ���� IDLE�� ���ٸ� �ѱ��
	//if (_eMouseStatus == MOUSE_STATUS::IDLE && m_eStatus == _eMouseStatus)
	//	return;

	//// ���� ���°� ON_ALLIE�� ���
	//if (_eMouseStatus == MOUSE_STATUS::ON_ALLIE && m_eStatus == _eMouseStatus)
	//	return;

	// �ܺο��� Get�Լ��� ����Ͽ� �˼� �ֵ��� Status ���� 
	m_eStatus = _eMouseStatus;

	m_tFrame.iFrameScene = (int)_eMouseStatus;

	switch (_eMouseStatus)
	{
	case MOUSE_STATUS::IDLE:	// ���콺 ��� ����
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameCurr = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.dwFrameSpeed = 70;
		m_bClickMove = false;
		break;

	case MOUSE_STATUS::MOVE:	// ���콺�� ȭ�� ���� ���� ���� ���
		Set_FrameSceneInfo((int)m_eDir * 2, (int)m_eDir * 2 + 2);
		m_tFrame.dwFrameSpeed = 70;
		break;

	case MOUSE_STATUS::ON_ALLIE:	// ���� ������Ʈ�� ���콺�� �÷������� ���
	case MOUSE_STATUS::ON_ENEMY:	// �� ������Ʈ�� ���콺�� �÷������� ���
	case MOUSE_STATUS::ON_NEUTRAL:	// �߸� ������Ʈ�� ���콺�� �÷������� ���
		Set_FrameSceneInfo(0, 14);
		m_tFrame.dwFrameSpeed = 70;
		break;

	case MOUSE_STATUS::DRAG:
		m_tDragRect.left = m_tPos.x;
		m_tDragRect.top = m_tPos.y;
		m_bClickMove = true;
		m_bDrag = true;
		Set_FrameSceneInfo(5, 5);
		m_tFrame.dwFrameSpeed = 0;
		break;

	case MOUSE_STATUS::END:
		break;
	}
}

void CMouse::Update_Animation(void)
{
	DIR eDir = DIR::END;

	if (m_bInGame) {
		int iX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		// ȭ���� ���������� ���콺�� ��ǥ ó���� 800, 600 ���̿� �ִ�.

		// ���콺�� ������ ���� ���
		if (m_tInfo.fX <= 0) {
			eDir = DIR::LEFT;

			// ������ ���� ���
			if (m_tInfo.fY <= 0)
				eDir = DIR::TOP_LEFT;
			// �Ʒ����� ���� ���
			else if (m_tInfo.fY >= WINCY)
				eDir = DIR::BOTTOM_LEFT;
		}

		// ���콺�� �������� ���� ���
		if (m_tInfo.fX >= WINCX) {
			eDir = DIR::RIGHT;

			// ������ ���� ���
			if (m_tInfo.fY <= 0)
				eDir = DIR::TOP_RIGHT;
			// �Ʒ����� ���� ���
			else if (m_tInfo.fY >= WINCY)
				eDir = DIR::BOTTOM_RIGHT;
		}

		// ���콺�� ������ ���� ���
		if (m_tInfo.fY <= 0) {
			eDir = DIR::TOP;

			// ������ ���� ���
			if (m_tInfo.fX <= 0)
				eDir = DIR::TOP_LEFT;
			// �������� ���� ���
			else if (m_tInfo.fX >= WINCX)
				eDir = DIR::TOP_RIGHT;
		}

		// ���콺�� �Ʒ����� ���� ���
		if (m_tInfo.fY >= WINCY) {
			eDir = DIR::BOTTOM;

			// ������ ���� ���
			if (m_tInfo.fX <= 0)
				eDir = DIR::BOTTOM_LEFT;
			// �������� ���� ���
			else if (m_tInfo.fX >= WINCX)
				eDir = DIR::BOTTOM_RIGHT;
		}
	}

	// ���� ���¿� ���� ���°� �ٸ� ��츸 ������Ʈ
	if (eDir != m_eDir) {
		m_eDir = eDir;

		if (eDir == DIR::BOTTOM_LEFT || eDir == DIR::BOTTOM_RIGHT)
			int a = 10;


		if (m_eDir == DIR::END)
			Set_Status(MOUSE_STATUS::IDLE);
		else
			Set_Status(MOUSE_STATUS::MOVE);
	}

}

void CMouse::Update_Rect(void)
{
	int iGap = m_tInfo.fCX * 0.2;

	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));

	if (m_eStatus == MOUSE_STATUS::MOVE) {
		if (m_tInfo.fX <= 0) {
			m_tRect.left = LONG(-iGap);
			m_tRect.right = LONG(m_tInfo.fCX - iGap);
		}
		if (m_tInfo.fX >= WINCX) {
			m_tRect.left = LONG(WINCX - m_tInfo.fCX + iGap);
			m_tRect.right = LONG(WINCX + iGap);
		}
		if (m_tInfo.fY <= 0) {
			m_tRect.top = LONG(-iGap);
			m_tRect.bottom = LONG(m_tInfo.fCY - iGap);
		}
		if (m_tInfo.fY >= WINCY) {
			m_tRect.top = LONG(WINCY - m_tInfo.fCY + iGap);
			m_tRect.bottom = LONG(WINCY + iGap);
		}
	}
	else if (m_eStatus == MOUSE_STATUS::DRAG) {
		if (m_tInfo.fX <= 0) {
			m_tRect.left = 0;
			m_tRect.right = LONG(iGap);
		}
		if (m_tInfo.fX >= WINCX) {
			m_tRect.left = LONG(WINCX - iGap);
			m_tRect.right = LONG(WINCX);
		}
		if (m_tInfo.fY <= 0) {
			m_tRect.top = LONG(0);
			m_tRect.bottom = LONG(iGap);
		}
		if (m_tInfo.fY >= WINCY) {
			m_tRect.top = LONG(WINCY - iGap);
			m_tRect.bottom = LONG(WINCY);
		}
	}
}

void CMouse::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameCurr;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameCurr >= m_tFrame.iFrameEnd)
			m_tFrame.iFrameCurr = m_tFrame.iFrameStart;
	}
}

void CMouse::Set_Click(bool _bClick)
{
	m_bClick = _bClick;

	if (m_bClick) {
		m_tDragRect.left = m_tPos.x - 2;
		m_tDragRect.top = m_tPos.y - 2;
		m_tDragRect.right = m_tPos.x + 2;
		m_tDragRect.bottom = m_tPos.y + 2;
		m_tClickPos = m_tPos;
	}
	else {
		m_tDragRect.left = m_tPos.x;
		m_tDragRect.top = m_tPos.x;
		m_tDragRect.right = m_tPos.y;
		m_tDragRect.bottom = m_tPos.y;
		m_bClickMove = false;
		m_bDrag = false;
		Set_Status(MOUSE_STATUS::IDLE);
	}
}

void CMouse::Set_FrameSceneInfo(int _iFrameStart, int _iFrameEnd)
{
	m_tFrame.iFrameStart = _iFrameStart;
	m_tFrame.iFrameCurr = _iFrameStart;
	m_tFrame.iFrameEnd = _iFrameEnd;
}

void CMouse::Draw_Target(HDC hDC, TARGET _eTarget)
{
	// m_bDrawTargetCircle�� false�� �׸��� �ʾҴٴ� ��.
	if (!m_bDrawTargetCircle) {
		

		if (m_bDrawTargetCircle) {

		}
	}

}

void CMouse::Set_TargetFrame(TARGET _eTarget)
{
	switch (_eTarget)
	{
	case TARGET::ALLIE:
		m_tTargetFrame.iFrameStart = 0;
		m_tTargetFrame.iFrameEnd = 5;
		break;

	case TARGET::NEUTRAL:
		m_tTargetFrame.iFrameStart = 5;
		m_tTargetFrame.iFrameEnd = 10;
		break;

	case TARGET::ENEMY:
		m_tTargetFrame.iFrameStart = 10;
		m_tTargetFrame.iFrameEnd = 15;
		break;

	case TARGET::END:
		break;
	}
	m_tTargetFrame.dwFrameSpeed = 30;
	m_tTargetFrame.dwFrameTime = GetTickCount();
	m_tTargetFrame.iFrameCurr = m_tTargetFrame.iFrameStart;
	m_bDrawTargetCircle = true;
}

void CMouse::Move_TargetFrame(void)
{
	if (m_bDrawTargetCircle) {
		if (m_tTargetFrame.dwFrameTime + m_tTargetFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tTargetFrame.iFrameCurr;
			m_tTargetFrame.dwFrameTime = GetTickCount();

			if (m_tTargetFrame.iFrameCurr >= m_tTargetFrame.iFrameEnd) {
				m_tTargetFrame.iFrameCurr = m_tTargetFrame.iFrameStart;
				m_bDrawTargetCircle = false;
			}
		}
	}
}

void CMouse::Draw_DragRect(HDC hDC)
{
	// ���콺�� ������ ���� ��� drag Rect ǥ��
	if (m_bClickMove) {
		HPEN MyPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		HPEN OldPen = (HPEN)SelectObject(hDC, MyPen);

		MoveToEx(hDC, m_tDragRect.left, m_tDragRect.top, nullptr);
		LineTo(hDC, m_tDragRect.left, m_tDragRect.bottom);
		LineTo(hDC, m_tDragRect.right, m_tDragRect.bottom);
		LineTo(hDC, m_tDragRect.right, m_tDragRect.top);
		LineTo(hDC, m_tDragRect.left, m_tDragRect.top);

		SelectObject(hDC, OldPen);
		DeleteObject(MyPen);
	}
}
