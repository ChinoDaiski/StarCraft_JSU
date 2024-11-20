#pragma once
#include "TerranUnit.h"
class CScv : public CTerranUnit {
public:
	CScv();
	virtual ~CScv();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Attack(void) override;
};

