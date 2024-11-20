#pragma once

#include "Singleton.h"
#include "Include.h"
#include "Unit.h"


// �ǹ� ����
enum class BUILD_PRODUCE {
	// ���, ���� ���׷��̵�
	Cybernetics_Core,

	// ����ĳ��, ���� ���׷��̵�
	Forge,

	// �ؼ��� - ���κ�
	Nexus,

	// ��Ÿ����Ʈ - ��ī��, Ŀ����, ĳ����, �ƺ���
	Stargate,

	END
};

// �ǹ� �������� �� ���� ����Ʈ
enum class CREATE_AFTER { 
	// �ƹ�Ÿ ���� �ǹ�
	Arbiter_Tribunal,

	// ���� ���� �ǹ�
	Assimilator,

	// �߾� ������
	Citadel_of_Adun,

	// ���, ���� ���׷��̵�
	Cybernetics_Core,

	// ĳ���� ������
	Fleet_Beacon,

	// ����ĳ��, ���� ���׷��̵�
	Forge,

	// ����Ʈ���� - ����, ���, �������÷�, ��ũ���÷�
	Gateway,

	// �ؼ��� - ���κ�
	Nexus,

	// ������
	Observatory,

	// ���� ĳ��
	Photon_Cannon,

	// ���Ϸ� - �α� ��
	Pylon,

	// �κ�ƽ�� - ��Ʋ, ����, ������
	Robotics_Facility,

	// ������ ������
	Robotics_Support_Bay,

	// ���� ���͸�
	Shield_Battery,

	// ��Ÿ����Ʈ - ��ī��, Ŀ����, ĳ����, �ƺ���
	Stargate,

	// ����/��ũ ���÷�, ���÷� ������
	Tempar_Archives,

	END };

// ��Ÿ �̹����� �ʿ��� �ǹ�
enum class BUILD_ITSELF {
	// ���Ϸ� - �α� ��
	Pylon,

	// ���� ĳ��
	Photon_Cannon,

	// ���� ���͸�
	Shield_Battery,
	
	END
};


class CEffectMgr : public CSingleton<CEffectMgr> {
public:
	CEffectMgr();
	~CEffectMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// ���ڷ� ���� ��ġ�� ���ڷ� ���� ������ ���� ����� ����Ѵ�.
	void Show_DeadEffect(UNIT_NAME _eName, int _fX, int _fY);

	// ���ڷ� ���� ��ġ�� ���ڷ� ���� ����Ʈ�� ����Ѵ�.
	void Create_Effect(EFFECT _eEffect, int _fX, int _fY, int _fCX, int _fCY);

	// ���ڷ� ���� ��ġ�� ���ڷ� ���� ����Ʈ�� ����Ѵ�.
	void Show_Create_After_Effect(CREATE_AFTER _eEffect, int _fX, int _fY);

public:
	// Effect ������ ���� �ʱ�ȭ
	void Init_Effect_Frame_Info(EFFECT _eEffect);
	// Create After ������ ���� �ʱ�ȭ
	void Init_Create_After_Frame_Info(CREATE_AFTER _eEffect);

public:
	void Set_FrameInfo(FRAME& _tFrame, int _iEndScene, DWORD _dwSpeed, int _iWidth, int _iHeight);

private:
	HDC		m_EffectDC[(int)EFFECT::END];
	FRAME	m_tEffectFrame[(int)EFFECT::END];

	HDC		m_Create_AfterDC[(int)CREATE_AFTER::END];
	FRAME	m_tCreate_AfterFrame[(int)CREATE_AFTER::END];
};

