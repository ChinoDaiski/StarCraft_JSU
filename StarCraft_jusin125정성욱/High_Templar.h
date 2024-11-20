

#pragma once

#include "Unit.h"

class CHigh_Templar : public CUnit {
public:
	CHigh_Templar();
	virtual ~CHigh_Templar();

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
	DWORD		dwFrameTime;
	DWORD		dwFrameSpeed;
};

