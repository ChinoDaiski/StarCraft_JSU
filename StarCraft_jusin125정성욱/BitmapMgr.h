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

// DDB : ��ġ�� �������� ��Ʈ�� ���� ����, �̹����� ũ��, ���� �� �⺻���� ������ �̹��� �����ͷ� �����Ǿ� �ִ�. �پ��� �ػ��� ��ġ���� �������ϰ� ������ ���Ѵ�.
// ��� ��Ʈ���� ��� ��ġ������ �÷� ��Ʈ���� �÷� ��ġ������ ����� �����ϴ�.

// DIB : ��ġ�� �������� ��Ʈ�� ���� ����