#include "stdafx.h"
#include "UIButtonMgr.h"
#include "BuildMgr.h"
#include "UnitMgr.h"
#include "SoundMgr.h"


CUIButtonMgr::CUIButtonMgr()
{
	//ZeroMemory(m_Button, sizeof(CUIButton) * 9);
}


CUIButtonMgr::~CUIButtonMgr()
{
	Release();
}

void CUIButtonMgr::Initialize(void)
{
	Clear_ButtonInfo();

	for (int i = 0; i < (int)BUTTON_ACTION::END; ++i) {
		m_ActionButton[i] = new CActionButton((BUTTON_ACTION)i);
	}
	for (int i = 0; i < (int)BUTTON_BUILD::END; ++i) {
		m_BuildButton[i] = new CBuildButton((BUTTON_BUILD)i);
	}
	for (int i = 0; i < (int)BUTTON_SKILL::END; ++i) {
		m_SkillButton[i] = new CSkillButton((BUTTON_SKILL)i);
	}
	for (int i = 0; i < (int)BUTTON_UNIT::END; ++i) {
		m_UnitButton[i] = new CUnitButton((BUTTON_UNIT)i);
	}
	for (int i = 0; i < (int)BUTTON_UPGRADE::END; ++i) {
		m_UpgradeButton[i] = new CUpgradeButton((BUTTON_UPGRADE)i);
	}
	m_TempButton = new CTempButton;
}

int CUIButtonMgr::Update(void)
{
	for (int i = 0; i < 9; ++i) {
		if (!m_stButton[i].empty()) {
			m_stButton[i].top()->Update();
		}
	}

	return 0;
}

void CUIButtonMgr::Late_Update(void)
{
	for (int i = 0; i < 9; ++i) {
		if (!m_stButton[i].empty()) {
			m_stButton[i].top()->Late_Update();
		}
	}
}

void CUIButtonMgr::Render(HDC hDC)
{
	for (int i = 0; i < 9; ++i) {
		if (!m_stButton[i].empty()) {
			m_stButton[i].top()->Render(hDC);
		}
	}
}

void CUIButtonMgr::Release(void)
{
}

void CUIButtonMgr::Clear_ButtonInfo(void)
{
	for (int i = 0; i < 9; ++i) {
		while (!m_stButton[i].empty()) {
			m_stButton[i].pop();
		}
	}
}

void CUIButtonMgr::Set_ButtonInfo(void)
{
	// 시작 위치			left, top				=> 632, 447
	// 가로/세로 길이		Width, Height			=> 45, 42
	// 가로/세로 gap		GapWidth, GapHeight		=> 12, 7

	int	iLeft = 633;
	int	iTop = 448;
	int	iWidth = UNIT_BUTTON_WIDTH;
	int	iHeight = UNIT_BUTTON_HEIGHT;
	int iGapWidth = 8;
	int iGapHeight = 8;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			// 중점 위치 설정
			float fX = iLeft + (iWidth >> 1) + (iWidth + iGapWidth) * j;
			float fY = iTop + (iHeight >> 1) + (iHeight + iGapHeight) * i;

			if (!m_stButton[i * 3 + j].empty()) {
				m_stButton[i * 3 + j].top()->Set_Pos(fX, fY);
				m_stButton[i * 3 + j].top()->Update_Rect();
			}
		}
	}
}

void CUIButtonMgr::Set_UnitButtonInfo(int _iButtonNum, BUTTON_ACTION _eAction)
{
	m_stButton[_iButtonNum].push(m_ActionButton[(int)_eAction]);
}

void CUIButtonMgr::Set_UnitButtonInfo(int _iButtonNum, BUTTON_BUILD _eAction)
{
	m_stButton[_iButtonNum].push(m_BuildButton[(int)_eAction]);
}

void CUIButtonMgr::Set_UnitButtonInfo(int _iButtonNum, BUTTON_SKILL _eAction)
{
	m_stButton[_iButtonNum].push(m_SkillButton[(int)_eAction]);
}

void CUIButtonMgr::Set_UnitButtonInfo(int _iButtonNum, BUTTON_UNIT _eAction)
{
	m_stButton[_iButtonNum].push(m_UnitButton[(int)_eAction]);
}

void CUIButtonMgr::Set_UnitButtonInfo(int _iButtonNum, BUTTON_UPGRADE _eAction)
{
	m_stButton[_iButtonNum].push(m_UpgradeButton[(int)_eAction]);
}

