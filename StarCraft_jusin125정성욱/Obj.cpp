
#include "stdafx.h"
#include "Obj.h"
#include "User.h"
#include "ScrollMgr.h"

CObj::CObj()
	: m_fSpeed(0.f), m_eDir(DIR(0)), m_bDead(false)
	, m_fDistance(100.f), m_fAngle(0.f), m_pFrameKey(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::Update_Rect(const INFO& _tInfo, RECT& _tRect)
{
	_tRect.left = LONG(_tInfo.fX - (_tInfo.fCX / 2.f));
	_tRect.top = LONG(_tInfo.fY - (_tInfo.fCY / 2.f));
	_tRect.right = LONG(_tInfo.fX + (_tInfo.fCX / 2.f));
	_tRect.bottom = LONG(_tInfo.fY + (_tInfo.fCY / 2.f));
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameCurr;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameCurr >= m_tFrame.iFrameEnd)
			m_tFrame.iFrameCurr = m_tFrame.iFrameStart;
	}
}

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::Set_Pos(POINT _pt)
{
	m_tInfo.fX = _pt.x;
	m_tInfo.fY = _pt.y;
}

void CObj::Set_Size(float _fX, float _fY)
{
	m_tInfo.fCX = _fX;
	m_tInfo.fCY = _fY;
}

void CObj::Set_Dir(DIR eDir)
{
	m_eDir = eDir;
}

void CObj::Set_Angle(float fAngle)
{
	m_fAngle = fAngle;
}

void CObj::Set_Target(CObj* pTarget)
{
	m_pTarget = pTarget;
}

void CObj::Set_PosX(float _fX)
{
	m_tInfo.fX += _fX;
}

void CObj::Set_PosY(float _fY)
{
	m_tInfo.fY += _fY;
}

void CObj::Set_FrameKey(TCHAR* pFrameKey)
{
	m_pFrameKey = pFrameKey;
}

void CObj::Set_BmpSize(int _iX, int _iY)
{
	m_iCWidth = _iX;
	m_iCHeight = _iY;
}


void CObj::DrawShad(HDC hDC)
{
}

void CObj::DrawWire(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TransparentBlt(hDC,
		int(m_tWireInfo.m_tRect.left - iScrollX),
		int(m_tWireInfo.m_tRect.top - iScrollY),
		(int)m_tWireInfo.m_tInfo.fCX,
		(int)m_tWireInfo.m_tInfo.fCY + 10,
		m_tWireInfo.m_WireDC,
		0, 0,
		m_tWireInfo.m_tInfo.fCX,
		m_tWireInfo.m_tInfo.fCY,
		RGB(255, 255, 255));
}


