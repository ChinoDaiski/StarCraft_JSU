#pragma once

#include "Singleton.h"
#include "Include.h"
#include "Obj.h"

enum class KIND { Tile, Terran, Protoss, Zerg, End };

class CEditorUI : public CSingleton<CEditorUI> {
public:
	CEditorUI();
	virtual ~CEditorUI();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Update_Rect(void);
	RECT	Get_Rect(void) const {
		return m_tRect;
	}

private:
	RECT		m_tRect;
	INFO		m_tInfo;

	HDC			m_bitmapDC;

	vector<CObj*>	m_vecButton[(int)KIND::End];
};

