#pragma once

#include "Enum.h"

typedef struct tagInfo
{
	float		fX;			// 중점의 X좌표
	float		fY;			// 중점의 Y좌표
	float		fCX;		// 가로 사이즈
	float		fCY;		// 세로 사이즈
}INFO;

typedef struct tagLinePos
{
	float		fX;
	float		fY;

	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _fX, float _fY) : fX(_fX), fY(_fY) {}
	
}LINEPOS;


typedef struct tagLineInfo
{
	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& tLeft, LINEPOS& tRight)
		: tLeftPos(tLeft), tRightPos(tRight) {}

}LINEINFO;

typedef struct	tagFrame 
{
	int			iFrameStart;		// 시작 프레임
	int			iFrameCurr;			// 현재 프레임
	int			iFrameEnd;			// 최대 프레임
	int			iFrameScene;		// 프레임의 상태(기본, 움직임, 선택... 등등 오브젝트의 특정 상태), 이미지의 세로축을 담당한다.

	DWORD		dwFrameSpeed;	// 1프레임 당 가지고 있는 스피드, 높을 수록 더 느린 모션이 나온다.
	DWORD		dwFrameTime;	// 해당 프레임이 가지고 있는 시간

	int			iWidth;				// 프레임의 가로/세로 크기
	int			iHeight;

	int			iAdditionalWidth;	// 이미지가 매끄럽지 않아 추가적으로 위치를 더하여 출력할때 사용하는 변수
	int			iAdditionalHeight;

	tagFrame() {}
	tagFrame(int _iFrameStart, int _iFrameEnd
		, int _iFrameScene
		, int _iWidth, int _iHeight
		, int _iAdditionalWidth = 0, int _iAdditionalHeight = 0
		, DWORD _dwFrameSpeed = 100, DWORD _dwFrameTime = GetTickCount()
		)

		: iFrameStart(_iFrameStart), iFrameCurr(_iFrameStart), iFrameEnd(_iFrameEnd), iFrameScene(_iFrameScene)
		, iWidth(_iWidth), iHeight(_iHeight)
		, iAdditionalWidth(_iAdditionalWidth), iAdditionalHeight(_iAdditionalHeight)
		, dwFrameSpeed(_dwFrameSpeed), dwFrameTime(_dwFrameTime)
		
	{}

}FRAME;

typedef struct _tagBuildInfo {
	BUILD		m_eBuild;			// 건물의 이름

	RECT		m_tJudgelRect;		// 실제 판정이 되는 RECT
	RECT		m_tRect;			// 건물이 그려지는 대 필요한 정보
	INFO		m_tInfo;

	HDC			m_DC;				// 건물 이미지가 그려져 있는 dc의 정보
	HDC			m_ProduceDC;		// 유닛 생성시 필요한 이미지가 그려져 있는 dc정보
	HDC			m_Create_AfterDC;	// 건물을 다 짓고 난 후 그려지는 이미지 정보

	int			iWidth;				// 이미지의 가로/세로 크기
	int			iHeight;
	int			iRealWidth;			// 이미지안의 건물 실제 가로/세로 크기
	int			iRealHeight;

	int			m_iHP;				// 건물의 체력
	int			m_iMaxHP;
	int			m_iSheild;			// 건물의 쉴드(프로토스 전용)
	int			m_iMaxSheild;			

	int			m_iCostMineral;
	int			m_iCostGas;
	
	DWORD		m_dwBuildTime;		// 건물을 짓는데 걸리는 총 시간
	DWORD		m_dwCurrBuildTime;	// 건물 짓는데 걸리는 현재 시간
}BuildInfo, *PBuildInfo;

typedef struct _tagButtonInfo {
	TERRAIN		Terrain;		// 타일 정보
	UNIT_NAME	eUnit;			// 유닛 정보
	BUILD		eBuild;			// 건물 정보

	RECT		rt;				// 버튼의 위치 정보

	int			iWidth;			// 버튼 이미지의 가로 세로 길이
	int			iHeight;
}ButtonInfo, *PButtonInfo;