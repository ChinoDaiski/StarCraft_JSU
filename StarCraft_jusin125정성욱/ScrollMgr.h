#pragma once

#include "Include.h"

class CScrollMgr : public CSingleton<CScrollMgr>
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	float			Get_ScrollX() { return m_fScrollX; }
	float			Get_ScrollY() { return m_fScrollY; }
	void			Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void			Set_ScrollY(float _fY) { m_fScrollY += _fY; }
	void			Set_Scroll(float _fX, float _fY) { m_fScrollX = _fX; m_fScrollY = _fY; }
	void			Scroll_Lock(int _iCX, int _iCY);

private:
	float					m_fScrollX;
	float					m_fScrollY;
};

