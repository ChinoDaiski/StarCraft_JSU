
#include "stdafx.h"
#include "BitmapMgr.h"

CBitmapMgr::CBitmapMgr()
{
}

CBitmapMgr::~CBitmapMgr()
{
	Release();
}

void CBitmapMgr::Initialize(void)
{
}

int CBitmapMgr::Update(void)
{
	return 0;
}

void CBitmapMgr::Late_Update(void)
{
}

void CBitmapMgr::Render(HDC hDC)
{
}

void CBitmapMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	//auto	iter = m_mapBit.find()
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CFind_Key(pImgKey));

	if (iter == m_mapBit.end())
	{
		CMyBitMap*	pBmp = new CMyBitMap;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}
}

HDC CBitmapMgr::Find_Image(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CFind_Key(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

CMyBitMap* CBitmapMgr::Find_Bitmap(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CFind_Key(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second;
}

void CBitmapMgr::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}