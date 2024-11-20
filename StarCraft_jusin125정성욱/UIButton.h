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
	int				m_iDrawID;		// ������ �ʰų� : 0 -> �⺻�� ������ ���� ����, �����ų� : 1, Ȱ��ȭ�� ���� �ʰų� : 2
	HDC				m_DC;			// �̹����� DC
};