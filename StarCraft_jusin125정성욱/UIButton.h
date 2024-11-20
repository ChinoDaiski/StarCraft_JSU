#pragma once

#include "Obj.h"


class CUIButton : public CObj {
public:
	CUIButton();
	virtual ~CUIButton();

public:
	virtual void		Initialize(void) PURE;
	virtual int			Update(void) PURE;
	virtual int			Late_Update(void) PURE;
	virtual void		Render(HDC hDC) PURE;
	virtual void		Release(void) PURE;

public:
	virtual void		Click(void) PURE;
	void	Set_DrawID(int _iID) { m_iDrawID = _iID; }
	int		Get_DrawID(void) { return m_iDrawID; }


protected:
	int				m_iDrawID;		// 누르지 않거나 : 0 -> 기본이 누르지 않은 상태, 누르거나 : 1, 활성화가 되지 않거나 : 2
	HDC				m_DC;			// 이미지의 DC
};