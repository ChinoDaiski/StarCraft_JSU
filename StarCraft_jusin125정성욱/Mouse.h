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
	// ���� ���콺
	void LButtonDown(void);			// ���� ���콺�� ������ ���
	void LButtonPressing(void);		// ���� ���콺�� ������ ���� ���
	void LButtonUp(void);			// ���� ���콺�� �����ٰ� ���� ���

public:
	// ������ ���콺
	void RButtonDown(void);			// ������ ���콺�� ������ ���
	void RButtonPressing(void);		// ������ ���콺�� ������ ���� ���
	void RButtonUp(void);			// ������ ���콺�� �����ٰ� ���� ���

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

	POINT			m_tPos;			// ���콺�� ���� ��ǥ

	FRAME			m_tFrame;
	RECT			m_tRect;
	INFO			m_tInfo;

	DIR				m_eDir;

	bool			m_bInGame;		// ��ҿ��� false�� �⺻ ��Ǹ� ����ϴٰ�, ���� �ȿ� ������ true�� ���� ��� ���

	RECT			m_tDragRect;	// drag �Ҷ� �簢���� ����
	bool			m_bDrag;		// drag ���̶�� ���� Ȯ���� �ִ� ����

	bool			m_bClick;		// ���콺 Ŭ���� ������ true, �ƴϸ� false�� ���� ��� �ִ� ����
	bool			m_bClickMove;	// ���콺�� ������ ���������� �Ǵ��ϴ� ����, �������ٸ� true, �ƴ϶�� false ��ȯ
	POINT			m_tClickPos;	// ���콺�� ���� ������ ����/���� ��ǥ

	MOUSE_STATUS	m_eStatus;

	bool			m_bDrawTargetCircle;
	FRAME			m_tTargetFrame;

	// �ǹ��� ���� ��Ȳ�� ���, �ش��ϴ� �ǹ��� ������ ���
	bool			m_bDrawBuild;
	BUILD			m_eSelectBuildInfo;

	bool			m_bLbuttonDown;
};

