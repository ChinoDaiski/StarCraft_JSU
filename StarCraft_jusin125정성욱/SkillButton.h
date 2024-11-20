#pragma once
#include "UIButton.h"
class CSkillButton : public CUIButton {
public:
	CSkillButton();
	CSkillButton(BUTTON_SKILL _eButtonInfo);
	virtual ~CSkillButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	virtual void		Click(void) override;
	void	Set_Button(BUTTON_SKILL _eButtonInfo) { m_eButtonInfo = _eButtonInfo; }

private:
	BUTTON_SKILL		m_eButtonInfo;
};

