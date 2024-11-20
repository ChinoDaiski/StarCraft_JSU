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
	bool		checkOpenList(CNodeInfo* _nodeInfo);	// ���� lstOpen�� ���� �������� ��尡 �ִ� �˻��ϴ� �Լ�
	CNodeInfo*	Recursive_FindPath(CNodeInfo* _parentInfo, CTile* _endTile);	// �ֺ��� ���� Ž���� �ݺ��ϴ� �Լ�
	bool		checkFind_Path(POINT _startPos, POINT _endPos);					// ���� ã�Ҵ��� �˻��ϴ� �Լ�. ã������ true

public:
	void		reset(void);			// ������ �ִ� STL�� ��� �ʱ�ȭ �� �� ����ϴ� �Լ�

private:
	list<CNodeInfo*>	m_lstOpen;	// �ֺ��� �� �� �ִ� ����� ������ ��� �ִ� list
	list<CNodeInfo*>	m_lstClose;	// ���¸���Ʈ���� F�� ���� ���� ���� NodeInfo�� ��� �ִ� list

	list<CTile*>		m_lstPath;	// �� �� �ִ� ���� NodeInfo�� Parent�� ������ ���� ó������ ������� ���� ������ �ִ� vector
									// m_lstClose => 5, 4, 3, 2, 1
									// m_lstPath => 1, 2, 3, 4, 5

	//POINT	NodeDir[(int)DIR::END];	// ��� ������ ����(�밢�� ����)

	CTileMgr*		m_pTileMgr;		// Tile�� ������ ������ �ִ� TileMgr
};

