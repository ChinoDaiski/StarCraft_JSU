#pragma once

// 유닛을 여러개 선택했을 경우 출력되는 UI와 관련된 싱글턴

#include "Singleton.h"
#include "Include.h"
#include "User.h"
#include "Obj.h"

typedef struct _tagSmallWireInfo {
	HDC		m_smallDC;
	RECT	m_tRect;
	INFO	m_tInfo;
}SmallWire, *PSmallWire;


class UnitUIMgr : public CSingleton<UnitUIMgr> {
public:
	UnitUIMgr();
	~UnitUIMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override; 
	
private:
	SmallWire		m_UnitWire[12];
};

