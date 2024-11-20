#include "stdafx.h"
#include "MyBitMap.h"


CMyBitMap::CMyBitMap()
{
}


CMyBitMap::~CMyBitMap()
{
	Release();
}

void CMyBitMap::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,			// 프로그램 인스턴스 핸들을 전달
		pFilePath,		// 파일의 경로
		IMAGE_BITMAP,	// 어떤 타입, 비트맵, 커서인지, 아이콘인지
		0,				// 가로, 세로 사이즈
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	int iNum = GetLastError();

	// LR_LOADFROMFILE : 파일에서 이미지를 불러오겠다는 뜻
	// LR_CREATEDIBSECTION : 읽어온 파일을 DIB형태로 변환하겠다는 뜻

	/*- LoadImage는 비트맵의 현재 정보를 가지고 있는 상태지 그리는 상태는 아니다.
	- 비트맵을 그리기 위해서 m_hMemDC정보를 준비했으나 '현재 선택된 GDI오브젝트'는 기본값이 상황이다.
	- 준비한 DC의 GDI오브젝트에 불러온 비트맵을 선택하기 위해 SelectObject 사용한다.

	- SelectObject는 GDI 오브젝트를 선택하기 전 오브젝트를 반환*/

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

}

void CMyBitMap::Release(void)
{
	// LoadImage 읽어들인 정보를 삭제하는 함수

	// 현재 dc에 선택된 GDI 오브젝트는 해제할 수가 없다.
	// 해제하기 위해 기존에 사용하던 GDI오브젝트로 교체를 하고 그 다음 삭제를 진행하는 코드이다.

	SelectObject(m_hMemDC, m_hOldBmp);

	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
