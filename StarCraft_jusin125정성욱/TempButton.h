#pragma once
#include "UIButton.h"

class CTempButton : public CUIButton {
public:
	CTempButton(BUTTON_UPGRADE _eButtonInfo = BUTTON_UPGRADE::END);
	virtual ~CTempButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Click(void) override;

private:
	BUTTON_UPGRADE		m_eButtonInfo;
};
