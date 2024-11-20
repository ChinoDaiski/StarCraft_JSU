#pragma once

#include "Include.h"

class CResourceMgr : public CSingleton<CResourceMgr> {
public:
	CResourceMgr();
	virtual ~CResourceMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// 처음 나오는 씬인 로고씬을 띄우는데 필요한 리소스를 비트맵 매니저에 로드하는 함수
	void Load_Logo(void);

	// 게임에서 사용하는 모든 리소스를 비트맵 매니저에 로드하는 함수
	void Load_All(void);
};

