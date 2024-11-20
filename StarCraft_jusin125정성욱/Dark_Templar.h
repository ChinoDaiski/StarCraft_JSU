
#pragma once

#include "Unit.h"

class CDark_Templar : public CUnit {
public:
	CDark_Templar();
	virtual ~CDark_Templar();

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
};