void CUIButtonMgr::ClickObject(UNIT_NAME _eUnitName)
{
	Clear_ButtonInfo();

	CSoundMgr::Get_Instance()->StopSound(CHANNELID::Alliance);

	switch (_eUnitName)
	{
	case UNIT_NAME::Probe:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Mining);
		Set_UnitButtonInfo(6, BUTTON_ACTION::NBuild);
		Set_UnitButtonInfo(7, BUTTON_ACTION::HBuild);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ppryes00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ppryes01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ppryes02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ppryes03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}

		break;
	case UNIT_NAME::Zealot:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PZeYes00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PZeYes01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PZeYes02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PZeYes03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}

		break;
	case UNIT_NAME::Dark_Templar:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDTWht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDTWht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDTWht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDTWht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;

	case UNIT_NAME::Dragon:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDrYes00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDrYes01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDrYes02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PDrYes03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;

	case UNIT_NAME::Reaver:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ptrwht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ptrwht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ptrwht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"ptrwht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;

	case UNIT_NAME::Shuttle:
		break;

	case UNIT_NAME::Scout:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PScWht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PScWht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PScWht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PScWht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::Arbiter:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);
		Set_UnitButtonInfo(6, BUTTON_SKILL::Recall);
		Set_UnitButtonInfo(7, BUTTON_SKILL::StasisField);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pabWht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pabWht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pabWht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pabWht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::Archon:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"parWht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"parWht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"parWht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"parWht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::Dark_Archon:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(6, BUTTON_SKILL::FeedBack);
		Set_UnitButtonInfo(7, BUTTON_SKILL::MindControl);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pdawht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pdawht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pdawht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pdawht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::Observer:
		break;
	case UNIT_NAME::Carrier:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);
		Set_UnitButtonInfo(6, BUTTON_UNIT::Interceptor);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PCaWht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PCaWht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PCaWht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"PCaWht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::Interceptor:
		break;
	case UNIT_NAME::Corsair:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(2, BUTTON_ACTION::Attack);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);
		Set_UnitButtonInfo(6, BUTTON_SKILL::Wap);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pcowht00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pcowht01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pcowht02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pcowht03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::High_Templar:
		Set_UnitButtonInfo(0, BUTTON_ACTION::Move);
		Set_UnitButtonInfo(1, BUTTON_ACTION::Stop);
		Set_UnitButtonInfo(3, BUTTON_ACTION::Patrol);
		Set_UnitButtonInfo(4, BUTTON_ACTION::Hold);
		Set_UnitButtonInfo(6, BUTTON_SKILL::Storm);
		Set_UnitButtonInfo(7, BUTTON_SKILL::Illusion);

		switch (rand() % 4)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pteYes00.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pteYes01.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pteYes02.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySoundW(L"pteYes03.wav", CHANNELID::Alliance, UNIT_SOUND);
			break;
		}
		break;
	case UNIT_NAME::END:
		break;
	default:
		break;
	}

	Set_ButtonInfo();
}

