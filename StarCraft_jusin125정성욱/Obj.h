#pragma once

#include "Include.h"


enum class UNIT_TYPE { Ground, Air, END };
enum class UNIT_ATTACK_TYPE { Ground, Air, All, END };

// 유닛의 HP 상태를 나타내는 바
typedef struct _tagUnitBar {
	// FrameBar
	INFO				m_tFrameBarInfo;	// 기본적으로 깔리는 이미지의 정보
	RECT				m_tFrameBarRect;
	HDC					m_FrameBarDC;		// 깍인 체력과 쉴드를 만들어 주기위해 색이 비어있는 이미지 DC

											// HpBar
	INFO				m_tHpBarInfo;		// 깔리는 이미지 위에 그려지는 이미지 정보
	RECT				m_tHpBarRect;
	HDC					m_HpBarDC;			// 체력바에 색상이 있는 이미지 DC, 아래쪽만 그려주기

											// ShieldBar
	INFO				m_tShieldBarInfo;	// 깔리는 이미지 위에 그려지는 이미지 정보
	RECT				m_tShieldBarRect;
	HDC					m_ShieldBarDC;		// 쉴드에 색상이 있는 이미지 DC, 위쪽만 그려주기

}UnitStatusBar, *PUnitStatusBar;

typedef struct _tagWireInfo {
	INFO				m_tInfo;			// 와이어 이미지가 그려지기위해 필요한 정보
	RECT				m_tRect;

	HDC					m_WireDC;			// 선택당한 유닛 밑에 뜨는 원의 이미지 DC
}WireInfo, *PWireInfo;

typedef struct _tagShadowInfo {
	INFO				m_tInfo;			// 와이어 이미지가 그려지기위해 필요한 정보
	RECT				m_tRect;

	HDC					m_WireDC;			// 선택당한 유닛 밑에 뜨는 원의 이미지 DC
}ShadowInfo, *PShadowInfo;

typedef struct _tagPortrait {
	INFO				m_tInfo;			// 초상화 이미지가 그려지기위해 필요한 정보
	RECT				m_tRect;
	FRAME				m_tFrame;

	HDC					m_PortraitDC;		// 선택당한 유닛의 초상화 이미지 DC
}PortraitInfo, *PPortraitInfo;

// 유닛 그리는 순서 : 그림자 -> 와이어 -> 유닛 -> 상태바 순으로 그리기

// 와이어 프레임 정보 - 유닛의 이미지가 그려져 있는 DC의 모음
typedef struct _tagWireFrame {
	// BigWireFrame
	HDC					m_BigWireDC;		// 선택당한 유닛의 혼자 선택 당했을 경우 출력되는 큰 그림 정보가 담겨있는 DC
	INFO				m_tBigWireInfo;		// DC를 그리는 정보	
	RECT				m_tBigWireRect;
	FRAME				m_tBigWireFrame;

	// SmallWireFrame
	HDC					m_SmallWireDC;		// 선택당한 유닛의 여러개가 같이 선택 당했을 경우 출력되는 작은그림 정보가 담겨있는 DC
	INFO				m_tSmallWireInfo;		// DC를 그리는 정보
	RECT				m_tSmallWireRect;
	FRAME				m_tSmallWireFrame;

	// TransWireFrame
	HDC					m_TransWireDC;		// 선택당한 유닛이 셔틀에 탔을 경우 나오는 그림의 정보가 담겨있는 DC
	INFO				m_tTransWireInfo;		// DC를 그리는 정보
	RECT				m_tTransWireRect;
	FRAME				m_tTransWireFrame;
}WireFrameInfo, *PWireFrameInfo;

// 스탯창 정보 - 유닛의 스탯이 그려져 있는 DC의 정보
typedef struct _tagStatusFrame {
	HDC					m_StatusDC;			// 선택당한 유닛의 혼자 선택 당했을 경우 출력되는 스탯 정보가 담겨있는 DC

	INFO				m_tStatusInfo;		// DC를 그리는 정보
	RECT				m_tStatusRect;
	FRAME				m_tStatusFrame;
}StatusFrameInfo, *PStatusFrameInfo;

typedef struct _tagUnit {
	UNIT_NAME	eUnitName;	// 유닛 이름

	int		iAttack;		// 공격력
	int		iArmor;			// 방어력

	int		iRange;			// 공격 범위
	DWORD	dwOffense;		// 공격 주기

	int		iHP;			// 체력
	int		iMaxHP;

	int		iPopulation;	// 인구

	UNIT_TYPE			eType;		// 유닛 타입(유닛이 공중형인지, 지상형인지)
	UNIT_ATTACK_TYPE	eAttType;	// 공격 타입(유닛의 공격 가능 범위가 지상만인지 공중만인지 둘다 되는지)

	HDC		m_MoveDC;
	HDC		m_AttackDC;

	TCHAR*	m_MoveFrameKey;
	TCHAR*	m_AttackFrameKey;

	FRAME	tMoveFrame;
	FRAME	tAttackFrame;

	// 프로토스는 추가로 쉴드가 존재
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

	// 인자로 받은 오브젝트와의 거리를 반환하는 함수
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
	// 0 ~ 9 사이의 숫자를 인자로 받아 해당하는 Wire를 유닛이 가지도록 하는 함수
	void	Set_Wire(int _iNum);

	// 0 ~ 8 사이의 숫자를 인자로 받아 해당하는 Status를 유닛이 가지도록 하는 함수
	void	Set_StatusFrame(int _iNum);

	// 인자로 유닛의 종류를 받아 초상화의 정보를 초기화 하는 함수
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
	// 유닛 정보
	UNITInfo		m_tUnitInfo;

	RELATION		m_eRelation;		// 해당 유닛이 아군/적/중립 유닛인지에 대한 상태를 가지고 있는 변수
	OBJ_TYPE		m_eType;			// 해당 오브젝트의 타입 - 유닛 or 건물

	// 선택된 유닛 관련 정보
	bool				m_bSelected;		// 유저에게 선택당한 상황인지 아닌지 확인하는 변수, true면 선택된것이고, false면 선택되지 않은 상황이다. 

	WireFrameInfo		m_tWireFrameInfo;	// 유닛의 와이어프레임 이미지를 담고 있는 구조체
	UnitStatusBar		m_tStatusBar;		// 유닛 상태바
	ShadowInfo			m_tShadowInfo;		// 유닛의 그림자와 관련된 구조체

	WireInfo			m_tWireInfo;		// 유닛을 선택하게 되면 주위에 나오는 와이어와 관련된 구조체
	PortraitInfo		m_tPortrait;		// 유닛을 선택하게 되면 밑에 나오는 초상화
	StatusFrameInfo		m_tStatusFrameInfo;	// 유닛을 선택하게 되면 나오는 스탯창과 관련된 구조체

protected:
	BuildInfo			m_tBuildInfo;
};
