#include "stdafx.h"
#include "ResourceMgr.h"
#include "BitmapMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "AnimateButton.h"
#include "UnitMgr.h"

CResourceMgr::CResourceMgr()
{
}


CResourceMgr::~CResourceMgr()
{
}

void CResourceMgr::Initialize(void)
{
}

int CResourceMgr::Update(void)
{
	return 0;
}

void CResourceMgr::Late_Update(void)
{
}

void CResourceMgr::Render(HDC hDC)
{
}

void CResourceMgr::Release(void)
{
}

void CResourceMgr::Load_Logo(void)
{
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Logo/back_buffer.bmp", L"Back");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Logo/MainLogo.bmp", L"Logo_Title");
}

void CResourceMgr::Load_All(void)
{

	// 마우스
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Mouse/mouse.bmp", L"Mouse");
	//==============================================================================================================================


	// 메인 선택화면
	//==============================================================================================================================
	// 메인 배경화면
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/MainTitle.bmp", L"Main_Title");

	// 싱글 플레이 관련
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/SinglePlay/singleplay.bmp", L"Main_SinglePlay");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/SinglePlay/singleplay_on.bmp", L"Main_SinglePlay_On");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Button/single_button.bmp", L"Main_SinglePlay_Button");

	// 에디터 관련
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Editor/editor.bmp", L"Main_Editor");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Editor/editor_on.bmp", L"Main_Editor_On");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Button/editor_button.bmp", L"Main_Editor_Button");

	// 나가기 관련
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Exit/exit.bmp", L"Main_Exit");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Exit/exit_on.bmp", L"Main_Exit_On");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/MainTitle/Button/exit_button.bmp", L"Main_Exit_Button");
	//==============================================================================================================================



	// 끝나는 화면
	//==============================================================================================================================
	// 승리시
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/End/Win.bmp", L"Win");
	// 패배시
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/End/Defeat.bmp", L"Lose");
	//==============================================================================================================================


	// 싱글 플레이
	//==============================================================================================================================
	
	// UI 및 맵 관련
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/SinglePlay/Main_Map.bmp", L"Single_Map");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/SinglePlay/Mini_Map.bmp", L"Single_Mini_Map");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/SinglePlay/MainUI.bmp", L"MainUI");

	// 프로토스 관련

	// 건물 관련
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Arbiter_Tribunal.bmp", L"Arbiter_Tribunal");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Assimilator.bmp", L"Assimilator");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Citadel_of_Adun.bmp", L"Citadel_of_Adun");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Cybernetics_Core.bmp", L"Cybernetics_Core");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Fleet_Beacon.bmp", L"Fleet_Beacon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Forge.bmp", L"Forge");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Gateway.bmp", L"Gateway");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Nexus.bmp", L"Nexus");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Observatory.bmp", L"Observatory");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Photon_Cannon.bmp", L"Photon_Cannon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Pylon.bmp", L"Pylon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Robotics_Facility.bmp", L"Robotics_Facility");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Robotics_Support_Bay.bmp", L"Robotics_Support_Bay");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Shield_Battery.bmp", L"Shield_Battery");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Stargate.bmp", L"Stargate");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Tempar_Archives.bmp", L"Tempar_Archives");

	// 건물 지을 때 판별하는 초록/빨간색 사각형
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Check_Impossible.bmp", L"BuildCheck_impossible");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Check_Possible.bmp", L"BuildCheck_possible");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Check_Good.bmp", L"BuildCheck_Good");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Check_Bad.bmp", L"BuildCheck_Bad");

	// 알파블렌드를 위한 흰 배경
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/Alpha.bmp", L"Alpha");

	// 건물을 짓는 동안 나오는 이미지
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Building/createBuild.bmp", L"createBuild");

	// 건물 완성 후 나오는 이미지
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Arbiter_Tribunal.bmp", L"Create_Arbiter_Tribunal");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Assimilator.bmp", L"Create_Assimilator");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Citadel_of_Adun.bmp", L"Create_Citadel_of_Adun");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Cybernetics_Core.bmp", L"Create_Cybernetics_Core");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Fleet_Beacon.bmp", L"Create_Fleet_Beacon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Forge.bmp", L"Create_Forge");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Gateway.bmp", L"Create_Gateway");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Nexus.bmp", L"Create_Nexus");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Observatory.bmp", L"Create_Observatory");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Photon_Cannon.bmp", L"Create_Photon_Cannon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Pylon.bmp", L"Create_Pylon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Robotics_Facility.bmp", L"Create_Robotics_Facility");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Robotics_Support_Bay.bmp", L"Create_Robotics_Support_Bay");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Shield_Battery.bmp", L"Create_Shield_Battery");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Stargate.bmp", L"Create_Stargate");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/BuildTime/Tempar_Archives.bmp", L"Create_Tempar_Archives");
	

	// 에디터
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/back_ui.bmp", L"Editor_UI");
	
	// 에디터용 작은 타일 관련
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/TileIcon/2.bmp", L"Editor_Tile_Dirt");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/TileIcon/1.bmp", L"Editor_Tile_Water");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/TileIcon/0.bmp", L"Editor_Tile_Creep");

	// 에디터용 유닛 작은 타일 관련

	// 유닛 - 지상
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/0.bmp", L"Editor_Unit_Probe");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/1.bmp", L"Editor_Unit_Zealot");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/2.bmp", L"Editor_Unit_Dragon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/3.bmp", L"Editor_Unit_HighTemplar");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/4.bmp", L"Editor_Unit_Archon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/5.bmp", L"Editor_Unit_DarkTemplar");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/6.bmp", L"Editor_Unit_Reaver");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Ground/7.bmp", L"Editor_Unit_DarkArchon");

	// 유닛 - 공중
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/0.bmp", L"Editor_Unit_Shuttle");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/1.bmp", L"Editor_Unit_Scout");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/2.bmp", L"Editor_Unit_Arbiter");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/3.bmp", L"Editor_Unit_Carrier");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/4.bmp", L"Editor_Unit_Intersepter");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/5.bmp", L"Editor_Unit_Observer");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Air/6.bmp", L"Editor_Unit_Corsair");

	// 건물
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build00.bmp", L"Editor_Build_Nexus");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build01.bmp", L"Editor_Build_Robotics_Facility");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build02.bmp", L"Editor_Build_Pylon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build03.bmp", L"Editor_Build_Assimilator");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build04.bmp", L"Editor_Build_Observatory");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build05.bmp", L"Editor_Build_Gateway");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build06.bmp", L"Editor_Build_Photon_Cannon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build07.bmp", L"Editor_Build_Citadel_of_Adun");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build08.bmp", L"Editor_Build_Cybernetics_Core");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build09.bmp", L"Editor_Build_Tempar_Archives");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build10.bmp", L"Editor_Build_Forge");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build11.bmp", L"Editor_Build_Stargate");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build12.bmp", L"Editor_Build_Fleet_Beacon");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build13.bmp", L"Editor_Build_Arbiter_Tribunal");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build14.bmp", L"Editor_Build_Robotics_Support_Bay");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Editor/CmdIcon/P_Build/Build15.bmp", L"Editor_Build_Shield_Battery");

	// 일반 타일 관련
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Tile/dirt.bmp", L"Tile_Dirt");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Tile/water.bmp", L"Tile_Water");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Tile/creep.bmp", L"Tile_Creep");
	//==============================================================================================================================


	// 유닛 관련 리소스 업로드
	//============================================================================================================================== 

	// 버튼 관련 리소스
	//============================================================================================================================== 
	// 유닛 액션
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Button/Action.bmp", L"Action");
	// 유닛 모습
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Button/Unit.bmp", L"Unit");
	// 스킬
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Button/Skill.bmp", L"Skill");
	// 업그레이드
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Button/Upgrade.bmp", L"Upgrade");
	// 건물
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Button/Build.bmp", L"Build");
	//============================================================================================================================== 

	// 유닛 와이어
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire00.bmp", L"Unit_Wire00");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire01.bmp", L"Unit_Wire01");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire02.bmp", L"Unit_Wire02");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire03.bmp", L"Unit_Wire03");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire04.bmp", L"Unit_Wire04");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire05.bmp", L"Unit_Wire05");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire06.bmp", L"Unit_Wire06");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire07.bmp", L"Unit_Wire07");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire08.bmp", L"Unit_Wire08");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Wire/Wire09.bmp", L"Unit_Wire09");

	// 유닛 체력/쉴드 마나 스탯창
	// FrameBar
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_0.bmp", L"Unit_Frame00");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_1.bmp", L"Unit_Frame01");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_2.bmp", L"Unit_Frame02");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_3.bmp", L"Unit_Frame03");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_4.bmp", L"Unit_Frame04");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_5.bmp", L"Unit_Frame05");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_6.bmp", L"Unit_Frame06");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_7.bmp", L"Unit_Frame07");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarFrame/Frame_8.bmp", L"Unit_Frame08");

	// HpBar
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_0.bmp", L"Unit_Hp00");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_1.bmp", L"Unit_Hp01");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_2.bmp", L"Unit_Hp02");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_3.bmp", L"Unit_Hp03");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_4.bmp", L"Unit_Hp04");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_5.bmp", L"Unit_Hp05");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_6.bmp", L"Unit_Hp06");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_7.bmp", L"Unit_Hp07");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarHp/Hpbar_8.bmp", L"Unit_Hp08");

	// ShieldBar
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_0.bmp", L"Unit_Shield00");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_1.bmp", L"Unit_Shield01");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_2.bmp", L"Unit_Shield02");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_3.bmp", L"Unit_Shield03");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_4.bmp", L"Unit_Shield04");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_5.bmp", L"Unit_Shield05");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_6.bmp", L"Unit_Shield06");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_7.bmp", L"Unit_Shield07");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Bar/BarShield/Shield_8.bmp", L"Unit_Shield08");
	//=============================================================================================================================== 







	// 프로토스 유닛 리소스
	//==============================================================================================================================
	// Probe
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Probe/probe_WireTrans.bmp", L"Unit_Probe_WireTrans");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Probe/probe_move.bmp", L"Unit_Probe_Move");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Probe/Probe_Reset.bmp", L"Probe_Reset");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Probe/Probe_Plg.bmp", L"Probe_Plg");
	//==============================================================================================================================
	// Arbiter
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Arbiter/Arbiter_move.bmp", L"Unit_Arbiter_move");
	//==============================================================================================================================
	// Scout
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Scout/Scout_move.bmp", L"Unit_Scout_move");
	//==============================================================================================================================
	// Corsair
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Carrier/Carrier_move.bmp", L"Unit_Carrier_move");
	//==============================================================================================================================
	// Carrier
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Corsair/Corsair_move.bmp", L"Unit_Corsair_move");
	//==============================================================================================================================
	// Zealot
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Zealot/Zealot_move.bmp", L"Unit_Zealot_move");
	////==============================================================================================================================
	// Dragon
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Dragon/Dragon_move.bmp", L"Unit_Dragon_move");
	//==============================================================================================================================
	// High_Templar
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/High_Templar/High_Templar_move.bmp", L"Unit_High_Templar_move");
	//==============================================================================================================================
	// Dark_Templar
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Dark_Templar/Dark_Templar_move.bmp", L"Unit_Dark_Templar_move");
	//==============================================================================================================================
	// Reaver
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Reaver/Reaver_move.bmp", L"Unit_Reaver_move");
	//==============================================================================================================================
	// Archon
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Archon/Archon_move.bmp", L"Unit_Archon_move");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Archon/Archon_body.bmp", L"Unit_Archon_body");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Archon/Archon_aulora.bmp", L"Unit_Archon_aulora");
	//==============================================================================================================================
	// Dark_Archon
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Dark_Archon/Dark_Archon_move.bmp", L"Unit_Dark_Archon_move");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Dark_Archon/Dark_Archon_body.bmp", L"Unit_Dark_Archon_body");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/ProtossUnit/Dark_Archon/Dark_Archon_aulora.bmp", L"Unit_Dark_Archon_aulora");
	//==============================================================================================================================


	// Status
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status00.bmp", L"Unit_Probe_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status01.bmp", L"Unit_Interceptor_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status02.bmp", L"Unit_Observer_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status03.bmp", L"Unit_Zealot_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status04.bmp", L"Unit_Dragon_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status05.bmp", L"Unit_Reaver_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status06.bmp", L"Unit_High_Templar_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status07.bmp", L"Unit_Shuttle_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status08.bmp", L"Unit_Scout_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status09.bmp", L"Unit_Corsair_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status10.bmp", L"Unit_Archon_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status11.bmp", L"Unit_DarkArchon_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status12.bmp", L"Unit_Arbiter_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status13.bmp", L"Unit_Carrier_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status14.bmp", L"Unit_Dark_Templar_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status15.bmp", L"Build_Nexus_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status16.bmp", L"Build_Pylon_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status17.bmp", L"Build_Assimilator_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status18.bmp", L"Build_Gateway_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status19.bmp", L"Build_Forge_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status20.bmp", L"Build_Photon_Cannon_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status21.bmp", L"Build_Cybernetics_Core_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status22.bmp", L"Build_Shield_Battery_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status23.bmp", L"Build_Robotics_Facility_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status24.bmp", L"Build_Stargate_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status25.bmp", L"Build_Citadel_of_Adun_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status26.bmp", L"Build_Robotics_Support_Bay_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status27.bmp", L"Build_Fleet_Beacon_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status28.bmp", L"Build_Tempar_Archives_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status29.bmp", L"Build_Observatory_Status");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Status/Status30.bmp", L"Build_Arbiter_Tribunal_Status");


	// SmallWireFrame
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame00.bmp", L"Unit_Zealot_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame01.bmp", L"Unit_Dragon_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame02.bmp", L"Unit_High_Templar_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame03.bmp", L"Unit_Archon_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame04.bmp", L"Unit_Dark_Templar_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame05.bmp", L"Unit_Dark_Archon_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame06.bmp", L"Unit_Reaver_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame07.bmp", L"Unit_Shuttle_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame08.bmp", L"Unit_Observer_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame09.bmp", L"Unit_Scout_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame10.bmp", L"Unit_Carrier_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame11.bmp", L"Unit_Interceptor_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame12.bmp", L"Unit_Corsair_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame13.bmp", L"Unit_Arbiter_WireSmall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/SmallWireFrame/SmallWireFrame14.bmp", L"Unit_Probe_WireSmall");


	// BigWireFrame
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame00.bmp", L"Unit_Probe_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame01.bmp", L"Unit_Zealot_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame02.bmp", L"Unit_Dragon_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame03.bmp", L"Unit_High_Templar_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame04.bmp", L"Unit_Archon_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame05.bmp", L"Unit_Dark_Templar_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame06.bmp", L"Unit_Dark_Archon_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame07.bmp", L"Unit_Reaver_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame08.bmp", L"Unit_Shuttle_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame09.bmp", L"Unit_Observer_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame10.bmp", L"Unit_Scout_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame11.bmp", L"Unit_Carrier_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame12.bmp", L"Unit_Interceptor_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame13.bmp", L"Unit_Corsair_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame14.bmp", L"Unit_Arbiter_WireBig");
																				   
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame15.bmp", L"Build_Nexus_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame18.bmp", L"Build_Assimilator_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame17.bmp", L"Build_Pylon_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame20.bmp", L"Build_Gateway_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame25.bmp", L"Build_Forge_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame21.bmp", L"Build_Photon_Cannon_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame23.bmp", L"Build_Cybernetics_Core_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame30.bmp", L"Build_Shield_Battery_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame16.bmp", L"Build_Robotics_Facility_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame26.bmp", L"Build_Stargate_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame22.bmp", L"Build_Citadel_of_Adun_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame29.bmp", L"Build_Robotics_Support_Bay_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame27.bmp", L"Build_Fleet_Beacon_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame24.bmp", L"Build_Tempar_Archives_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame19.bmp", L"Build_Observatory_WireBig");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/BigWireFrame/BigWireFrame28.bmp", L"Build_Arbiter_Tribunal_WireBig");


	// Portrait
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait00.bmp", L"Unit_Arbiter_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait01.bmp", L"Unit_Archon_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait02.bmp", L"Unit_Carrier_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait03.bmp", L"Unit_Corsair_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait04.bmp", L"Unit_Dark_Archon_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait05.bmp", L"Unit_Dark_Templar_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait06.bmp", L"Unit_Dragon_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait07.bmp", L"Unit_High_Templar_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait08.bmp", L"Unit_Interceptor_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait09.bmp", L"Unit_Observer_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait10.bmp", L"Unit_Zealot_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait11.bmp", L"Unit_Probe_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait12.bmp", L"Unit_Reaver_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait13.bmp", L"Unit_Scout_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait14.bmp", L"Unit_Shuttle_Portrait");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Unit/Portrait/Portrait15.bmp", L"Unit_Aldaris_Portrait");



	// 총알 및 이펙트 관련
	//==============================================================================================================================
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Bullet.bmp", L"Bullet");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Scarab/Scarab.bmp", L"Scarab");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Scarab/Scarab_move.bmp", L"Scarab_move");


	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Scarab/Scarab_Explosion.bmp", L"Scarab_Explosion");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/BulletExplosion.bmp", L"BulletExplosion");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Corsair_Splash.bmp", L"Corsair_Splash");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Frozen.bmp", L"Frozen");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/MindControl.bmp", L"MindControl");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Recall.bmp", L"Recall");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Stasis.bmp", L"Stasis");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Storm.bmp", L"Storm");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Scout_Ground.bmp", L"Scout_Ground");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Explosion_Big.bmp", L"Explosion_Big");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Explosion_Middle.bmp", L"Explosion_Middle");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Explosion_Small.bmp", L"Explosion_Small");

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/DarkArchon_Dead.bmp", L"DarkArchon_Dead");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/DarkTemplar_Dead.bmp", L"DarkTemplar_Dead");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/HighTemplar_Dead.bmp", L"HighTemplar_Dead");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Zealot_Dead.bmp", L"Zealot_Dead");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/Effect/Dragon_Dead.bmp", L"Dragon_Dead");



}
