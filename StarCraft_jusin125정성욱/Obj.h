#pragma once

#include "Include.h"


enum class UNIT_TYPE { Ground, Air, END };
enum class UNIT_ATTACK_TYPE { Ground, Air, All, END };

// ������ HP ���¸� ��Ÿ���� ��
typedef struct _tagUnitBar {
	// FrameBar
	INFO				m_tFrameBarInfo;	// �⺻������ �򸮴� �̹����� ����
	RECT				m_tFrameBarRect;
	HDC					m_FrameBarDC;		// ���� ü�°� ���带 ����� �ֱ����� ���� ����ִ� �̹��� DC

											// HpBar
	INFO				m_tHpBarInfo;		// �򸮴� �̹��� ���� �׷����� �̹��� ����
	RECT				m_tHpBarRect;
	HDC					m_HpBarDC;			// ü�¹ٿ� ������ �ִ� �̹��� DC, �Ʒ��ʸ� �׷��ֱ�

											// ShieldBar
	INFO				m_tShieldBarInfo;	// �򸮴� �̹��� ���� �׷����� �̹��� ����
	RECT				m_tShieldBarRect;
	HDC					m_ShieldBarDC;		// ���忡 ������ �ִ� �̹��� DC, ���ʸ� �׷��ֱ�

}UnitStatusBar, *PUnitStatusBar;

typedef struct _tagWireInfo {
	INFO				m_tInfo;			// ���̾� �̹����� �׷��������� �ʿ��� ����
	RECT				m_tRect;

	HDC					m_WireDC;			// ���ô��� ���� �ؿ� �ߴ� ���� �̹��� DC
}WireInfo, *PWireInfo;

typedef struct _tagShadowInfo {
	INFO				m_tInfo;			// ���̾� �̹����� �׷��������� �ʿ��� ����
	RECT				m_tRect;

	HDC					m_WireDC;			// ���ô��� ���� �ؿ� �ߴ� ���� �̹��� DC
}ShadowInfo, *PShadowInfo;

typedef struct _tagPortrait {
	INFO				m_tInfo;			// �ʻ�ȭ �̹����� �׷��������� �ʿ��� ����
	RECT				m_tRect;
	FRAME				m_tFrame;

	HDC					m_PortraitDC;		// ���ô��� ������ �ʻ�ȭ �̹��� DC
}PortraitInfo, *PPortraitInfo;

// ���� �׸��� ���� : �׸��� -> ���̾� -> ���� -> ���¹� ������ �׸���

// ���̾� ������ ���� - ������ �̹����� �׷��� �ִ� DC�� ����
typedef struct _tagWireFrame {
	// BigWireFrame
	HDC					m_BigWireDC;		// ���ô��� ������ ȥ�� ���� ������ ��� ��µǴ� ū �׸� ������ ����ִ� DC
	INFO				m_tBigWireInfo;		// DC�� �׸��� ����	
	RECT				m_tBigWireRect;
	FRAME				m_tBigWireFrame;

	// SmallWireFrame
	HDC					m_SmallWireDC;		// ���ô��� ������ �������� ���� ���� ������ ��� ��µǴ� �����׸� ������ ����ִ� DC
	INFO				m_tSmallWireInfo;		// DC�� �׸��� ����
	RECT				m_tSmallWireRect;
	FRAME				m_tSmallWireFrame;

	// TransWireFrame
	HDC					m_TransWireDC;		// ���ô��� ������ ��Ʋ�� ���� ��� ������ �׸��� ������ ����ִ� DC
	INFO				m_tTransWireInfo;		// DC�� �׸��� ����
	RECT				m_tTransWireRect;
	FRAME				m_tTransWireFrame;
}WireFrameInfo, *PWireFrameInfo;

// ����â ���� - ������ ������ �׷��� �ִ� DC�� ����
typedef struct _tagStatusFrame {
	HDC					m_StatusDC;			// ���ô��� ������ ȥ�� ���� ������ ��� ��µǴ� ���� ������ ����ִ� DC

	INFO				m_tStatusInfo;		// DC�� �׸��� ����
	RECT				m_tStatusRect;
	FRAME				m_tStatusFrame;
}StatusFrameInfo, *PStatusFrameInfo;

typedef struct _tagUnit {
	UNIT_NAME	eUnitName;	// ���� �̸�

	int		iAttack;		// ���ݷ�
	int		iArmor;			// ����

	int		iRange;			// ���� ����
	DWORD	dwOffense;		// ���� �ֱ�

	int		iHP;			// ü��
	int		iMaxHP;

	int		iPopulation;	// �α�

	UNIT_TYPE			eType;		// ���� Ÿ��(������ ����������, ����������)
	UNIT_ATTACK_TYPE	eAttType;	// ���� Ÿ��(������ ���� ���� ������ �������� ���߸����� �Ѵ� �Ǵ���)

	HDC		m_MoveDC;
	HDC		m_AttackDC;

	TCHAR*	m_MoveFrameKey;
	TCHAR*	m_AttackFrameKey;

	FRAME	tMoveFrame;
	FRAME	tAttackFrame;

	// �����佺�� �߰��� ���尡 ����
	int		m_iShield;
	int		m_iMaxShield;

}UNITInfo, *PUNITInfo;