void CUIButtonMgr::ClickObject(BUILD _eBuild)
{
	Clear_ButtonInfo();

	switch (_eBuild)
	{
	case BUILD::Arbiter_Tribunal:
		Set_UnitButtonInfo(0, BUTTON_UPGRADE::ArbiterMpUpgrade);
		Set_UnitButtonInfo(1, BUTTON_UPGRADE::ArbiterRecallUpgrade);
		Set_UnitButtonInfo(2, BUTTON_UPGRADE::ArbiterStasisFieldUpgrade);
		break;
	case BUILD::Assimilator:
		break;
	case BUILD::Citadel_of_Adun:
		Set_UnitButtonInfo(0, BUTTON_UPGRADE::ZealotSpeedUP);
		break;
	case BUILD::Cybernetics_Core:
		Set_UnitButtonInfo(0, BUTTON_UPGRADE::ArrArmorUpgrade);
		Set_UnitButtonInfo(1, BUTTON_UPGRADE::ArrAttUpgrade);
		Set_UnitButtonInfo(2, BUTTON_UPGRADE::DragonRangeUP);
		break;
	case BUILD::Fleet_Beacon:
		Set_UnitButtonInfo(0, BUTTON_UPGRADE::CorsairMpUp);
		Set_UnitButtonInfo(1, BUTTON_UPGRADE::InterceptorCountUpgrade);
		Set_UnitButtonInfo(2, BUTTON_UPGRADE::ScoutSpeedUpgrade);
		Set_UnitButtonInfo(3, BUTTON_UPGRADE::ScoutViewUpgrade);
		break;
	case BUILD::Forge:
		Set_UnitButtonInfo(0, BUTTON_UPGRADE::GroundArmorUpgrade);
		Set_UnitButtonInfo(1, BUTTON_UPGRADE::GroundAttUpgrade);
		Set_UnitButtonInfo(2, BUTTON_UPGRADE::GroundShildUpgrade);
		break;

	case BUILD::Gateway:
		Set_UnitButtonInfo(0, BUTTON_UNIT::Zealot);
		Set_UnitButtonInfo(1, BUTTON_UNIT::Dragoon);
		Set_UnitButtonInfo(2, BUTTON_UNIT::HighTemplar);
		Set_UnitButtonInfo(3, BUTTON_UNIT::DarkTemplar);
		Set_UnitButtonInfo(4, BUTTON_UNIT::Archon);
		Set_UnitButtonInfo(5, BUTTON_UNIT::Dark_Archon);
		break;
	case BUILD::Nexus:
		Set_UnitButtonInfo(0, BUTTON_UNIT::Probe);
		Set_UnitButtonInfo(5, BUTTON_ACTION::Rally);
		break;
	case BUILD::Observatory:
		break;
	case BUILD::Photon_Cannon:
		break;
	case BUILD::Pylon:
		break;
	case BUILD::Robotics_Facility:
		Set_UnitButtonInfo(0, BUTTON_UNIT::Shuttle);
		Set_UnitButtonInfo(1, BUTTON_UNIT::Reaver);
		Set_UnitButtonInfo(2, BUTTON_UNIT::Observer);
		break;
	case BUILD::Robotics_Support_Bay:
		break;
	case BUILD::Shield_Battery:
		break;
	case BUILD::Stargate:
		Set_UnitButtonInfo(0, BUTTON_UNIT::Corsair);
		Set_UnitButtonInfo(1, BUTTON_UNIT::Scout);
		Set_UnitButtonInfo(2, BUTTON_UNIT::Carrier);
		Set_UnitButtonInfo(3, BUTTON_UNIT::Arbiter);
		break;
	case BUILD::Tempar_Archives:
		Set_UnitButtonInfo(0, BUTTON_UPGRADE::DarkArchonMindControlUpgrade);
		Set_UnitButtonInfo(1, BUTTON_UPGRADE::TemplarIllusionUpgrade);
		Set_UnitButtonInfo(2, BUTTON_UPGRADE::TemplarMpUpgrade);
		Set_UnitButtonInfo(3, BUTTON_UPGRADE::TemplarStormUpgrade);
		break;
	case BUILD::END:
		break;
	default:
		break;
	}

	Set_ButtonInfo();
}

void CUIButtonMgr::ClickObject(void)
{
}

void CUIButtonMgr::ClickButton(BUTTON_ACTION _eAction)
{
	if (_eAction == BUTTON_ACTION::NBuild ||
		_eAction == BUTTON_ACTION::HBuild ||
		_eAction == BUTTON_ACTION::Move ||
		_eAction == BUTTON_ACTION::Attack ||
		_eAction == BUTTON_ACTION::Stop ||
		_eAction == BUTTON_ACTION::Mining ||
		_eAction == BUTTON_ACTION::Hold ||
		_eAction == BUTTON_ACTION::Patrol ||
		_eAction == BUTTON_ACTION::Cancel) {
		;
	}
	else {
		Clear_ButtonInfo();
	}

	switch (_eAction)
	{
	case BUTTON_ACTION::Boarding:
		break;

	case BUTTON_ACTION::Cancel:
		for (int i = 0; i < 9; ++i) {
			if (!m_stButton[i].empty())
				m_stButton[i].pop();
		}
		if (CBuildMgr::Get_Instance()->Get_CurrBuild() != BUILD::END)
			CBuildMgr::Get_Instance()->Set_CurrBuild(BUILD::END);
		break;

	case BUTTON_ACTION::HBuild:
		Set_UnitButtonInfo(0, BUTTON_BUILD::Robotics_Facility);
		Set_UnitButtonInfo(1, BUTTON_BUILD::Stargate);
		Set_UnitButtonInfo(2, BUTTON_BUILD::Citadel_of_Adun);
		Set_UnitButtonInfo(3, BUTTON_BUILD::Robotics_Support_Bay);
		Set_UnitButtonInfo(4, BUTTON_BUILD::Fleet_Beacon);
		Set_UnitButtonInfo(5, BUTTON_BUILD::Tempar_Archives);
		Set_UnitButtonInfo(6, BUTTON_BUILD::Observatory);
		Set_UnitButtonInfo(7, BUTTON_BUILD::Arbiter_Tribunal);
		Set_UnitButtonInfo(8, BUTTON_ACTION::Cancel);
		break;

	case BUTTON_ACTION::NBuild:
		Set_UnitButtonInfo(0, BUTTON_BUILD::Nexus);
		Set_UnitButtonInfo(1, BUTTON_BUILD::Pylon);
		Set_UnitButtonInfo(2, BUTTON_BUILD::Assimilator);
		Set_UnitButtonInfo(3, BUTTON_BUILD::Gateway);
		Set_UnitButtonInfo(4, BUTTON_BUILD::Forge);
		Set_UnitButtonInfo(5, BUTTON_BUILD::Photon_Cannon);
		Set_UnitButtonInfo(6, BUTTON_BUILD::Cybernetics_Core);
		Set_UnitButtonInfo(7, BUTTON_BUILD::Shield_Battery);
		Set_UnitButtonInfo(8, BUTTON_ACTION::Cancel);
		break;

	case BUTTON_ACTION::Landing:
		break;

	case BUTTON_ACTION::Attack:
	case BUTTON_ACTION::Mining:
	case BUTTON_ACTION::Move:
	case BUTTON_ACTION::Patrol:
	case BUTTON_ACTION::Hold:
	case BUTTON_ACTION::Stop:
	case BUTTON_ACTION::Rally:
	case BUTTON_ACTION::Return:
		for (int i = 0; i < 8; ++i) {
			m_stButton[i].push(m_TempButton);
		}
		Set_UnitButtonInfo(8, BUTTON_ACTION::Cancel);
		break;

	case BUTTON_ACTION::END:
		break;

	default:
		break;
	}

	Set_ButtonInfo();
}

