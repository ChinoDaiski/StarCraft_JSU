#pragma once

#include "UIButton.h"

class CActionButton : public CUIButton {
public:
	CActionButton();
	CActionButton(BUTTON_ACTION _eButtonInfo);
	virtual ~CActionButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Click(void) override;
	void	Set_Button(BUTTON_ACTION _eButtonInfo) { m_eButtonInfo = _eButtonInfo; }

private:
	BUTTON_ACTION		m_eButtonInfo;
};