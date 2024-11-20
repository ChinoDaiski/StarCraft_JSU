#pragma once

#include "Include.h"

class CTimer : public CSingleton<CTimer>{
public:
	CTimer();
	~CTimer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	DWORD Get_Time() {
		return m_dwTimer;
	}

private:
	DWORD			m_dwTimer;
};