void CUIButtonMgr::ClickButton(BUTTON_BUILD _eAction)
{
	switch (_eAction)
	{
	case BUTTON_BUILD::Arbiter_Tribunal:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Arbiter_Tribunal);
		break;
	case BUTTON_BUILD::Assimilator:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Assimilator);
		break;
	case BUTTON_BUILD::Citadel_of_Adun:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Citadel_of_Adun);
		break;
	case BUTTON_BUILD::Cybernetics_Core:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Cybernetics_Core);
		break;
	case BUTTON_BUILD::Fleet_Beacon:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Fleet_Beacon);
		break;
	case BUTTON_BUILD::Forge:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Forge);
		break;
	case BUTTON_BUILD::Gateway:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Gateway);
		break;
	case BUTTON_BUILD::Nexus:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Nexus);
		break;
	case BUTTON_BUILD::Observatory:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Observatory);
		break;
	case BUTTON_BUILD::Photon_Cannon:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Photon_Cannon);
		break;
	case BUTTON_BUILD::Pylon:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Pylon);
		break;
	case BUTTON_BUILD::Robotics_Facility:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Robotics_Facility);
		break;
	case BUTTON_BUILD::Robotics_Support_Bay:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Robotics_Support_Bay);
		break;
	case BUTTON_BUILD::Shield_Battery:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Shield_Battery);
		break;
	case BUTTON_BUILD::Stargate:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Stargate);
		break;
	case BUTTON_BUILD::Tempar_Archives:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::Tempar_Archives);
		break;
	case BUTTON_BUILD::END:
		CBuildMgr::Get_Instance()->Set_ShowBuildMouse(BUILD::END);
		break;
	default:
		break;
	}

	Set_ButtonInfo();
}

void CUIButtonMgr::ClickButton(BUTTON_SKILL _eAction)
{



	Set_ButtonInfo();
}

void CUIButtonMgr::ClickButton(BUTTON_UNIT _eUnit)
{
	switch (_eUnit)
	{
	case BUTTON_UNIT::Arbiter:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Arbiter, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Archon:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Archon, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Carrier:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Carrier, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Corsair:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Corsair, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::DarkTemplar:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Dark_Templar, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Dark_Archon:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Dark_Archon, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Dragoon:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Dragon, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::HighTemplar:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::High_Templar, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Interceptor:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Interceptor, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Observer:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Observer, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Probe:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Probe, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Reaver:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Reaver, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Scout:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Scout, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Shuttle:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Shuttle, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::Zealot:
		CUnitMgr::Get_Instance()->Create_Unit(UNIT_NAME::Zealot, (MAPCX >> 1), (MAPCY >> 1), SCENEID::SINGLEPLAY);
		break;
	case BUTTON_UNIT::END:
		break;
	default:
		break;
	}


	Set_ButtonInfo();
}

void CUIButtonMgr::ClickButton(BUTTON_UPGRADE _eAction)
{
	Set_ButtonInfo();
}

void CUIButtonMgr::ClickUp(void)
{
	for (int i = 0; i < 9; ++i) {
		if (!m_stButton[i].empty())
			dynamic_cast<CUIButton*>(m_stButton[i].top())->Set_DrawID(0);
	}
}