void CObj::DrawStatusBar(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iGap = 0;


	if (m_tUnitInfo.eUnitName == UNIT_NAME::Archon ||
		m_tUnitInfo.eUnitName == UNIT_NAME::Arbiter ||
		m_tUnitInfo.eUnitName == UNIT_NAME::Reaver ||
		m_tUnitInfo.eUnitName == UNIT_NAME::Scout)
		iGap = 20;
	else if (m_tUnitInfo.eUnitName == UNIT_NAME::Corsair)
		iGap = 15;
	else if (m_tUnitInfo.eUnitName == UNIT_NAME::Carrier)
		iGap = 20;

	// FrameBar
	//===========================================================================================================================
	TransparentBlt(hDC,
		int(m_tStatusBar.m_tFrameBarRect.left - iScrollX),
		int(m_tStatusBar.m_tFrameBarRect.top - iScrollY - iGap),
		(int)m_tStatusBar.m_tFrameBarInfo.fCX,
		(int)m_tStatusBar.m_tFrameBarInfo.fCY,
		m_tStatusBar.m_FrameBarDC,
		0, 0,
		m_tStatusBar.m_tFrameBarInfo.fCX,
		m_tStatusBar.m_tFrameBarInfo.fCY,
		RGB(255, 255, 255));
	//===========================================================================================================================


	// HpBar
	//===========================================================================================================================
	TransparentBlt(hDC,
		int(m_tStatusBar.m_tHpBarRect.left - iScrollX),
		int(m_tStatusBar.m_tHpBarRect.top - iScrollY - iGap) + 4,
		(int)m_tStatusBar.m_tHpBarInfo.fCX,
		(int)m_tStatusBar.m_tHpBarInfo.fCY - 4,
		m_tStatusBar.m_HpBarDC,
		0, 4,
		m_tStatusBar.m_tHpBarInfo.fCX,
		m_tStatusBar.m_tHpBarInfo.fCY - 4,
		RGB(255, 255, 255));
	//===========================================================================================================================


	// ShieldBar
	//===========================================================================================================================
	TransparentBlt(hDC,
		int(m_tStatusBar.m_tShieldBarRect.left - iScrollX),
		int(m_tStatusBar.m_tShieldBarRect.top - iScrollY - iGap),
		(int)m_tStatusBar.m_tShieldBarInfo.fCX,
		4,
		m_tStatusBar.m_ShieldBarDC,
		0, 0,
		m_tStatusBar.m_tShieldBarInfo.fCX,
		4,
		RGB(255, 255, 255));
	//===========================================================================================================================

}

void CObj::DrawStatusInfo(HDC hDC)
{
	// UnitBigFrame
	//===========================================================================================================================
	TransparentBlt(hDC,
		int(m_tWireFrameInfo.m_tBigWireRect.left),
		int(m_tWireFrameInfo.m_tBigWireRect.top),
		(int)m_tWireFrameInfo.m_tBigWireInfo.fCX,
		(int)m_tWireFrameInfo.m_tBigWireInfo.fCY,
		m_tWireFrameInfo.m_BigWireDC,
		0, 0,
		m_tWireFrameInfo.m_tBigWireFrame.iWidth,
		m_tWireFrameInfo.m_tBigWireFrame.iHeight,
		RGB(0, 0, 0));
	//===========================================================================================================================


	// Unit Hp/Shield Status
	//===========================================================================================================================
	TCHAR strUnitStatusHp[16];
	TCHAR strUnitStatusShield[16];

	if (m_tBuildInfo.m_eBuild == BUILD::END) {
		swprintf_s(strUnitStatusHp, L"%d/%d",
			m_tUnitInfo.m_iShield, m_tUnitInfo.m_iMaxShield);

		swprintf_s(strUnitStatusShield, L"%d/%d",
			m_tUnitInfo.iHP, m_tUnitInfo.iMaxHP);
	}
	else {
		swprintf_s(strUnitStatusHp, L"%d/%d",
			m_tBuildInfo.m_iSheild, m_tBuildInfo.m_iMaxSheild);

		swprintf_s(strUnitStatusShield, L"%d/%d",
			m_tBuildInfo.m_iHP, m_tBuildInfo.m_iMaxHP);
	}

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(135, 206, 250));
	CUser::Get_Instance()->PrintText(hDC,
		m_tWireFrameInfo.m_tBigWireRect.left + 5, m_tWireFrameInfo.m_tBigWireRect.bottom + 5, strUnitStatusHp);

	SetTextColor(hDC, RGB(173, 255, 047));
	CUser::Get_Instance()->PrintText(hDC,
		m_tWireFrameInfo.m_tBigWireRect.left + 45, m_tWireFrameInfo.m_tBigWireRect.bottom + 5, strUnitStatusShield);
	//===========================================================================================================================


	// Unit Name/Upgrade Status
	//===========================================================================================================================
	StretchBlt(hDC,
		int(m_tStatusFrameInfo.m_tStatusRect.left),
		int(m_tStatusFrameInfo.m_tStatusRect.top),
		(int)m_tStatusFrameInfo.m_tStatusInfo.fCX,
		(int)m_tStatusFrameInfo.m_tStatusInfo.fCY,
		m_tStatusFrameInfo.m_StatusDC,
		0, 0,
		m_tStatusFrameInfo.m_tStatusFrame.iWidth,
		m_tStatusFrameInfo.m_tStatusFrame.iHeight,
		SRCCOPY);
	//===========================================================================================================================


}

