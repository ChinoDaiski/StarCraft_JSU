#pragma once

#include "Obj.h"
#include "MyBitMap.h"

class CAnimateButton : public CObj {
public:
	CAnimateButton();
	virtual ~CAnimateButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Lock(bool _bLock) {
		m_bLock = _bLock;
	}
	void Move_AdditionalFrame(void);

public:
	void Set_Bmp_Base(CMyBitMap* _base) {
		m_BitMap_Base = _base;
	}
	void Set_Bmp_Additional(CMyBitMap* _Additional) {
		m_BitMap_Additional = _Additional;
	}

	void Set_moveScene(SCENEID _eSceneID) {
		m_moveScene = _eSceneID;
	}
	SCENEID Get_moveScene(void) {
		return m_moveScene;
	}

	void Set_AdditionalFrameInfo(const FRAME& _tFrame) {
		m_tFrameAdditional = _tFrame;
	}

private:
	CMyBitMap*	m_BitMap_Base;				// �⺻������ ��µǴ� �̹�����

	CMyBitMap*	m_BitMap_Additional;		// �߰��� ��µ� �̹�����
	FRAME		m_tFrameAdditional;			// �߰��� ��µ� �̹����� ����������
									
									
	bool		m_bMouseOn;			// ���콺�� ��ȣ�ۿ��� �ϴ��� �Ǵ��ϴ� ����, Ȱ��ȭ�� ��ٸ� ��ư ���� �߰����� �̹����� ����Ѵ�.
									// false : ��Ȱ��ȭ
									// true : Ȱ��ȭ

	bool		m_bLock;			// �ش� ��鿡�� ����ϴ��� ���ϴ��� �Ǻ��ϴ� ����, true��� ������� �ʴ´�.

	SCENEID		m_moveScene;		// ��ư�� ������ ��� �̵��ϴ� ���� ���� ����

};