class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	const POINT& Get_Pos(void) const {
		POINT pt;
		pt.x = m_tInfo.fX;
		pt.y = m_tInfo.fY;
		return pt;
	}
	void		Set_Pos(float _fX, float _fY);
	void		Set_Pos(POINT _pt);
	void		Set_Size(float _fX, float _fY);

	void		Set_Dir(DIR eDir);
	void		Set_Angle(float fAngle);
	void		Set_Target(CObj* pTarget);

	void		Set_PosX(float _fX);
	void		Set_PosY(float _fY);

	void			Set_FrameKey(TCHAR* pFrameKey);
	const TCHAR*	Get_FrameKey() const {
		return m_pFrameKey;
	}

	void			Set_Frame(const FRAME& _tFrame) {
		m_tFrame = _tFrame;
	}

	void			Set_BmpSize(int _iX, int _iY);

	void			Set_Dead() { m_bDead = true; } 
	bool			Get_Dead() { return m_bDead; }

	const RECT&		Get_Rect(void)  const { return m_tRect; }
	const INFO&		Get_Info(void)	const { return m_tInfo; }
	void			Set_Info(const INFO& _tInfo) { m_tInfo = _tInfo; }

	// ���ڷ� ���� ������Ʈ���� �Ÿ��� ��ȯ�ϴ� �Լ�
	float Get_Distance(CObj* _pObj) {
		INFO info = _pObj->Get_Info();
		float fDistance =  sqrt(pow(m_tInfo.fX - info.fX, 2.f) + pow(m_tInfo.fY - info.fY, 2.f));

		return fDistance;
	}

public:
	virtual void		Initialize(void) = 0 ;			
	virtual int			Update(void) = 0;
	virtual int			Late_Update(void) = 0;
	virtual void		Render(HDC hDC) = 0;
	virtual void		Release(void) = 0;

public:
	void				Update_Rect(void);
	void				Update_Rect(const INFO& _tInfo, RECT& _tRect);
	void				Move_Frame(void);

public:
	void		Set_Relation(RELATION _eRelation) { m_eRelation = _eRelation; }
	const		RELATION&	Get_Relation(void) const { return m_eRelation; }

	void		Set_Type(OBJ_TYPE _eType) { m_eType = _eType; }
	const		OBJ_TYPE&	Get_Type(void) const { return m_eType; }

	void		Set_UnitType(UNIT_TYPE _eType) { m_tUnitInfo.eType = _eType; }
	const		UNIT_TYPE&	Get_UnitType(void) const { return m_tUnitInfo.eType; }

public:
	void	Select_Unit_byUser(bool _bSelect) {
		m_bSelected = _bSelect;
	}
	bool	Get_bUnitSelect(void) const {
		return m_bSelected;
	}


public:
	void		DrawShad(HDC hDC);
	void		DrawWire(HDC hDC);
	void		DrawStatusBar(HDC hDC);
	void		DrawStatusInfo(HDC hDC);
	void		DrawPortrait(HDC hDC);

public:
	// 0 ~ 9 ������ ���ڸ� ���ڷ� �޾� �ش��ϴ� Wire�� ������ �������� �ϴ� �Լ�
	void	Set_Wire(int _iNum);

	// 0 ~ 8 ������ ���ڸ� ���ڷ� �޾� �ش��ϴ� Status�� ������ �������� �ϴ� �Լ�
	void	Set_StatusFrame(int _iNum);

	// ���ڷ� ������ ������ �޾� �ʻ�ȭ�� ������ �ʱ�ȭ �ϴ� �Լ�
	void	Set_Portrait(UNIT_NAME _eUnitName);
	void	Set_Portrait(BUILD _eUnitName);

public:
	void Update_Wire(void);
	void Update_StatusBar(void);
	void Update_Shadow(void);
	void Update_Portrait(void);

public:
	const BuildInfo&	Get_BuildInfo(void) const { return m_tBuildInfo; }

protected:
	RECT		m_tRect;
	INFO		m_tInfo;
	FRAME		m_tFrame;

	CObj*		m_pTarget;

	float		m_fDistance;
	float		m_fSpeed;
	float		m_fAngle;
	DIR			m_eDir;

	bool		m_bDead;

	TCHAR*		m_pFrameKey;

	bool		m_bClick;

	int			m_iCWidth;
	int			m_iCHeight;

protected:
	// ���� ����
	UNITInfo		m_tUnitInfo;

	RELATION		m_eRelation;		// �ش� ������ �Ʊ�/��/�߸� ���������� ���� ���¸� ������ �ִ� ����
	OBJ_TYPE		m_eType;			// �ش� ������Ʈ�� Ÿ�� - ���� or �ǹ�

	// ���õ� ���� ���� ����
	bool				m_bSelected;		// �������� ���ô��� ��Ȳ���� �ƴ��� Ȯ���ϴ� ����, true�� ���õȰ��̰�, false�� ���õ��� ���� ��Ȳ�̴�. 

	WireFrameInfo		m_tWireFrameInfo;	// ������ ���̾������� �̹����� ��� �ִ� ����ü
	UnitStatusBar		m_tStatusBar;		// ���� ���¹�
	ShadowInfo			m_tShadowInfo;		// ������ �׸��ڿ� ���õ� ����ü

	WireInfo			m_tWireInfo;		// ������ �����ϰ� �Ǹ� ������ ������ ���̾�� ���õ� ����ü
	PortraitInfo		m_tPortrait;		// ������ �����ϰ� �Ǹ� �ؿ� ������ �ʻ�ȭ
	StatusFrameInfo		m_tStatusFrameInfo;	// ������ �����ϰ� �Ǹ� ������ ����â�� ���õ� ����ü

protected:
	BuildInfo			m_tBuildInfo;
};
