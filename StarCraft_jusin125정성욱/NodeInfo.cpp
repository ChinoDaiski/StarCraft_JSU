#include "stdafx.h"
#include "NodeInfo.h"


CNodeInfo::CNodeInfo(CTile* _currTile, CNodeInfo* _parentNode, int _iG, const INFO& _dstInfo)
	: m_pTile(_currTile), m_parentNode(_parentNode), m_iG(_iG)
{
	Set_H(_dstInfo);

	POINT pt;
	pt.x = _currTile->Get_Info().fX;
	pt.y = _currTile->Get_Info().fY;

	m_NodePos = pt;
}


CNodeInfo::~CNodeInfo()
{
}
