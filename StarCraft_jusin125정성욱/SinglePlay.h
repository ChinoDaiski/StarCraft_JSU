#pragma once

#include "Scene.h"

class CSinglePlay : public CScene {
public:
	CSinglePlay();
	virtual ~CSinglePlay();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

	virtual void Key_Input(void) override;

private:
	DWORD dwFrameTime[(int)UNIT_NAME::END];
	DWORD dwFrameSpeed[(int)UNIT_NAME::END];

	DWORD dwLevelTime;
	DWORD dwLevelSpeed;

	int m_iLevel;

	bool m_bLose;
	DWORD dwLoseTime;
	DWORD dwLoseSpeed;

	bool m_bWin;
	DWORD dwWinTime;
	DWORD dwWinSpeed;
};

