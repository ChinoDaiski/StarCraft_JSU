#include "stdafx.h"
#include "AnimateButton.h"
#include "SceneMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "BitmapMgr.h"


CAnimateButton::CAnimateButton()
{
}


CAnimateButton::~CAnimateButton()
{
	Release(); 
}

void CAnimateButton::Initialize(void)
{
	m_moveScene = SCENEID::END;
	m_bLock = false;
}

int CAnimateButton::Update(void)
{
	// Ȱ��ȭ�� ���� �ʾҴٸ�, �ѱ��.
	if (m_bLock)
		return OBJ_NOEVENT;

	Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

int CAnimateButton::Late_Update(void)
{
	// Ȱ��ȭ�� ���� �ʾҴٸ�, �ѱ��.
	if (m_bLock)
		return OBJ_NOEVENT;

}

void CAnimateButton::Render(HDC hDC)
{
	// Ȱ��ȭ�� ���� �ʾҴٸ�, �ѱ��.
	if (m_bLock)
		return;

	HDC	hMemDC = m_BitMap_Base->Get_MemDC();

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,

		m_tRect.right - m_tRect.left,
		m_tRect.bottom - m_tRect.top,

		hMemDC,

		m_tFrame.iWidth * m_tFrame.iFrameCurr,
		m_tFrame.iHeight * (int)m_tFrame.iFrameScene,

		m_tFrame.iWidth,
		m_tFrame.iHeight,

		RGB(255, 255, 255));


	// ���콺�� ��ư�� �浹���� ���
	POINT pt = CMouse::Get_Instance()->Get_Pos();

	if (PtInRect(&m_tRect, pt)) {

		hMemDC = m_BitMap_Additional->Get_MemDC();

		GdiTransparentBlt(hDC,
			m_tRect.left + m_tFrameAdditional.iAdditionalWidth,
			m_tRect.top + m_tFrameAdditional.iAdditionalHeight,

			m_tRect.right - m_tRect.left,
			m_tRect.bottom - m_tRect.top,

			hMemDC,

			m_tFrameAdditional.iWidth * m_tFrameAdditional.iFrameCurr,
			m_tFrameAdditional.iHeight * (int)m_tFrameAdditional.iFrameScene,

			m_tFrameAdditional.iWidth,
			m_tFrameAdditional.iHeight,

			RGB(255, 255, 255));

		Move_AdditionalFrame();
	}

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//GdiTransparentBlt(hDC,				// ������� dc, ���������� �׸��� �׸� dc
	//	m_tRect.left,					// ���� ���� ��ġ x��ǥ
	//	m_tRect.top,					// ���� ���� ��ġ y��ǥ
	//	(int)m_tInfo.fCX,				// ���� ���� �̹����� ���� ������
	//	(int)m_tInfo.fCY,				// ���� ���� �̹����� ���� ������
	//	hMemDC,							// ���� ��Ʈ�� �̹����� ������ �ִ� dc
	//	(int)m_tInfo.fCX * m_bCollision,	// ��Ʈ���� ����� ���� ��ǥ
	//	0,
	//	(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ������
	//	(int)m_tInfo.fCY,
	//	RGB(255, 255, 255));			// �����ϰ����ϴ� ����
}

void CAnimateButton::Release(void)
{

}

void CAnimateButton::Move_AdditionalFrame(void)
{
	if (m_tFrameAdditional.dwFrameTime + m_tFrameAdditional.dwFrameSpeed < GetTickCount())
	{
		++m_tFrameAdditional.iFrameCurr;
		m_tFrameAdditional.dwFrameTime = GetTickCount();

		if (m_tFrameAdditional.iFrameCurr >= m_tFrameAdditional.iFrameEnd)
			m_tFrameAdditional.iFrameCurr = 0;
	}
}
