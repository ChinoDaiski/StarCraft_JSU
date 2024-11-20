#pragma once

#include "Include.h"
#include "NodeInfo.h"
#include "TileMgr.h"

class CFindPath {
public:
	CFindPath();
	~CFindPath();

public:
	list<CTile*>	GetPath(CTile* _startTile, CTile* _endTile);

public:
	bool		checkOpenList(CNodeInfo* _nodeInfo);	// 기존 lstOpen에 현재 넣으려는 노드가 있는 검사하는 함수
	CNodeInfo*	Recursive_FindPath(CNodeInfo* _parentInfo, CTile* _endTile);	// 주변의 길을 탐색을 반복하는 함수
	bool		checkFind_Path(POINT _startPos, POINT _endPos);					// 길을 찾았는지 검사하는 함수. 찾았으면 true

public:
	void		reset(void);			// 가지고 있는 STL을 모두 초기화 할 때 사용하는 함수

private:
	list<CNodeInfo*>	m_lstOpen;	// 주변에 갈 수 있는 길들의 정보를 담고 있는 list
	list<CNodeInfo*>	m_lstClose;	// 오픈리스트에서 F의 값이 가장 작은 NodeInfo를 담고 있는 list

	list<CTile*>		m_lstPath;	// 갈 수 있는 길의 NodeInfo의 Parent를 역으로 돌려 처음부터 사용자의 길을 가지고 있는 vector
									// m_lstClose => 5, 4, 3, 2, 1
									// m_lstPath => 1, 2, 3, 4, 5

	//POINT	NodeDir[(int)DIR::END];	// 노드 방향의 정보(대각선 포함)

	CTileMgr*		m_pTileMgr;		// Tile의 정보를 가지고 있는 TileMgr
};

