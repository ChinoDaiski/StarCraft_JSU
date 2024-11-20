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
	int			m_iDrawID;			// ���콺�� �浹ó���� �Ǹ� 1, �ƴϸ� 0

	bool		m_bLock;			// �ش� ��鿡�� ����ϴ��� ���ϴ��� �Ǻ��ϴ� ����, true��� ������� �ʴ´�.

	SCENEID		m_moveScene;		// ��ư�� ������ ��� �̵��ϴ� ���� ���� ����

	RECT		m_tRealRect;		// ���� �׸��� �׷����� ��ġ
};