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
	CMyBitMap*	m_BitMap_Base;				// 기본적으로 출력되는 이미지들

	CMyBitMap*	m_BitMap_Additional;		// 추가로 출력될 이미지들
	FRAME		m_tFrameAdditional;			// 추가로 출력될 이미지의 프레임정보
									
									
	bool		m_bMouseOn;			// 마우스와 상호작용을 하는지 판단하는 변수, 활성화가 됬다면 버튼 위에 추가적인 이미지를 출력한다.
									// false : 비활성화
									// true : 활성화

	bool		m_bLock;			// 해당 장면에서 사용하는지 안하는지 판별하는 변수, true라면 사용하지 않는다.

	SCENEID		m_moveScene;		// 버튼을 눌렀을 경우 이동하는 씬에 대한 정보

};