#pragma once

#include "UIButton.h"

class CBuildButton : public CUIButton {
public:
	CBuildButton();
	CBuildButton(BUTTON_BUILD _eButtonInfo);
	virtual ~CBuildButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Click(void) override;
	void	Set_Button(BUTTON_BUILD _eButtonInfo) { m_eButtonInfo = _eButtonInfo; }

private:
	BUTTON_BUILD		m_eButtonInfo;
};

