#pragma once

#include "Include.h"

class CMyBitMap
{
public:
	CMyBitMap();
	~CMyBitMap();

public:
	HDC			Get_MemDC() { return m_hMemDC; }
	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release(void);
	
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldBmp;

};

