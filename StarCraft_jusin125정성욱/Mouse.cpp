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
	GetCursorPos(&m_tPos);	// 현재 윈도위 좌표를 기준으로 마우스의 위치를 얻어오는 함수
	ScreenToClient(g_hWnd, &m_tPos);

	m_tInfo.fX = (float)m_tPos.x;
	m_tInfo.fY = (float)m_tPos.y;

	// SinglePlay 씬인 경우
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {

		// 마우스가 유닛 위에 있을 경우
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

		// 클릭이 된 상태이고, 클릭할 때의 마우스 위치와 현재 마우스 위치가 다르면 클릭한 상태로 움직인것이니 drag상태이다.
		if ((true == m_bClick) && (m_tClickPos.x != m_tPos.x) && (m_tClickPos.y != m_tPos.y) && (false == m_bClickMove)) {
			Set_Status(MOUSE_STATUS::DRAG);
		}

		// 드래그 상태일 경우
		if (m_eStatus == MOUSE_STATUS::DRAG) {
			// dragRect update하기
			m_tDragRect.right = m_tInfo.fX;
			m_tDragRect.bottom = m_tInfo.fY;
		}


	}
	
	// 특정 씬이 아닌 경우
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

		// 대각선, 양쪽을 움직이니 스피드값을 유지하기 위해 이렇게 작성
		float Diagonal = fSpeed * 0.85f;

		// drag 상태라면, 움직이지 않는다.
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

	// 인게임에서만 rect 출력
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		//// 드래그 라인 출력
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

	// 오른쪽 마우스를 눌렀을 경우
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

	// 싱글 플레이 씬일 경우
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {

		// 마우스 관련
		//======================================================================
		// 만약 마우스의 위치가 미니맵 사각형의 안이라면 넘긴다.
		if (PtInRect(&CMiniMap::Get_Instance()->Get_MiniMapRect(), m_tPos)) {

		}

		// 클릭 하지 않았다면
		else {
			Set_Click(true);
		}
		//======================================================================
		
		// 현재 건물을 생성하는 버튼을 눌러 건물 표시가 마우스를 따라다니며 출력된다면
		if (CBuildMgr::Get_Instance()->Get_CurrBuild() != BUILD::END) {
			// 현재 유저가 선택한 유닛은 프로브 1개이므로, 해당하는 유닛을 가져와 해당 위치에 어떤 건물을 생성하라고 명령을 내린다.
			POINT pt = CMouse::Get_Instance()->Get_Pos();
			list<CObj*> pObj = CUser::Get_Instance()->Get_SelectObjArr();
			dynamic_cast<CProbe*>(pObj.front())->Create_Build(CBuildMgr::Get_Instance()->Get_CurrBuild(), pt);

			// 다시 빌드 정보를 END로 바꾼다.
			CBuildMgr::Get_Instance()->Set_CurrBuild(BUILD::END);
		}


		// 유저 관련
		//======================================================================
		// 모든 유닛들을 검사하여 마우스와 충돌되는지 확인
		list<CObj*> pObj = CObjMgr::Get_Instance()->Get_SelectedObj();

		// 유닛을 클릭한다면, 단, 1개일 경우
		if (!pObj.empty()){
			CObj* temp = pObj.front();
			pObj.clear();
			pObj.push_back(temp);
			CUser::Get_Instance()->Set_SelectObj(pObj);
		}
		// 유닛을 클릭하지 않는다면
		else {
			// 넘어간다

			//// 유저가 선택한 유닛의 정보를 들고온다.
			//pObj = CUser::Get_Instance()->Get_SelectObjArr();

			//// 유저가 선택한 유닛이 있을 경우
			//if (!pObj.empty()) {
			//	
			//	// 마우스 y좌표의 위치가 UI의 윗부분보다 작을 경우
			//	if (m_tPos.y < CSinglePlayUI::Get_Instance()->Get_Rect().top) {
			//		// 아무런 유닛을 선택하지 않는것으로 한다.
			//		//CUser::Get_Instance()->Set_SelectObj(nullptr);
			//	}
			//	// 마우스 y좌표의 위치가 UI의 윗부분보다 클 경우
			//	else {
			//		// 유닛의 행동과 관련된 버튼을 누른다.
			//	}
			//}
		}

		// 마우스 상태가 Drag이면, 선택된 오브젝트 null로 만들기
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

	// 싱글 플레이 씬일 경우
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		
		// Drag 상태일 경우
		if (m_eStatus == MOUSE_STATUS::DRAG) {
			// DragRect안에 있는 유닛의 정보를 찾아 해당하는 유닛의 정보를 유저에게 보낸다.
			list<CObj*> pObj = CObjMgr::Get_Instance()->Get_SelectedObj();
			CUser::Get_Instance()->Set_SelectObj(pObj);
		}

		// 마우스 관련
		//======================================================================
		Set_Click(false);
		//======================================================================

		CUIButtonMgr::Get_Instance()->ClickUp();
	}
}

