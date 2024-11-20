
#pragma once

#include "Unit.h"

class CArchon : public CUnit {
public:
	CArchon();
	virtual ~CArchon();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	void	Update_State(void) override;

public:
	virtual void		Attack(CObj* _pObj) override;

private:
	HDC		m_bodyDC;
	FRAME	m_tbodyFrame;

	HDC		m_auloraDC;
	FRAME	m_tauloraFrame;
};

