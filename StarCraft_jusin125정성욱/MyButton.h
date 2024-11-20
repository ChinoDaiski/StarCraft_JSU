#pragma once

#include "Obj.h"

class CMyButton : public CObj {
public:
	CMyButton();
	virtual ~CMyButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_RealRect(const RECT& _rt) {
		m_tRealRect = _rt;
	}
	void		Set_moveScene(SCENEID _eScene) {
		m_moveScene = _eScene;
	}

private:
	int			m_iDrawID;			// 마우스와 충돌처리가 되면 1, 아니면 0

	bool		m_bLock;			// 해당 장면에서 사용하는지 안하는지 판별하는 변수, true라면 사용하지 않는다.

	SCENEID		m_moveScene;		// 버튼을 눌렀을 경우 이동하는 씬에 대한 정보

	RECT		m_tRealRect;		// 실제 그림이 그려지는 위치
};