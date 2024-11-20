#pragma once
#include "UIButton.h"
class CUpgradeButton :
	public CUIButton
{
public:
	CUpgradeButton();
	CUpgradeButton(BUTTON_UPGRADE _eButtonInfo);
	virtual ~CUpgradeButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Click(void) override;
	void	Set_Button(BUTTON_UPGRADE _eButtonInfo) { m_eButtonInfo = _eButtonInfo; }

private:
	BUTTON_UPGRADE		m_eButtonInfo;
};

