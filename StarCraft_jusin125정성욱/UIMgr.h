#pragma once

#include "Singleton.h"

class CUIMgr : public CSingleton<CUIMgr> {
public:
	CUIMgr();
	~CUIMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