void CObj::DrawPortrait(HDC hDC)
{
	StretchBlt(hDC,
		int(m_tPortrait.m_tRect.left),
		int(m_tPortrait.m_tRect.top),
		(int)m_tPortrait.m_tInfo.fCX,
		(int)m_tPortrait.m_tInfo.fCY,
		m_tPortrait.m_PortraitDC,
		m_tPortrait.m_tFrame.iWidth * m_tPortrait.m_tFrame.iFrameCurr, 0,
		m_tPortrait.m_tFrame.iWidth,
		m_tPortrait.m_tFrame.iHeight,
		SRCCOPY);
}

void CObj::Set_Wire(int _iNum)
{
	// 0 ~ 9 사이의 값을 가져오지 않으면 아무것도 하지 않는다.
	if (!(0 <= _iNum && _iNum <= 9))
		return;

	// wire HDC 설정
	TCHAR szBuff[32] = L"";
	swprintf_s(szBuff, L"Unit_Wire%02d", _iNum);
	m_tWireInfo.m_WireDC = CBitmapMgr::Get_Instance()->Find_Image(szBuff);


	// 설정한 HDC의 이미지 정보 설정
	switch (_iNum)
	{
	case 0:
		m_tWireInfo.m_tInfo.fCX = 32;
		m_tWireInfo.m_tInfo.fCY = 32;
		break;
	case 1:
		m_tWireInfo.m_tInfo.fCX = 40;
		m_tWireInfo.m_tInfo.fCY = 40;
		break;
	case 2:
		m_tWireInfo.m_tInfo.fCX = 64;
		m_tWireInfo.m_tInfo.fCY = 64;
		break;
	case 3:
		m_tWireInfo.m_tInfo.fCX = 64;
		m_tWireInfo.m_tInfo.fCY = 64;
		break;
	case 4:
		m_tWireInfo.m_tInfo.fCX = 80;
		m_tWireInfo.m_tInfo.fCY = 80;
		break;
	case 5:
		m_tWireInfo.m_tInfo.fCX = 96;
		m_tWireInfo.m_tInfo.fCY = 96;
		break;
	case 6:
		m_tWireInfo.m_tInfo.fCX = 128;
		m_tWireInfo.m_tInfo.fCY = 128;
		break;
	case 7:
		m_tWireInfo.m_tInfo.fCX = 128;
		m_tWireInfo.m_tInfo.fCY = 128;
		break;
	case 8:
		m_tWireInfo.m_tInfo.fCX = 148;
		m_tWireInfo.m_tInfo.fCY = 148;
		break;
	case 9:
		m_tWireInfo.m_tInfo.fCX = 224;
		m_tWireInfo.m_tInfo.fCY = 224;
		break;
	}

}

