#pragma once

#include "Singleton.h"
#include "Struct.h"

class CMiniMap : public CSingleton<CMiniMap>
{
public:
	CMiniMap();
	virtual ~CMiniMap();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

public:
	void	Update_MiniMap(void);
	void	Set_InGame(bool _bInGame) {
		m_bInGame = _bInGame;
	}
	const RECT&		Get_Rect() const {
		return m_tRect;
	}
	const RECT&		Get_MiniMapRect() const {
		return m_tMinimapRect;
	}

private:
	bool	m_bInGame;

	POINT	m_tStartPos;

	RECT	m_tRect;			// �̴ϸ� ���� ���׸��� �簢���� ����
	RECT	m_tMinimapRect;		// �̴ϸ� �簢���� ����
	INFO	m_tInfo;

	int		m_iWidth;
	int		m_iHeight;
};

