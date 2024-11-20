#pragma once

#include "UIButton.h"

class CUnitButton : public CUIButton {
public:
	CUnitButton();
	CUnitButton(BUTTON_UNIT _eButtonInfo);
	virtual ~CUnitButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Click(void) override;
	void	Set_Button(BUTTON_UNIT _eButtonInfo) { m_eButtonInfo = _eButtonInfo; }

private:
	BUTTON_UNIT		m_eButtonInfo;
};

