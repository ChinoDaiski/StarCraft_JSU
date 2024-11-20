#pragma once

#include "Singleton.h"
#include "Include.h"
#include "Unit.h"

class CCollisionMgr : public CSingleton<CCollisionMgr>
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	bool	Check_Sphere(CObj* pDest, CObj* pSrc);
	bool	Check_Rect(CObj* pDest, CObj* pSrc, float* _pX, float* _pY);

public:
	void	Collision_UnitToUnit(list<CObj*>& Dest, list<CObj*>& Src);
	void	Collision_Sphere(list<CObj*>& Dest, list<CObj*>& Src);
	void	Collision_RectEx(list<CObj*>& Dest, list<CObj*>& Src);
};



