#include "stdafx.h"
#include "FindPath.h"
#include "TileMgr.h"


CFindPath::CFindPath()
	: m_pTileMgr(CTileMgr::Get_Instance())
{
	/*NodeDir[(int)DIR::LEFT].x = -1;
	NodeDir[(int)DIR::LEFT].y = 0;

	NodeDir[(int)DIR::RIGHT].x = 1;
	NodeDir[(int)DIR::RIGHT].y = 0;

	NodeDir[(int)DIR::TOP].x = 0;
	NodeDir[(int)DIR::TOP].y = -1;

	NodeDir[(int)DIR::BOTTOM].x = 0;
	NodeDir[(int)DIR::BOTTOM].y = 1;

	NodeDir[(int)DIR::TOP_LEFT].x = -1;
	NodeDir[(int)DIR::TOP_LEFT].y = -1;

	NodeDir[(int)DIR::TOP_RIGHT].x = 1;
	NodeDir[(int)DIR::TOP_RIGHT].y = -1;

	NodeDir[(int)DIR::BOTTOM_LEFT].x = -1;
	NodeDir[(int)DIR::BOTTOM_LEFT].y = 1;

	NodeDir[(int)DIR::BOTTOM_RIGHT].x = 1;
	NodeDir[(int)DIR::BOTTOM_RIGHT].y = 1;*/

	m_lstOpen.clear();
	m_lstClose.clear();
	m_lstPath.clear();
}

CFindPath::~CFindPath()
{
}

list<CTile*> CFindPath::GetPath(CTile* _startTile, CTile* _endTile)
{
	// �ʱ�ȭ
	reset();

	// ���� Ÿ�ϰ� ��Ÿ���� ���ٸ�, path�� ��ȯ
	if ((_startTile == _endTile) || (nullptr == _endTile)) {
		return m_lstPath;
	}

	// ��� Ž�� ����, ���� ��尡 �θ� ��
	CNodeInfo* _parentInfo = new CNodeInfo(_startTile, nullptr, 0, _endTile->Get_Info());
	m_lstClose.push_back(_parentInfo);

	// ��ã�� ����
	CNodeInfo* FindPath = Recursive_FindPath(_parentInfo, _endTile);

	// FindPath�� Parent�� ������ ���� ���� ����.
	while (nullptr != FindPath->Get_Parent()) {
		m_lstPath.insert(m_lstPath.begin(), dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Find_Tile(FindPath->Get_Pos())));
		FindPath = FindPath->Get_Parent();
	}

	// ã�� lstPath�� ��ȯ
	return m_lstPath;
}

bool CFindPath::checkOpenList(CNodeInfo * _nodeInfo)
{
	// lstClose �˻�
	for (auto& iter : m_lstClose) {
		if (iter->Get_Tile() == _nodeInfo->Get_Tile()) {
			return true;
		}
	}

	// lstOpen �˻�
	for (auto& iter : m_lstOpen) {
		if (iter->Get_Tile() == _nodeInfo->Get_Tile()) {

			// ���� ���� �ڸ��� �ִٸ� ���� F�� ���� ���Ͽ� �� ���� F ���� ����
			if (iter->Get_F() > _nodeInfo->Get_F()) {
				m_lstOpen.remove(iter);
				m_lstOpen.push_back(_nodeInfo);
				return true;
			}
		}
	}

	m_lstOpen.push_back(_nodeInfo);
	return true;
}

CNodeInfo* CFindPath::Recursive_FindPath(CNodeInfo * _parentInfo, CTile * _endTile)
{	
	// ���� Ÿ�ϰ� ��Ÿ���� ���ٸ�, path�� ��ȯ
	if ((_parentInfo->Get_Tile() == _endTile) || (nullptr == _endTile)) {
		return _parentInfo;
	}
	
	// �ֺ� Ÿ�ϵ��� �˻�
	for (int i = 0; i < (int)DIR::END; ++i) {
		// �ش� ������ Ÿ���� ã�´�.
		CTile* pTile = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Find_Tile_Dir(_parentInfo->Get_Pos(), (DIR)i));

		// ã�� Ÿ���� �����ϴ��� Ȯ��
		// Ÿ���� �����Ѵٸ�
		if (nullptr != pTile) {
			CNodeInfo* _pChild = new CNodeInfo(pTile, _parentInfo, _parentInfo->Get_G() + TILECX, _endTile->Get_Info());
			checkOpenList(_pChild);
		}
	}

	CNodeInfo* pBest = m_lstOpen.front();
	for (auto& iter : m_lstOpen) {
		// best�� ���� lstOpen�� �ִ� �ͺ��� ũ��, best�� ���� ���������� �ٲ�
		if (pBest->Get_F() >= iter->Get_F())
			pBest = iter;
	}

	m_lstOpen.remove(pBest);
	m_lstClose.push_back(pBest);

	return Recursive_FindPath(pBest, _endTile);
}

bool CFindPath::checkFind_Path(POINT _startPos, POINT _endPos)
{
	CObj* pstartTile = m_pTileMgr->Find_Tile(_startPos);
	CObj* pendTile = m_pTileMgr->Find_Tile(_endPos);

	if (nullptr != pstartTile && (pstartTile == pendTile))
		return true;

	return false;
}

void CFindPath::reset(void)
{
	if (!m_lstOpen.empty())
		m_lstOpen.clear();

	if (!m_lstClose.empty())
		m_lstClose.clear();

	if (!m_lstPath.empty())
		m_lstPath.clear();
}