void CObj::Set_StatusFrame(int _iNum)
{
	// 0 ~ 8 사이의 값을 가져오지 않으면 아무것도 하지 않는다.
	if (!(0 <= _iNum && _iNum <= 8))
		return;

	// FrameBar HDC 설정
	TCHAR szBuff[32] = L"";
	swprintf_s(szBuff, L"Unit_Frame%02d", _iNum);

	// 기본 프레임바 이미지 가져오기
	m_tStatusBar.m_FrameBarDC = CBitmapMgr::Get_Instance()->Find_Image(szBuff);

	// HpBar HDC 설정
	lstrcpy(szBuff, L"");
	swprintf_s(szBuff, L"Unit_Hp%02d", _iNum);

	// 체력바 이미지 가져오기
	m_tStatusBar.m_HpBarDC = CBitmapMgr::Get_Instance()->Find_Image(szBuff);

	// ShieldBar HDC 설정
	lstrcpy(szBuff, L"");
	swprintf_s(szBuff, L"Unit_Shield%02d", _iNum);

	// 쉴드바 이미지 가져오기
	m_tStatusBar.m_ShieldBarDC = CBitmapMgr::Get_Instance()->Find_Image(szBuff);

	// 설정한 HDC의 이미지 정보 설정
	switch (_iNum) {
	case 0:
		m_tStatusBar.m_tFrameBarInfo.fCX = 22;
		m_tStatusBar.m_tHpBarInfo.fCX = 22;
		m_tStatusBar.m_tShieldBarInfo.fCX = 22;
		break;
	case 1:
		m_tStatusBar.m_tFrameBarInfo.fCX = 31;
		m_tStatusBar.m_tHpBarInfo.fCX = 31;
		m_tStatusBar.m_tShieldBarInfo.fCX = 31;
		break;
	case 2:
		m_tStatusBar.m_tFrameBarInfo.fCX = 31;
		m_tStatusBar.m_tHpBarInfo.fCX = 31;
		m_tStatusBar.m_tShieldBarInfo.fCX = 31;
		break;
	case 3:
		m_tStatusBar.m_tFrameBarInfo.fCX = 34;
		m_tStatusBar.m_tHpBarInfo.fCX = 34;
		m_tStatusBar.m_tShieldBarInfo.fCX = 34;
		break;
	case 4:
		m_tStatusBar.m_tFrameBarInfo.fCX = 52;
		m_tStatusBar.m_tHpBarInfo.fCX = 52;
		m_tStatusBar.m_tShieldBarInfo.fCX = 52;
		break;
	case 5:
		m_tStatusBar.m_tFrameBarInfo.fCX = 79;
		m_tStatusBar.m_tHpBarInfo.fCX = 79;
		m_tStatusBar.m_tShieldBarInfo.fCX = 79;
		break;
	case 6:
		m_tStatusBar.m_tFrameBarInfo.fCX = 82;
		m_tStatusBar.m_tHpBarInfo.fCX = 82;
		m_tStatusBar.m_tShieldBarInfo.fCX = 82;
		break;
	case 7:
		m_tStatusBar.m_tFrameBarInfo.fCX = 91;
		m_tStatusBar.m_tHpBarInfo.fCX = 91;
		m_tStatusBar.m_tShieldBarInfo.fCX = 91;
		break;
	case 8:
		m_tStatusBar.m_tFrameBarInfo.fCX = 109;
		m_tStatusBar.m_tHpBarInfo.fCX = 109;
		m_tStatusBar.m_tShieldBarInfo.fCX = 109;
		break;
	}

	m_tStatusBar.m_tFrameBarInfo.fCY = 7;
	m_tStatusBar.m_tHpBarInfo.fCY = 7;
	m_tStatusBar.m_tShieldBarInfo.fCY = 7;

}

