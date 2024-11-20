#pragma once

#include "Singleton.h"
#include "Include.h"
#include "Unit.h"

#include "UnitButton.h"
#include "ActionButton.h"
#include "BuildButton.h"
#include "UpgradeButton.h"
#include "SkillButton.h"
#include "TempButton.h"

class CUIButtonMgr : public CSingleton<CUIButtonMgr> {
public:
	CUIButtonMgr();
	~CUIButtonMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Clear_ButtonInfo(void);

	// 매니저가 가지고 있는 버튼의 정보를 조정하는 함수 - 위치와 관련된 모든 처리를 한다.
	void Set_ButtonInfo(void);

	// 버튼의 정보를 세팅하는 함수
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_ACTION _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_BUILD _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_SKILL _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_UNIT _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_UPGRADE _eAction);

	// 특정 물체를 눌렀을 경우, 그것에 해당하는 버튼들로 매니저의 버튼을 바꾸는 하수
	void ClickObject(UNIT_NAME _eUnitName);		// 유닛을 눌렀을 경우
	void ClickObject(BUILD _eBuild);			// 건물을 눌렀을 경우
	void ClickObject(void);						// 아무것도 누르지 않았을 경우


	void ClickButton(BUTTON_ACTION _eAction);	// 액션 버튼을 눌렀을 경우
	void ClickButton(BUTTON_BUILD _eAction);	// 건물 버튼을 눌렀을 경우
	void ClickButton(BUTTON_SKILL _eAction);	// 스킬 버튼을 눌렀을 경우
	void ClickButton(BUTTON_UNIT _eAction);		// 유닛 버튼을 눌렀을 경우
	void ClickButton(BUTTON_UPGRADE _eAction);	// 업그레이드 버튼을 눌렀을 경우

	// 버튼을 눌렀다가 놨을 경우 불리는 함수
	// 선택되었던 버튼을 선택하지 않은 것으로 바꾼다.
	void ClickUp(void);

private:
	stack<CObj*>	m_stButton[9];

	CObj*		m_ActionButton[(int)BUTTON_ACTION::END];
	CObj*		m_BuildButton[(int)BUTTON_BUILD::END];
	CObj*		m_SkillButton[(int)BUTTON_SKILL::END];
	CObj*		m_UnitButton[(int)BUTTON_UNIT::END];
	CObj*		m_UpgradeButton[(int)BUTTON_UPGRADE::END];
	CObj*		m_TempButton;
};