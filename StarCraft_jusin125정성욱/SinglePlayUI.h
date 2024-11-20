#pragma once

#include "Include.h"
#include "Singleton.h"

class CSinglePlayUI : public CSingleton<CSinglePlayUI> {
public:
	CSinglePlayUI();
	~CSinglePlayUI();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void			Update_Rect(void);
	const RECT&		Get_Rect(void) const { return m_tRect; }

	void	Set_Level(int _iLevel) { m_iLevel = _iLevel; }

private:
	RECT		m_tRect;
	INFO		m_tInfo;

	HDC			m_bitmapDC;

	int			m_iLevel;
};

