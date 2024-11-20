#pragma once

#include "Enum.h"

typedef struct tagInfo
{
	float		fX;			// ������ X��ǥ
	float		fY;			// ������ Y��ǥ
	float		fCX;		// ���� ������
	float		fCY;		// ���� ������
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
	int			iFrameStart;		// ���� ������
	int			iFrameCurr;			// ���� ������
	int			iFrameEnd;			// �ִ� ������
	int			iFrameScene;		// �������� ����(�⺻, ������, ����... ��� ������Ʈ�� Ư�� ����), �̹����� �������� ����Ѵ�.

	DWORD		dwFrameSpeed;	// 1������ �� ������ �ִ� ���ǵ�, ���� ���� �� ���� ����� ���´�.
	DWORD		dwFrameTime;	// �ش� �������� ������ �ִ� �ð�

	int			iWidth;				// �������� ����/���� ũ��
	int			iHeight;

	int			iAdditionalWidth;	// �̹����� �Ų����� �ʾ� �߰������� ��ġ�� ���Ͽ� ����Ҷ� ����ϴ� ����
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
	BUILD		m_eBuild;			// �ǹ��� �̸�

	RECT		m_tJudgelRect;		// ���� ������ �Ǵ� RECT
	RECT		m_tRect;			// �ǹ��� �׷����� �� �ʿ��� ����
	INFO		m_tInfo;

	HDC			m_DC;				// �ǹ� �̹����� �׷��� �ִ� dc�� ����
	HDC			m_ProduceDC;		// ���� ������ �ʿ��� �̹����� �׷��� �ִ� dc����
	HDC			m_Create_AfterDC;	// �ǹ��� �� ���� �� �� �׷����� �̹��� ����

	int			iWidth;				// �̹����� ����/���� ũ��
	int			iHeight;
	int			iRealWidth;			// �̹������� �ǹ� ���� ����/���� ũ��
	int			iRealHeight;

	int			m_iHP;				// �ǹ��� ü��
	int			m_iMaxHP;
	int			m_iSheild;			// �ǹ��� ����(�����佺 ����)
	int			m_iMaxSheild;			

	int			m_iCostMineral;
	int			m_iCostGas;
	
	DWORD		m_dwBuildTime;		// �ǹ��� ���µ� �ɸ��� �� �ð�
	DWORD		m_dwCurrBuildTime;	// �ǹ� ���µ� �ɸ��� ���� �ð�
}BuildInfo, *PBuildInfo;

typedef struct _tagButtonInfo {
	TERRAIN		Terrain;		// Ÿ�� ����
	UNIT_NAME	eUnit;			// ���� ����
	BUILD		eBuild;			// �ǹ� ����

	RECT		rt;				// ��ư�� ��ġ ����

	int			iWidth;			// ��ư �̹����� ���� ���� ����
	int			iHeight;
}ButtonInfo, *PButtonInfo;