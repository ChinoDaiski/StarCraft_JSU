
#pragma once
#include "Obj.h"
class CScarab : public CObj {
public:
	CScarab();
	virtual ~CScarab();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	void moveTarget();

private:
	HDC		m_bulletDC;
	HDC		m_bulletMoveDC;
	FRAME	m_tbulletFrame;
};

