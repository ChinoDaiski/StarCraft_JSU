#pragma once

#include "Include.h"

// �޵�����(������) + �̱���

class CObj;
class CObjMgr : public CSingleton<CObjMgr>
{
public:
	CObjMgr();
	virtual ~CObjMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	list<CObj*>*	Get_ObjList(SCENEID eSceneID, OBJID eID);
	CObj*			Find_Obj_FrameKey(SCENEID eSceneID, OBJID eID, const TCHAR* pFrameKey);

public:
	void			Add_Object(SCENEID eSceneID, OBJID eID, CObj* pObj);
	void			Delete_SceneObj(SCENEID eSceneID);

public:
	void			Set_SceneID(SCENEID eSceneID) {
		m_CurrScene = eSceneID;
	}

public:
	// ���콺�� Ŭ������ ��� �ش� ��ġ�� �ִ� obj�� ������ ��� �ش� obj�� return �ϴ� �Լ�
	list<CObj*>		Get_SelectedObj(void);

public:
	void			Create_Bullet(int _fX, int _fY, CObj* _pTarget);
	void			Create_Bullet(const POINT& _pt, CObj* _pTarget);
	void			Create_Scarab(int _fX, int _fY, CObj* _pTarget);
	void			Create_Scarab(const POINT& _pt, CObj* _pTarget);

public:
	void			DeadAll(SCENEID eSceneID, OBJID eID);

private:
	list<CObj*>		m_ObjList[(int)SCENEID::END][(int)OBJID::END];
	SCENEID			m_CurrScene;
};

