#pragma once
#include "Scene.h"

class CExit : public CScene {
public:
	CExit();
	virtual ~CExit();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

	virtual void Key_Input(void) override;
};