#pragma once

#include "Include.h"

class CMouse : public CSingleton<CMouse> {
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// 왼쪽 마우스
	void LButtonDown(void);			// 왼쪽 마우스를 눌렀을 경우
	void LButtonPressing(void);		// 왼쪽 마우스를 누르고 있을 경우
	void LButtonUp(void);			// 왼쪽 마우스를 눌렀다가 땟을 경우

public:
	// 오른쪽 마우스
	void RButtonDown(void);			// 오른쪽 마우스를 눌렀을 경우
	void RButtonPressing(void);		// 오른쪽 마우스를 누르고 있을 경우
	void RButtonUp(void);			// 오른쪽 마우스를 눌렀다가 땟을 경우

public:
	void Set_Status(MOUSE_STATUS _eMouseStatus);
	MOUSE_STATUS Get_Status(void) const {
		return m_eStatus;
	}

	const POINT& Get_Pos(void) const {
		return m_tPos;
	}
	void Update_Animation(void);
	void Update_Rect(void);
	void Move_Frame(void);

	void Set_InGame(bool _bInGame) {
		m_bInGame = _bInGame;
	}

	void Set_Click(bool _bClick);
	bool Get_bClick(void) const { return m_bClick; }
	void Set_FrameSceneInfo(int _iFrameStart, int _iFrameEnd);

	POINT Get_ClickPos(void) const { return m_tClickPos; }

public:
	void	Draw_Target(HDC hDC, TARGET _eTarget);
	void	Set_TargetFrame(TARGET _eTarget);
	void	Move_TargetFrame(void);

public:
	RECT	Get_DragRect(void) const { return m_tDragRect; }
	void	Set_DragRect(const RECT& _tDragRect) { m_tDragRect = _tDragRect; }
	void	Draw_DragRect(HDC hDC);

public:
	bool	Get_LbuttonDown(void) const { return m_bLbuttonDown; }
	void	Set_LbuttonDown(void) { m_bLbuttonDown = false; }

private:
	HDC				m_hDC;

	POINT			m_tPos;			// 마우스의 현재 좌표

	FRAME			m_tFrame;
	RECT			m_tRect;
	INFO			m_tInfo;

	DIR				m_eDir;

	bool			m_bInGame;		// 평소에는 false로 기본 모션만 출력하다가, 게임 안에 들어오면 true로 여러 모션 출력

	RECT			m_tDragRect;	// drag 할때 사각형의 범위
	bool			m_bDrag;		// drag 중이라는 것을 확인해 주는 변수

	bool			m_bClick;		// 마우스 클릭을 했으면 true, 아니면 false의 값을 들고 있는 변수
	bool			m_bClickMove;	// 마우스를 누르고 움직였는지 판단하는 변수, 움직였다면 true, 아니라면 false 반환
	POINT			m_tClickPos;	// 마우스를 누른 순간의 가로/세로 좌표

	MOUSE_STATUS	m_eStatus;

	bool			m_bDrawTargetCircle;
	FRAME			m_tTargetFrame;

	// 건물을 짓는 상황일 경우, 해당하는 건물의 정보를 출력
	bool			m_bDrawBuild;
	BUILD			m_eSelectBuildInfo;

	bool			m_bLbuttonDown;
};

