#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "Bullet.h"
#include "Scarab.h"
#include "UnitMgr.h"
#include "SoundMgr.h"

CObjMgr::CObjMgr()
	:m_CurrScene(SCENEID::LOGO)
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

std::list<CObj*>* CObjMgr::Get_ObjList(SCENEID eSceneID, OBJID eID)
{
	return &m_ObjList[(int)eSceneID][(int)eID];
}

CObj* CObjMgr::Find_Obj_FrameKey(SCENEID eSceneID, OBJID eoObjID, const TCHAR * pFrameKey)
{
	for (auto& obj : m_ObjList[(int)eSceneID][(int)eoObjID]) {
		if (lstrcmp(pFrameKey, obj->Get_FrameKey()) == 0) {
			return obj;
		}
	}

	return nullptr;
}

void CObjMgr::Add_Object(SCENEID eSceneID, OBJID eID, CObj * pObj)
{
	if (OBJID::END <= eID || nullptr == pObj)
		return;

	m_ObjList[(int)eSceneID][(int)eID].push_back(pObj);
}

void CObjMgr::Initialize(void)
{
	for (int i = 0; i < (int)SCENEID::END; ++i) {

		for (int j = 0; j < (int)OBJID::END; ++j) {
			for (auto& iter : m_ObjList[i][j]) {
				iter->Initialize();
			}
		}
	}
}

int CObjMgr::Update(void)
{
	int iEvent = 0;

	for (int i = 0; i < (int)OBJID::END; ++i)
	{
		auto& iter = m_ObjList[(int)m_CurrScene][i].begin();

		for (; iter != m_ObjList[(int)m_CurrScene][i].end(); )
		{
			iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[(int)m_CurrScene][i].erase(iter);
			}
			else
				++iter;
		}
	}

	CCollisionMgr::Get_Instance()->Collision_UnitToUnit(m_ObjList[(int)m_CurrScene][(int)OBJID::UNIT], m_ObjList[(int)m_CurrScene][(int)OBJID::UNIT]);

	return iEvent;
}

void CObjMgr::Late_Update(void)
{
	int iEvent = 0;

	for (int i = 0; i < (int)OBJID::END; ++i)
	{
		for (auto& iter : m_ObjList[(int)m_CurrScene][i])
		{
			iEvent = iter->Late_Update();

			if (OBJ_CHANGE == iEvent)
				return;
		}
	}

	//CCollisionMgr::Collision_Sphere(m_ObjList[BULLET], m_ObjList[MONSTER]);
	//CCollisionMgr::Collision_Rect(m_ObjList[BULLET], m_ObjList[MONSTER]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[MONSTER], m_ObjList[PLAYER]);
}

void CObjMgr::Render(HDC hDC)
{
	RECT rt;
	rt.left = CScrollMgr::Get_Instance()->Get_ScrollX();
	rt.right = rt.left + WINCX;
	rt.top = CScrollMgr::Get_Instance()->Get_ScrollY();
	rt.bottom = rt.top + WINCY;


	for (int i = 0; i < (int)OBJID::END; ++i)
	{
		for (auto& iter : m_ObjList[(int)m_CurrScene][i]) {
			if (PtInRect(&rt, iter->Get_Pos()))
				iter->Render(hDC);
		}
	}


}

void CObjMgr::Release(void)
{
	for (int i = 0; i < (int)SCENEID::END; ++i) {

		for (int j = 0; j < (int)OBJID::END; ++j) {
			for_each(m_ObjList[i][j].begin(), m_ObjList[i][j].end(), Safe_Delete<CObj*>);
			m_ObjList[i][j].clear();
		}

	}
}

void CObjMgr::Delete_SceneObj(SCENEID eSceneID)
{
	for (int i = 0; i < (int)OBJID::END; ++i) {
		for (auto& iter : m_ObjList[(int)eSceneID][i]) {
			Safe_Delete(iter);
		}

		m_ObjList[(int)eSceneID][i].clear();
	}
}

list<CObj*> CObjMgr::Get_SelectedObj(void)
{
	list<CObj*> m_lstObj;

	// 마우스가 Drag 되고 있다면 
	if (CMouse::Get_Instance()->Get_Status() == MOUSE_STATUS::DRAG) {
		// 다중 선택 : 마우스와 DragRect와 유닛의 중점을 비교하여 걸리는 모든 유닛을 선택한다. 단, 건물은 제외

		POINT pt{};

		for (auto& iter : m_ObjList[(int)m_CurrScene][(int)OBJID::UNIT]) {
			pt.x = iter->Get_Info().fX;
			pt.y = iter->Get_Info().fY;

			RECT rt = CMouse::Get_Instance()->Get_DragRect();
			rt.left += CScrollMgr::Get_Instance()->Get_ScrollX();
			rt.right += CScrollMgr::Get_Instance()->Get_ScrollX();
			rt.top += CScrollMgr::Get_Instance()->Get_ScrollY();
			rt.bottom += CScrollMgr::Get_Instance()->Get_ScrollY();

			if (PtInRect(&rt, pt)) {
				m_lstObj.push_back(iter);
			}
		}
	}

	// 마우스가 Drag 상태가 아니라면
	else {
		// 단일 선택 : 마우스의 중점과 유닛의 Rect를 비교하여 걸리는 유닛을 선택한다. 건물도 포함
		POINT pt = CMouse::Get_Instance()->Get_Pos();
		pt.x += CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y += CScrollMgr::Get_Instance()->Get_ScrollY();

		for (int i = (int)OBJID::BUILD; i <= (int)OBJID::UNIT; ++i) {
			for (auto& iter : m_ObjList[(int)m_CurrScene][i]) {
				if (PtInRect(&iter->Get_Rect(), pt)) {
					m_lstObj.push_back(iter);
				}
			}
		}
	}

	return m_lstObj;
}

void CObjMgr::Create_Bullet(int _fX, int _fY, CObj * _pTarget)
{
	//CSoundMgr::Get_Instance()->StopSound(CHANNELID::EFFECT);

	CObj* pObj = new CBullet();
	pObj->Set_Pos(_fX, _fY);
	pObj->Set_Size(30, 30);

	pObj->Initialize();
	pObj->Set_Target(_pTarget);
	pObj->Update();

	CObjMgr::Get_Instance()->Add_Object(SCENEID::SINGLEPLAY, OBJID::BULLET, pObj);
}

void CObjMgr::Create_Bullet(const POINT & _pt, CObj * _pTarget)
{
	Create_Bullet(_pt.x, _pt.y, _pTarget);
}

void CObjMgr::Create_Scarab(int _fX, int _fY, CObj * _pTarget)
{
	CObj* pObj = new CScarab();
	pObj->Set_Pos(_fX, _fY);
	pObj->Set_Size(30, 30);

	pObj->Initialize();
	pObj->Set_Target(_pTarget);
	pObj->Update();

	CObjMgr::Get_Instance()->Add_Object(SCENEID::SINGLEPLAY, OBJID::BULLET, pObj);
}

void CObjMgr::Create_Scarab(const POINT & _pt, CObj * _pTarget)
{
	Create_Scarab(_pt.x, _pt.y, _pTarget);
}

void CObjMgr::DeadAll(SCENEID eSceneID, OBJID eID)
{
	for (auto& Unit : m_ObjList[(int)eSceneID][(int)eID])
		Unit->Set_Dead();
}
