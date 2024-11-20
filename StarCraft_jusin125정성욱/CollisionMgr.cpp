#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Initialize(void)
{
}

int CCollisionMgr::Update(void)
{
	return 0;
}

void CCollisionMgr::Late_Update(void)
{
}

void CCollisionMgr::Render(HDC hDC)
{
}

void CCollisionMgr::Release(void)
{
}

void CCollisionMgr::Collision_UnitToUnit(list<CObj*>& Dest, list<CObj*>& Src)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SrcIter : Src)
		{
			if (DestIter == SrcIter)
				continue;

			else if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SrcIter->Get_Rect())))
			{
				;
			//	// 지상대 지상만 유닛을 부딪혔을 경우 이동한다.
			//	if (dynamic_cast<CUnit*>(DestIter)->Get_UnitType() == UNIT_TYPE::Ground &&
			//		dynamic_cast<CUnit*>(SrcIter)->Get_UnitType() == UNIT_TYPE::Ground) {

			//		if (!dynamic_cast<CUnit*>(DestIter)->Get_UnitMove() &&
			//			!dynamic_cast<CUnit*>(SrcIter)->Get_UnitMove()) {
			//			POINT pt1 = dynamic_cast<CUnit*>(DestIter)->Get_Pos();
			//			POINT pt2 = dynamic_cast<CUnit*>(SrcIter)->Get_Pos();

			//			switch (((rand() % 100) * (rand() % 100)) % 4) {
			//			case 0:
			//				dynamic_cast<CUnit*>(DestIter)->Move(pt1.x - 10, pt1.y);
			//				dynamic_cast<CUnit*>(SrcIter)->Move(pt2.x + 10, pt2.y);
			//				break;
			//			case 1:
			//				dynamic_cast<CUnit*>(DestIter)->Move(pt1.x + 10, pt1.y);
			//				dynamic_cast<CUnit*>(SrcIter)->Move(pt2.x - 10, pt2.y);
			//				break;
			//			case 2:
			//				dynamic_cast<CUnit*>(DestIter)->Move(pt1.x, pt1.y - 10);
			//				dynamic_cast<CUnit*>(SrcIter)->Move(pt2.x, pt2.y + 10);
			//				break;
			//			case 3:
			//				dynamic_cast<CUnit*>(DestIter)->Move(pt1.x, pt1.y + 10);
			//				dynamic_cast<CUnit*>(SrcIter)->Move(pt2.x, pt2.y - 10);
			//				break;
			//			}
			//		}
			//	}
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSrc)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius > fDistance;		// 충돌 했다
}


bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSrc, float* _pX, float* _pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	// float		fCX = pDest->Get_Info().fCX / 2.f + pSrc->Get_Info().fCX / 2.f;
	// 위의 식을 아래 식으로 변경했을 뿐
	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pX = fCX - fWidth;
		*_pY = fCY - fHeight;

		return true;
	}
	return false;
}

void CCollisionMgr::Collision_RectEx(list<CObj*>& Dest, list<CObj*>& Src)
{
	RECT	rc{};

	float		fWidth, fHeight;

	for (auto& DestIter : Dest)
	{
		for (auto& SrcIter : Src)
		{
			if (Check_Rect(DestIter, SrcIter, &fWidth, &fHeight))
			{
				// 상하 충돌
				if (fWidth > fHeight)
				{
					// 하 충돌
					if (DestIter->Get_Info().fY < SrcIter->Get_Info().fY)
						SrcIter->Set_PosY(fHeight);
					// 상 충돌
					else
						SrcIter->Set_PosY(-fHeight);
				}
				// 좌우 충돌
				else
				{
					// 우 충돌
					if (DestIter->Get_Info().fX < SrcIter->Get_Info().fX)
						SrcIter->Set_PosX(fWidth);
					// 좌 충돌
					else
						SrcIter->Set_PosX(-fWidth);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*>& Dest, list<CObj*>& Src)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SrcIter : Src)
		{
			if (Check_Sphere(DestIter, SrcIter))
			{
				DestIter->Set_Dead();
				SrcIter->Set_Dead();
			}
		}
	}

}
