#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "User.h"
#include "MiniMap.h"


CTile::CTile(TERRAIN _eTerrainInfo)
	: m_eTerrainInfo(_eTerrainInfo)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Set_TerrainInfo(TERRAIN _eTerrainInfo)
{
	m_eTerrainInfo = _eTerrainInfo;

	switch (m_eTerrainInfo)
	{
	case TERRAIN::DIRT:
		// 지상 유닛이 움직일 수 있는 타일
		m_pFrameKey = L"Tile_Dirt";
		m_bEnable = true;
		break;

	case TERRAIN::WATER:
		// 지상 유닛이 움직일 수 없는 타일
		m_pFrameKey = L"Tile_Water";
		m_bEnable = false;
		break;

	case TERRAIN::CREEP:
		// 지상 유닛이 움직일 수 있는 타일
		m_pFrameKey = L"Tile_Creep";
		m_bEnable = true;
		break;

	case TERRAIN::NONE_MOVE:
		m_pFrameKey = L"None";
		m_bEnable = true;
		break;

	case TERRAIN::NONE_NOMOVE:
		m_pFrameKey = L"None";
		m_bEnable = false;
		break;

	case TERRAIN::END:
		m_pFrameKey = L"None";
		m_bEnable = true;
		break;

	default:
		m_pFrameKey = L"None";
		m_bEnable = true;
		break;
	}

	m_bitmapDC = CBitmapMgr::Get_Instance()->Find_Image(m_pFrameKey);
}

void CTile::Initialize(void)
{
	m_bEnable = true;	// 처음에는 이동이 가능한 타일로 설정

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	Set_TerrainInfo(m_eTerrainInfo);
	m_bShowEnable = false;

	Update_Rect();
}

int CTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CTile::Late_Update(void)
{
	return 0;
}

void CTile::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if ((m_tInfo.fX < iScrollX + WINCX + TILECX) && (m_tInfo.fY < iScrollY + WINCY + TILECY)) {

		BitBlt(hDC,							// 복사받을 dc, 최종적으로 그림을 그릴 dc
			int(m_tRect.left - iScrollX),	// 복사 받을 위치 x좌표
			int(m_tRect.top - iScrollY),	// 복사 받을 위치 y좌표
			(int)m_tInfo.fCX,				// 복사 받을 이미지의 가로 사이즈
			(int)m_tInfo.fCY,				// 복사 받을 이미지의 세로 사이즈
			m_bitmapDC,						// 현재 비트맵 이미지를 가지고 있는 dc
			0,								// 비트맵을 출력할 시작 좌표
			0,
			SRCCOPY);

		// 타일에 라인을 긋는다.
		//MoveToEx(hDC, m_tRect.left - iScrollX, m_tRect.top - iScrollY, nullptr);
		//LineTo(hDC, m_tRect.left - iScrollX, m_tRect.bottom - iScrollY);
		//LineTo(hDC, m_tRect.right - iScrollX, m_tRect.bottom - iScrollY);
		//LineTo(hDC, m_tRect.right - iScrollX, m_tRect.top - iScrollY);
		//LineTo(hDC, m_tRect.left - iScrollX, m_tRect.top - iScrollY);

		if (m_bShowEnable) {
			LPCWSTR str;
			
			if (m_bEnable)
				str = L"1";
			else
				str = L"2";

			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(255, 255, 255));
			TextOut(hDC, m_tRect.left - iScrollX, m_tRect.top - iScrollY, str, lstrlen(str));
		}
	}

}

void CTile::Release(void)
{

}