void CMouse::RButtonDown(void)
{
	// 싱글 플레이 씬일 경우
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {
		list<CObj*> pObj = CUser::Get_Instance()->Get_SelectObjArr();
		if (!pObj.empty()) {
			// 마우스의 현재 좌표가 싱글 플레이 UI와 충돌하지 않을 경우 
			if (!PtInRect(&CSinglePlayUI::Get_Instance()->Get_Rect(), m_tPos)) {
				// 현재 마우스의 좌표로 유닛을 이동한다.
				POINT pt = m_tPos;
				pt.x += CScrollMgr::Get_Instance()->Get_ScrollX();
				pt.y += CScrollMgr::Get_Instance()->Get_ScrollY();

				for (auto& iter : pObj) {
					if (iter->Get_Type() == OBJ_TYPE::UNIT) {
						// 이동 위치를 지정
						dynamic_cast<CUnit*>(iter)->Set_DstPos(pt);
						// 홀드 상태 해제
						dynamic_cast<CUnit*>(iter)->Set_Hold(false);
						// 이동 상태로 변환
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
	// 인자로 받은 상태가 움직이는 상태이고, 현재 상태가 drag라면, 상태를 변화시키지 않는다.
	// 왜냐하면 drag상태에선 스크롤 이동을 하면 안되기 때문이다.
	if (_eMouseStatus == MOUSE_STATUS::MOVE && m_eStatus == MOUSE_STATUS::DRAG)
		return;
	else if (m_eStatus == MOUSE_STATUS::DRAG && m_bDrag)
		return;
	else if (_eMouseStatus == MOUSE_STATUS::MOVE)
		;
	else if (m_eStatus == _eMouseStatus)
		return;

	//// 현재 상태가 IDLE 상태일 경우 인자로 받은 상태 IDLE과 같다면 넘기기
	//if (_eMouseStatus == MOUSE_STATUS::IDLE && m_eStatus == _eMouseStatus)
	//	return;

	//// 현재 상태가 ON_ALLIE일 경우
	//if (_eMouseStatus == MOUSE_STATUS::ON_ALLIE && m_eStatus == _eMouseStatus)
	//	return;

	// 외부에서 Get함수를 사용하여 알수 있도록 Status 갱신 
	m_eStatus = _eMouseStatus;

	m_tFrame.iFrameScene = (int)_eMouseStatus;

	switch (_eMouseStatus)
	{
	case MOUSE_STATUS::IDLE:	// 마우스 평소 상태
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameCurr = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.dwFrameSpeed = 70;
		m_bClickMove = false;
		break;

	case MOUSE_STATUS::MOVE:	// 마우스가 화면 가장 끝에 있을 경우
		Set_FrameSceneInfo((int)m_eDir * 2, (int)m_eDir * 2 + 2);
		m_tFrame.dwFrameSpeed = 70;
		break;

	case MOUSE_STATUS::ON_ALLIE:	// 동맹 오브젝트에 마우스가 올려져있을 경우
	case MOUSE_STATUS::ON_ENEMY:	// 적 오브젝트에 마우스가 올려져있을 경우
	case MOUSE_STATUS::ON_NEUTRAL:	// 중립 오브젝트에 마우스가 올려져있을 경우
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

		// 화면은 움직이지만 마우스의 좌표 처리는 800, 600 사이에 있다.

		// 마우스가 왼쪽을 향한 경우
		if (m_tInfo.fX <= 0) {
			eDir = DIR::LEFT;

			// 위쪽을 향한 경우
			if (m_tInfo.fY <= 0)
				eDir = DIR::TOP_LEFT;
			// 아래쪽을 향한 경우
			else if (m_tInfo.fY >= WINCY)
				eDir = DIR::BOTTOM_LEFT;
		}

		// 마우스가 오른쪽을 향한 경우
		if (m_tInfo.fX >= WINCX) {
			eDir = DIR::RIGHT;

			// 위쪽을 향한 경우
			if (m_tInfo.fY <= 0)
				eDir = DIR::TOP_RIGHT;
			// 아래쪽을 향한 경우
			else if (m_tInfo.fY >= WINCY)
				eDir = DIR::BOTTOM_RIGHT;
		}

		// 마우스가 위쪽을 향한 경우
		if (m_tInfo.fY <= 0) {
			eDir = DIR::TOP;

			// 왼쪽을 향한 경우
			if (m_tInfo.fX <= 0)
				eDir = DIR::TOP_LEFT;
			// 오른쪽을 향한 경우
			else if (m_tInfo.fX >= WINCX)
				eDir = DIR::TOP_RIGHT;
		}

		// 마우스가 아래쪽을 향한 경우
		if (m_tInfo.fY >= WINCY) {
			eDir = DIR::BOTTOM;

			// 왼쪽을 향한 경우
			if (m_tInfo.fX <= 0)
				eDir = DIR::BOTTOM_LEFT;
			// 오른쪽을 향한 경우
			else if (m_tInfo.fX >= WINCX)
				eDir = DIR::BOTTOM_RIGHT;
		}
	}

	// 이전 상태와 지금 상태가 다른 경우만 업데이트
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
	// m_bDrawTargetCircle이 false면 그리지 않았다는 뜻.
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
	// 마우스를 누르고 있을 경우 drag Rect 표현
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
