#include "stdafx.h"
#include "Build.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"

CBuild::CBuild()
{
}

CBuild::CBuild(const BuildInfo& _tBuildInfo)
{
	m_tBuildInfo = _tBuildInfo;
}


CBuild::~CBuild()
{
}

void CBuild::Initialize(void)
{
	m_eType = OBJ_TYPE::BUILD;

	m_CreateBuildDC = CBitmapMgr::Get_Instance()->Find_Image(L"createBuild");
	m_CreateBuildAfterDC = CBitmapMgr::Get_Instance()->Find_Image(L"createBuildAfter");

	Set_BuildStatus(BUILD_STATUS::Build_Start);

	m_tCreateBuildFrame.iWidth = 152;
	m_tCreateBuildFrame.iHeight = 152;
	m_tCreateBuildFrame.dwFrameSpeed = 30;
	m_tCreateBuildFrame.iFrameStart = 0;
	m_tCreateBuildFrame.iFrameCurr = 0;

	m_tBuildInfo.m_dwCurrBuildTime = 0;

	m_eRelation = RELATION::Alliance;

	m_iRepeatBuildingCnt = 5;

	Set_Build(m_tBuildInfo.m_eBuild);

	Set_BuildInfo(m_tBuildInfo.m_eBuild);
}

int CBuild::Update(void)
{
	Update_Rect();
	Update_Wire();
	Update_StatusBar();
	Update_Shadow();
	Update_Portrait();
	Move_BuildFrame();

	return 0;
}

int CBuild::Late_Update(void)
{
	return 0;
}

void CBuild::Render(HDC hDC)
{
	Update_Rect();

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 유닛 그리는 순서 : 그림자 -> 와이어 -> 건물 -> 상태바 순으로 그리기
	// 유저에게 선택을 당했다면
	// 와이어와 상태바를 출력한다.

	// 와이어
	if (m_bSelected)
		DrawWire(hDC);

	switch (m_eBuildStatus)
	{
	case BUILD_STATUS::Build_Start:
	case BUILD_STATUS::Building:
	case BUILD_STATUS::Building_Compelete:
	{

		TransparentBlt(hDC,
			int(m_tRect.left - iScrollX),
			int(m_tRect.top - iScrollY),

			m_tInfo.fCX,
			m_tInfo.fCY,

			m_CreateBuildDC,

			163 * m_tCreateBuildFrame.iFrameCurr,
			172 * (int)m_eBuildStatus,

			163,
			172,

			RGB(255, 255, 255));
	}
	break;

	case BUILD_STATUS::Build_After:
		TransparentBlt(hDC,
			int(m_tInfo.fX - m_tBuildInfo.iRealWidth * 0.5 - iScrollX),
			int(m_tInfo.fY - m_tBuildInfo.iRealHeight * 0.5 - iScrollY),

			m_tBuildInfo.iRealWidth,
			m_tBuildInfo.iRealHeight,

			m_tBuildInfo.m_Create_AfterDC,

			m_tBuildInfo.iWidth * m_tCreateBuildFrame.iFrameCurr,
			0,

			m_tBuildInfo.iWidth,
			m_tBuildInfo.iHeight,

			RGB(255, 255, 255));
		break;

	case BUILD_STATUS::Build_Compelte:
	{
		// 그림자
		DrawShad(hDC);

		TransparentBlt(hDC,
			int(m_tInfo.fX - m_tBuildInfo.iRealWidth * 0.5 - iScrollX),
			int(m_tInfo.fY - m_tBuildInfo.iRealHeight * 0.5 - iScrollY),

			m_tBuildInfo.iRealWidth,
			m_tBuildInfo.iRealHeight,

			m_tBuildInfo.m_DC,

			0, 0,

			m_tBuildInfo.iWidth,
			m_tBuildInfo.iHeight,

			RGB(255, 255, 255));
	}
	break;

	case BUILD_STATUS::END:
		break;
	default:
		break;
	}


	// 상태바
	if (m_bSelected)
		DrawStatusBar(hDC);

}

void CBuild::Release(void)
{
}

