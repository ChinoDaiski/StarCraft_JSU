#pragma once

#include "Include.h"

class CKeyMgr : public CSingleton<CKeyMgr>
{
public:
	CKeyMgr();
	virtual ~CKeyMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	bool		Key_Pressing(int iKey);
	bool		Key_Down(int iKey);
	bool		Key_Up(int iKey);

private:
	bool		m_bKeyState[VK_MAX];
};

