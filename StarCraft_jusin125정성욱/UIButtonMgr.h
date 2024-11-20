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

	// �Ŵ����� ������ �ִ� ��ư�� ������ �����ϴ� �Լ� - ��ġ�� ���õ� ��� ó���� �Ѵ�.
	void Set_ButtonInfo(void);

	// ��ư�� ������ �����ϴ� �Լ�
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_ACTION _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_BUILD _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_SKILL _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_UNIT _eAction);
	void Set_UnitButtonInfo(int _iButtonNum, BUTTON_UPGRADE _eAction);

	// Ư�� ��ü�� ������ ���, �װͿ� �ش��ϴ� ��ư��� �Ŵ����� ��ư�� �ٲٴ� �ϼ�
	void ClickObject(UNIT_NAME _eUnitName);		// ������ ������ ���
	void ClickObject(BUILD _eBuild);			// �ǹ��� ������ ���
	void ClickObject(void);						// �ƹ��͵� ������ �ʾ��� ���


	void ClickButton(BUTTON_ACTION _eAction);	// �׼� ��ư�� ������ ���
	void ClickButton(BUTTON_BUILD _eAction);	// �ǹ� ��ư�� ������ ���
	void ClickButton(BUTTON_SKILL _eAction);	// ��ų ��ư�� ������ ���
	void ClickButton(BUTTON_UNIT _eAction);		// ���� ��ư�� ������ ���
	void ClickButton(BUTTON_UPGRADE _eAction);	// ���׷��̵� ��ư�� ������ ���

	// ��ư�� �����ٰ� ���� ��� �Ҹ��� �Լ�
	// ���õǾ��� ��ư�� �������� ���� ������ �ٲ۴�.
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