void CBuild::Set_BuildStatus(BUILD_STATUS _eBuildStatus)
{
	m_eBuildStatus = _eBuildStatus;

	m_tCreateBuildFrame.dwFrameTime = GetTickCount();

	m_tCreateBuildFrame.iFrameCurr = 0;

	// 상태에 따른 Frame 정보 초기화
	switch (_eBuildStatus)
	{
	case BUILD_STATUS::Build_Start:
		CSoundMgr::Get_Instance()->PlaySoundW(L"BuildWarp.wav", CHANNELID::Build, UNIT_SOUND);
		m_tCreateBuildFrame.iFrameEnd = 6;
		m_tInfo.fCX = 150;
		m_tInfo.fCY = 150;

		break;
	
	case BUILD_STATUS::Building:
		m_tCreateBuildFrame.dwFrameSpeed = 70;
		m_tCreateBuildFrame.iFrameEnd = 5;
		break;
	
	case BUILD_STATUS::Building_Compelete:
		m_tCreateBuildFrame.iFrameEnd = 2;
		break;

	case BUILD_STATUS::Build_After:
		CSoundMgr::Get_Instance()->PlaySoundW(L"BuildSuccess.wav", CHANNELID::Build, UNIT_SOUND);
		m_tCreateBuildFrame.iFrameEnd = 20;
		break;

	case BUILD_STATUS::Build_Compelte:
		m_tCreateBuildFrame.iFrameEnd = 0;
		break;

	case BUILD_STATUS::END:
		break;

	default:
		break;
	}
}

void CBuild::Move_BuildFrame(void)
{
	if (m_eBuildStatus == BUILD_STATUS::Build_Compelte)
		return;

	if (m_tCreateBuildFrame.dwFrameTime + m_tCreateBuildFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tCreateBuildFrame.iFrameCurr;
		m_tCreateBuildFrame.dwFrameTime = GetTickCount();

		// 상태에 따라 달라지게 만든다.
		if (m_tCreateBuildFrame.iFrameCurr >= m_tCreateBuildFrame.iFrameEnd) {
			switch (m_eBuildStatus)
			{
			case BUILD_STATUS::Build_Start:
				Set_BuildStatus(BUILD_STATUS::Building);
				break;

			case BUILD_STATUS::Building:
				if (m_iRepeatBuildingCnt <= 0)
					Set_BuildStatus(BUILD_STATUS::Building_Compelete);
				else {
					--m_iRepeatBuildingCnt;
					m_tCreateBuildFrame.iFrameCurr = 0;
				}
				break;

			case BUILD_STATUS::Building_Compelete:
				Set_BuildStatus(BUILD_STATUS::Build_After);
				break;

			case BUILD_STATUS::Build_After:
				Set_BuildStatus(BUILD_STATUS::Build_Compelte);
				break;

			case BUILD_STATUS::Build_Compelte:
				break;

			case BUILD_STATUS::END:
				break;

			default:
				break;
			}
			
		}
	}
}

void CBuild::Set_Build(BUILD _eBuild)
{

	// 유닛의 아래 나타나는 동그란 와이어
	Set_Wire(4);

	// 유닛의 체력과 쉴드를 나타내는 스탯바
	Set_StatusFrame(7);

	switch (_eBuild)
	{
	case BUILD::Arbiter_Tribunal:
		break;
	case BUILD::Assimilator:
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
		Set_Wire(6);
		break;

	case BUILD::Nexus:
		Set_Wire(6);
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
		Set_Wire(6);
		break;
	case BUILD::Tempar_Archives:
		break;
	case BUILD::END:
		break;
	default:
		break;
	}

}

