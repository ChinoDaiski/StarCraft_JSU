
#pragma once

#include "Unit.h"

class CCorsair : public CUnit {
public:
	CCorsair();
	virtual ~CCorsair();

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
	bool	m_bMove;
	bool	m_bUp;
	int		m_iSize;

private:
	DWORD		dwFrameTime;
	DWORD		dwFrameSpeed;
};

