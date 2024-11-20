#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

	void Set_EffectInfo(HDC _EffectDC, const FRAME& _tEffectFrame);

private:
	HDC		m_EffectDC;
	FRAME	m_tEffectFrame;
};

