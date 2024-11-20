#pragma once

#include "Include.h"
#include "Unit.h"

class CUser : public CSingleton<CUser> {
public:
	CUser();
	~CUser();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

public:
	void		Set_Speed(float _fSpeed) {
		m_fSpeed = _fSpeed;
	}
	float		Get_Speed(void) {
		return m_fSpeed;
	}

	void		Set_BInfo(ButtonInfo _tBInfo) {
		m_tBInfo = _tBInfo;
	}
	ButtonInfo		Get_BInfo(void) const {
		return m_tBInfo;
	}

public:
	void					Set_SelectObj(list<CObj*> _pArrObj);
	const list<CObj*>&		Get_SelectObjArr(void) const { return m_pArrDragedObj; }

public:
	void		PrintText(HDC hDC, int _iX, int _iY, TCHAR* _strText);
	void		PrintText(HDC hDC, int _iX, int _iY, TCHAR* _strText, int _iSize);


private:
	float			m_fSpeed;
	ButtonInfo		m_tBInfo;

	HPEN			MyPen, OldPen;

	list<CObj*>		m_pArrDragedObj;		// 드래그나 클릭을 할 경우 선택된 유닛들의 정보

	LOGFONT			m_lFont;				// 글씨체의 정보
};

