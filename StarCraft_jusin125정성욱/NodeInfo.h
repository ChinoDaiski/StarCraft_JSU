#pragma once

#include "Include.h"
#include "Tile.h"

class CNodeInfo {
public:
	CNodeInfo(CTile* _currTile, CNodeInfo* _parentNode, int _iG, const INFO& _dstInfo);
	~CNodeInfo();

public:
	void Set_G(int _iG) { m_iG = _iG; }
	void Set_H(const INFO& _dstInfo) { m_iH = (int)std::abs(_dstInfo.fX - m_NodePos.x) + (int)std::abs(_dstInfo.fY - m_NodePos.y); }

	int Get_F() const { return m_iG + m_iH; }
	int Get_G() const { return m_iG; }
	int Get_H() const { return m_iH; }

public:
	CNodeInfo* Get_Parent() const {
		return m_parentNode;
	}
	POINT	Get_Pos() const {
		return m_NodePos;
	}
	CTile*	Get_Tile() const {
		return m_pTile;
	}

private:
	POINT	m_NodePos;
	CTile*	m_pTile;

	int		m_iG;	// 시작점으로 부터의 비용
	int		m_iH;	// 도착점까지의 비용

	CNodeInfo* m_parentNode;
};

