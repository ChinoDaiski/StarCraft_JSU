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
	// 초기화
	reset();

	// 시작 타일과 끝타일이 같다면, path를 반환
	if ((_startTile == _endTile) || (nullptr == _endTile)) {
		return m_lstPath;
	}

	// 노드 탐색 시작, 현재 노드가 부모가 됨
	CNodeInfo* _parentInfo = new CNodeInfo(_startTile, nullptr, 0, _endTile->Get_Info());
	m_lstClose.push_back(_parentInfo);

	// 길찾기 시작
	CNodeInfo* FindPath = Recursive_FindPath(_parentInfo, _endTile);

	// FindPath의 Parent를 역으로 돌려 길을 만듦.
	while (nullptr != FindPath->Get_Parent()) {
		m_lstPath.insert(m_lstPath.begin(), dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Find_Tile(FindPath->Get_Pos())));
		FindPath = FindPath->Get_Parent();
	}

	// 찾은 lstPath를 반환
	return m_lstPath;
}

bool CFindPath::checkOpenList(CNodeInfo * _nodeInfo)
{
	// lstClose 검사
	for (auto& iter : m_lstClose) {
		if (iter->Get_Tile() == _nodeInfo->Get_Tile()) {
			return true;
		}
	}

	// lstOpen 검사
	for (auto& iter : m_lstOpen) {
		if (iter->Get_Tile() == _nodeInfo->Get_Tile()) {

			// 만약 같은 자리에 있다면 서로 F의 값을 비교하여 더 작은 F 값을 넣음
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
	// 시작 타일과 끝타일이 같다면, path를 반환
	if ((_parentInfo->Get_Tile() == _endTile) || (nullptr == _endTile)) {
		return _parentInfo;
	}
	
	// 주변 타일들을 검사
	for (int i = 0; i < (int)DIR::END; ++i) {
		// 해당 방향의 타일을 찾는다.
		CTile* pTile = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Find_Tile_Dir(_parentInfo->Get_Pos(), (DIR)i));

		// 찾은 타일이 존재하는지 확인
		// 타일이 존재한다면
		if (nullptr != pTile) {
			CNodeInfo* _pChild = new CNodeInfo(pTile, _parentInfo, _parentInfo->Get_G() + TILECX, _endTile->Get_Info());
			checkOpenList(_pChild);
		}
	}

	CNodeInfo* pBest = m_lstOpen.front();
	for (auto& iter : m_lstOpen) {
		// best의 값이 lstOpen에 있는 것보다 크면, best는 제일 작은놈으로 바뀜
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