void CObj::Set_Portrait(UNIT_NAME _eUnitName)
{
	m_tPortrait.m_tInfo.fCX = 70;
	m_tPortrait.m_tInfo.fCY = 56;
	m_tPortrait.m_tInfo.fX = 555;
	m_tPortrait.m_tInfo.fY = 548;

	Update_Rect(m_tPortrait.m_tInfo, m_tPortrait.m_tRect);

	m_tPortrait.m_tFrame.dwFrameSpeed = 100;
	m_tPortrait.m_tFrame.dwFrameTime = 0;
	m_tPortrait.m_tFrame.iFrameStart = 0;
	m_tPortrait.m_tFrame.iFrameCurr = 0;
	m_tPortrait.m_tFrame.iFrameScene = 0;
	m_tPortrait.m_tFrame.iWidth = 57;
	m_tPortrait.m_tFrame.iHeight = 49;

	m_tPortrait.m_tFrame.iFrameEnd = 50;
	switch (_eUnitName)
	{
	case UNIT_NAME::Probe:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Probe_Portrait");

		m_tPortrait.m_tFrame.iFrameEnd = 75;
		break;
	case UNIT_NAME::Zealot:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Zealot_Portrait");

		m_tPortrait.m_tFrame.iFrameEnd = 50;
		break;
	case UNIT_NAME::Dark_Templar:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Templar_Portrait");
		break;
	case UNIT_NAME::Dragon:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dragon_Portrait");
		break;
	case UNIT_NAME::Reaver:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Reaver_Portrait");
		break;
	case UNIT_NAME::Shuttle:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Shuttle_Portrait");
		break;
	case UNIT_NAME::Scout:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Scout_Portrait");

		m_tPortrait.m_tFrame.iFrameEnd = 65;
		break;
	case UNIT_NAME::Arbiter:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Arbiter_Portrait");

		m_tPortrait.m_tFrame.iFrameEnd = 75;
		break;
	case UNIT_NAME::Archon:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Archon_Portrait");
		break;
	case UNIT_NAME::Dark_Archon:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Dark_Archon_Portrait");
		break;
	case UNIT_NAME::Observer:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Observer_Portrait");
		break;
	case UNIT_NAME::Carrier:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Carrier_Portrait");
		break;
	case UNIT_NAME::Interceptor:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Interceptor_Portrait");
		break;
	case UNIT_NAME::Corsair:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Corsair_Portrait");
		break;
	case UNIT_NAME::High_Templar:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_High_Templar_Portrait");
		break;
	case UNIT_NAME::END:
		break;
	default:
		break;
	}
}

void CObj::Set_Portrait(BUILD _eUnitName)
{
	m_tPortrait.m_tInfo.fCX = 70;
	m_tPortrait.m_tInfo.fCY = 56;
	m_tPortrait.m_tInfo.fX = 555;
	m_tPortrait.m_tInfo.fY = 548;

	Update_Rect(m_tPortrait.m_tInfo, m_tPortrait.m_tRect);

	m_tPortrait.m_tFrame.dwFrameSpeed = 100;
	m_tPortrait.m_tFrame.dwFrameTime = 0;
	m_tPortrait.m_tFrame.iFrameStart = 0;
	m_tPortrait.m_tFrame.iFrameCurr = 0;
	m_tPortrait.m_tFrame.iFrameScene = 0;
	m_tPortrait.m_tFrame.iWidth = 57;
	m_tPortrait.m_tFrame.iHeight = 49;


	m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Arbiter_Portrait");

	m_tPortrait.m_tFrame.iFrameEnd = 75;

	switch (_eUnitName)
	{
	case BUILD::Arbiter_Tribunal:
		break;
	case BUILD::Assimilator:
		m_tPortrait.m_PortraitDC = CBitmapMgr::Get_Instance()->Find_Image(L"Unit_Scout_Portrait");

		m_tPortrait.m_tFrame.iFrameEnd = 65;
		break;
	case BUILD::Citadel_of_Adun:
		break;
	case BUILD::Cybernetics_Core:
		break;
	case BUILD::Fleet_Beacon:
		break;
	case BUILD::Forge:
		break;
	case BUILD::Gateway:
		break;
	case BUILD::Nexus:
		break;
	case BUILD::Observatory:
		break;
	case BUILD::Photon_Cannon:
		break;
	case BUILD::Pylon:
		break;
	case BUILD::Robotics_Facility:
		break;
	case BUILD::Robotics_Support_Bay:
		break;
	case BUILD::Shield_Battery:
		break;
	case BUILD::Stargate:
		break;
	case BUILD::Tempar_Archives:
		break;
	case BUILD::END:
		break;
	default:
		break;
	}
}