void CBuild::Set_BuildStatus(BUILD _eBuild)
{
	// 205 490		300 570
	ZeroMemory(&m_tStatusFrameInfo.m_tStatusFrame, sizeof(FRAME));

	m_tStatusFrameInfo.m_tStatusFrame.iWidth = 154;
	m_tStatusFrameInfo.m_tStatusFrame.iHeight = 84;

	switch (_eBuild)
	{
	case BUILD::Arbiter_Tribunal:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Arbiter_Tribunal_Status");
		break;
	case BUILD::Assimilator:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Assimilator_Status");
		break;
	case BUILD::Citadel_of_Adun:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Citadel_of_Adun_Status");
		break;
	case BUILD::Cybernetics_Core:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Cybernetics_Core_Status");
		break;
	case BUILD::Fleet_Beacon:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Fleet_Beacon_Status");
		break;
	case BUILD::Forge:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Forge_Status");
		break;
	case BUILD::Gateway:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Gateway_Status");
		break;
	case BUILD::Nexus:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Nexus_Status");
		break;
	case BUILD::Observatory:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Observatory_Status");
		break;
	case BUILD::Photon_Cannon:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Photon_Cannon_Status");
		break;
	case BUILD::Pylon:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Pylon_Status");
		break;
	case BUILD::Robotics_Facility:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Robotics_Facility_Status");
		break;
	case BUILD::Robotics_Support_Bay:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Robotics_Support_Bay_Status");
		break;
	case BUILD::Shield_Battery:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Shield_Battery_Status");
		break;
	case BUILD::Stargate:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Stargate_Status");
		break;
	case BUILD::Tempar_Archives:
		m_tStatusFrameInfo.m_StatusDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Tempar_Archives_Status");
		break;
	case BUILD::END:
		break;
	default:
		break;
	}

	m_tStatusFrameInfo.m_tStatusInfo.fCX = 180;
	m_tStatusFrameInfo.m_tStatusInfo.fCY = 90;
	m_tStatusFrameInfo.m_tStatusInfo.fX = 400;
	m_tStatusFrameInfo.m_tStatusInfo.fY = 540;

	Update_Rect(m_tStatusFrameInfo.m_tStatusInfo, m_tStatusFrameInfo.m_tStatusRect);
}

void CBuild::Set_WireFrameInfo(BUILD _eBuild)
{
	// 205 490		300 570
	m_tWireFrameInfo.m_tBigWireInfo.fX = 255;
	m_tWireFrameInfo.m_tBigWireInfo.fY = 530;
	m_tWireFrameInfo.m_tBigWireInfo.fCX = 100;
	m_tWireFrameInfo.m_tBigWireInfo.fCY = 80;

	Update_Rect(m_tWireFrameInfo.m_tBigWireInfo, m_tWireFrameInfo.m_tBigWireRect);

	m_tWireFrameInfo.m_tBigWireFrame.iFrameScene = 0;
	m_tWireFrameInfo.m_tBigWireFrame.iFrameCurr = 0;
	m_tWireFrameInfo.m_tBigWireFrame.iFrameStart = 0;
	m_tWireFrameInfo.m_tBigWireFrame.iFrameEnd = 6;

	m_tWireFrameInfo.m_tBigWireFrame.iWidth = 64;
	m_tWireFrameInfo.m_tBigWireFrame.iHeight = 64;

	switch (_eBuild)
	{
	case BUILD::Arbiter_Tribunal:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Arbiter_Tribunal_WireBig");
		break;
	case BUILD::Assimilator:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Assimilator_WireBig");
		break;
	case BUILD::Citadel_of_Adun:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Citadel_of_Adun_WireBig");
		break;
	case BUILD::Cybernetics_Core:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Cybernetics_Core_WireBig");
		break;
	case BUILD::Fleet_Beacon:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Fleet_Beacon_WireBig");
		break;
	case BUILD::Forge:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Forge_WireBig");
		break;
	case BUILD::Gateway:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Gateway_WireBig");
		break;
	case BUILD::Nexus:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Nexus_WireBig");
		break;
	case BUILD::Observatory:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Observatory_WireBig");
		break;
	case BUILD::Photon_Cannon:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Photon_Cannon_WireBig");
		break;
	case BUILD::Pylon:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Pylon_WireBig");
		break;
	case BUILD::Robotics_Facility:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Robotics_Facility_WireBig");
		break;
	case BUILD::Robotics_Support_Bay:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Robotics_Support_Bay_WireBig");
		break;
	case BUILD::Shield_Battery:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Shield_Battery_WireBig");
		break;
	case BUILD::Stargate:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Stargate_WireBig");
		break;
	case BUILD::Tempar_Archives:
		m_tWireFrameInfo.m_BigWireDC = CBitmapMgr::Get_Instance()->Find_Image(L"Build_Tempar_Archives_WireBig");
		break;
	case BUILD::END:
		break;
	default:
		break;
	}
}

void CBuild::Set_BuildInfo(BUILD _eBuild)
{
	// 유닛의 이름
	m_tBuildInfo.m_eBuild = _eBuild;

	// 유닛의 초상화 설정
	Set_Portrait(_eBuild);

	// 유닛의 와이어 프레임 설정
	Set_WireFrameInfo(_eBuild);

	// 유닛의 스탯창 정보 설정
	Set_BuildStatus(_eBuild);
}
