#pragma once

#include "Unit.h"

class CTerranUnit :	public CUnit {
public:
	CTerranUnit();
	virtual ~CTerranUnit();

public:
	virtual void		Initialize(void) = 0;
	virtual int			Update(void) = 0;
	virtual int			Late_Update(void) = 0;
	virtual void		Render(HDC hDC) = 0;
	virtual void		Release(void) = 0;

public:
	virtual void		Attack(void) = 0;
};