void CObj::Update_Wire(void)
{
	if (m_eType == OBJ_TYPE::UNIT) {
		m_tWireInfo.m_tInfo.fX = m_tInfo.fX;
		m_tWireInfo.m_tInfo.fY = m_tInfo.fY + 5;

		Update_Rect(m_tWireInfo.m_tInfo, m_tWireInfo.m_tRect);
	}
	else if (m_eType == OBJ_TYPE::BUILD) {
		m_tWireInfo.m_tInfo.fX = m_tInfo.fX;
		m_tWireInfo.m_tInfo.fY = m_tInfo.fY + 15;

		Update_Rect(m_tWireInfo.m_tInfo, m_tWireInfo.m_tRect);
	}
}

void CObj::Update_StatusBar(void)
{
	if (m_eType == OBJ_TYPE::UNIT) {
		// FrameBar
		//===========================================================================================================================
		m_tStatusBar.m_tFrameBarInfo.fX = m_tInfo.fX;
		m_tStatusBar.m_tFrameBarInfo.fY = m_tInfo.fY + m_tInfo.fCY * 0.5 + 5;

		Update_Rect(m_tStatusBar.m_tFrameBarInfo, m_tStatusBar.m_tFrameBarRect);
		//===========================================================================================================================


		// HpBar
		//===========================================================================================================================
		m_tStatusBar.m_tHpBarInfo.fX = m_tInfo.fX;
		m_tStatusBar.m_tHpBarInfo.fY = m_tInfo.fY + m_tInfo.fCY * 0.5 + 5;

		Update_Rect(m_tStatusBar.m_tHpBarInfo, m_tStatusBar.m_tHpBarRect);
		//===========================================================================================================================


		// ShieldBar
		//===========================================================================================================================
		m_tStatusBar.m_tShieldBarInfo.fX = m_tInfo.fX;
		m_tStatusBar.m_tShieldBarInfo.fY = m_tInfo.fY + m_tInfo.fCY * 0.5 + 5;

		Update_Rect(m_tStatusBar.m_tShieldBarInfo, m_tStatusBar.m_tShieldBarRect);
		//===========================================================================================================================
	}
	else if (m_eType == OBJ_TYPE::BUILD) {
		// FrameBar
		//===========================================================================================================================
		m_tStatusBar.m_tFrameBarInfo.fX = m_tInfo.fX;
		m_tStatusBar.m_tFrameBarInfo.fY = m_tInfo.fY + m_tBuildInfo.iRealHeight * 0.3;

		Update_Rect(m_tStatusBar.m_tFrameBarInfo, m_tStatusBar.m_tFrameBarRect);
		//===========================================================================================================================


		// HpBar
		//===========================================================================================================================
		m_tStatusBar.m_tHpBarInfo.fX = m_tInfo.fX;
		m_tStatusBar.m_tHpBarInfo.fY = m_tInfo.fY + m_tBuildInfo.iRealHeight * 0.3;

		Update_Rect(m_tStatusBar.m_tHpBarInfo, m_tStatusBar.m_tHpBarRect);
		//===========================================================================================================================


		// ShieldBar
		//===========================================================================================================================
		m_tStatusBar.m_tShieldBarInfo.fX = m_tInfo.fX;
		m_tStatusBar.m_tShieldBarInfo.fY = m_tInfo.fY + m_tBuildInfo.iRealHeight * 0.3;

		Update_Rect(m_tStatusBar.m_tShieldBarInfo, m_tStatusBar.m_tShieldBarRect);
		//===========================================================================================================================
	}
}

void CObj::Update_Shadow(void)
{
}

void CObj::Update_Portrait(void)
{
	if (m_tPortrait.m_tFrame.dwFrameTime + m_tPortrait.m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tPortrait.m_tFrame.iFrameCurr;
		m_tPortrait.m_tFrame.dwFrameTime = GetTickCount();

		if (m_tPortrait.m_tFrame.iFrameCurr >= m_tPortrait.m_tFrame.iFrameEnd)
			m_tPortrait.m_tFrame.iFrameCurr = m_tPortrait.m_tFrame.iFrameStart;
	}
}
