
#pragma once
#include "Scene.h"

class CWin : public CScene {
public:
	CWin();
	virtual ~CWin();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

	virtual void Key_Input(void) override;
};