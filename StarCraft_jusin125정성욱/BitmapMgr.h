#pragma once

#include "MyBitMap.h"
#include "AnimateButton.h"

class CBitmapMgr : public CSingleton<CBitmapMgr>
{
public:
	CBitmapMgr();
	virtual ~CBitmapMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Image(const TCHAR* pImgKey);
	CMyBitMap*	Find_Bitmap(const TCHAR* pImgKey);

private:
	map<const TCHAR*, CMyBitMap*>		m_mapBit;
};

// DDB : 장치에 의존적인 비트맵 포맷 형식, 이미지의 크기, 색상 등 기본적인 정보와 이미지 데이터로 구성되어 있다. 다양한 해상도의 장치에서 광범위하게 사용되지 못한다.
// 흑백 비트맵은 흑백 장치에서만 컬러 비트맵은 컬러 장치에서만 출력이 가능하다.

// DIB : 장치에 독립적인 비트맵 포맷 형식