#pragma once

#include "Include.h"
#include "stdafx.h"

class CScene
{
public:
	CScene(SCENEID _eID);
	virtual ~CScene();

public:
	virtual void	Initialize(void) PURE;
	virtual void	Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC _DC) PURE;
	virtual void	Release(void) PURE;

	virtual void	Key_Input(void) PURE;

public:
	SCENEID Get_ID() {
		return m_eID;
	}

private:
	SCENEID			m_eID;
};

