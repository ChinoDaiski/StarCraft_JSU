#pragma once

#include "Obj.h"

// 추상 팩토리 패턴

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory(){}

public:
	static	CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static	CObj*		Create(float _fX, float _fY, TCHAR* pFrameKey = L"", float _fAngle = 0.f, DIR eDir = DIR::END)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_FrameKey(pFrameKey);
		pObj->Set_Pos(_fX, _fY);

		if (0 != _fAngle)
			pObj->Set_Angle(_fAngle);

		if (DIR::END != eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}
};
