#include "stdafx.h"
#include "BuildMgr.h"
#include "BitmapMgr.h"
#include "Build.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "EditorUI.h"
#include "User.h"

#define BUILD_STANDARD 30

CBuildMgr::CBuildMgr()
{
}


CBuildMgr::~CBuildMgr()
{
}

void CBuildMgr::Initialize(void)
{
	ZeroMemory(m_tBuildInfoArr, sizeof(BuildInfo) * (int)BUILD::END);

	// 건물 DC 가져오기
	m_ArrDC[(int)BUILD::Arbiter_Tribunal] = CBitmapMgr::Get_Instance()->Find_Image(L"Arbiter_Tribunal");
	m_ArrDC[(int)BUILD::Assimilator] = CBitmapMgr::Get_Instance()->Find_Image(L"Assimilator");
	m_ArrDC[(int)BUILD::Citadel_of_Adun] = CBitmapMgr::Get_Instance()->Find_Image(L"Citadel_of_Adun");
	m_ArrDC[(int)BUILD::Cybernetics_Core] = CBitmapMgr::Get_Instance()->Find_Image(L"Cybernetics_Core");
	m_ArrDC[(int)BUILD::Fleet_Beacon] = CBitmapMgr::Get_Instance()->Find_Image(L"Fleet_Beacon");
	m_ArrDC[(int)BUILD::Forge] = CBitmapMgr::Get_Instance()->Find_Image(L"Forge");
	m_ArrDC[(int)BUILD::Gateway] = CBitmapMgr::Get_Instance()->Find_Image(L"Gateway");
	m_ArrDC[(int)BUILD::Nexus] = CBitmapMgr::Get_Instance()->Find_Image(L"Nexus");
	m_ArrDC[(int)BUILD::Observatory] = CBitmapMgr::Get_Instance()->Find_Image(L"Observatory");
	m_ArrDC[(int)BUILD::Photon_Cannon] = CBitmapMgr::Get_Instance()->Find_Image(L"Photon_Cannon");
	m_ArrDC[(int)BUILD::Pylon] = CBitmapMgr::Get_Instance()->Find_Image(L"Pylon");
	m_ArrDC[(int)BUILD::Robotics_Facility] = CBitmapMgr::Get_Instance()->Find_Image(L"Robotics_Facility");
	m_ArrDC[(int)BUILD::Robotics_Support_Bay] = CBitmapMgr::Get_Instance()->Find_Image(L"Robotics_Support_Bay");
	m_ArrDC[(int)BUILD::Shield_Battery] = CBitmapMgr::Get_Instance()->Find_Image(L"Shield_Battery");
	m_ArrDC[(int)BUILD::Stargate] = CBitmapMgr::Get_Instance()->Find_Image(L"Stargate");
	m_ArrDC[(int)BUILD::Tempar_Archives] = CBitmapMgr::Get_Instance()->Find_Image(L"Tempar_Archives");

	// 건물 create_After_DC 가져오기
	m_ArrCreate_AfterDC[(int)BUILD::Arbiter_Tribunal] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Arbiter_Tribunal");
	m_ArrCreate_AfterDC[(int)BUILD::Assimilator] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Assimilator");
	m_ArrCreate_AfterDC[(int)BUILD::Citadel_of_Adun] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Citadel_of_Adun");
	m_ArrCreate_AfterDC[(int)BUILD::Cybernetics_Core] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Cybernetics_Core");
	m_ArrCreate_AfterDC[(int)BUILD::Fleet_Beacon] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Fleet_Beacon");
	m_ArrCreate_AfterDC[(int)BUILD::Forge] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Forge");
	m_ArrCreate_AfterDC[(int)BUILD::Gateway] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Gateway");
	m_ArrCreate_AfterDC[(int)BUILD::Nexus] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Nexus");
	m_ArrCreate_AfterDC[(int)BUILD::Observatory] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Observatory");
	m_ArrCreate_AfterDC[(int)BUILD::Photon_Cannon] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Photon_Cannon");
	m_ArrCreate_AfterDC[(int)BUILD::Pylon] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Pylon");
	m_ArrCreate_AfterDC[(int)BUILD::Robotics_Facility] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Robotics_Facility");
	m_ArrCreate_AfterDC[(int)BUILD::Robotics_Support_Bay] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Robotics_Support_Bay");
	m_ArrCreate_AfterDC[(int)BUILD::Shield_Battery] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Shield_Battery");
	m_ArrCreate_AfterDC[(int)BUILD::Stargate] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Stargate");
	m_ArrCreate_AfterDC[(int)BUILD::Tempar_Archives] = CBitmapMgr::Get_Instance()->Find_Image(L"Create_Tempar_Archives");

	// 건물 정보 초기화
	for (int i = 0; i < (int)BUILD::END; ++i) {
		Init_BuildInfo((BUILD)i);
	}

	m_eCurrShowBuild = BUILD::END;

	m_bValid = true;
	m_ValidDC = CBitmapMgr::Get_Instance()->Find_Image(L"BuildCheck_Good");
	m_InValidDC = CBitmapMgr::Get_Instance()->Find_Image(L"BuildCheck_Bad");
	m_AlphaDC = CBitmapMgr::Get_Instance()->Find_Image(L"Alpha");
}

int CBuildMgr::Update(void)
{
	CBuild* pObj = nullptr;

	// 싱글 플레이일 경우
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::SINGLEPLAY) {

		// 현재 선택된 건물이 존재할 경우
		if (m_eCurrShowBuild != BUILD::END) {
			// 중점 업데이트
			POINT pt = CMouse::Get_Instance()->Get_Pos();
			m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fX = pt.x;
			m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fY = pt.y;

			m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tRect.left = LONG(m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fX - (m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fCX / 2.f));
			m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tRect.top = LONG(m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fY - (m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fCY / 2.f));
			m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tRect.right = LONG(m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fX + (m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fCX / 2.f));
			m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tRect.bottom = LONG(m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fY + (m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fCY / 2.f));
		}
	}

	// 에디터 일 경우
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::EDITOR) {

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL)) {
			if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
				RECT rt = CEditorUI::Get_Instance()->Get_Rect();
				POINT pt = CMouse::Get_Instance()->Get_Pos();
				pt.x += CScrollMgr::Get_Instance()->Get_ScrollX();
				pt.y += CScrollMgr::Get_Instance()->Get_ScrollY();

				if ((pt.y - CScrollMgr::Get_Instance()->Get_ScrollY()) < (rt.top - 20)) {
					create_Build(CUser::Get_Instance()->Get_BInfo().eBuild, (float)pt.x, (float)pt.y, SCENEID::EDITOR);
				}

				CMouse::Get_Instance()->Set_LbuttonDown();
			}
		}
	}


	return 0;
}

void CBuildMgr::Late_Update(void)
{
}

void CBuildMgr::Render(HDC hDC)
{
	if (m_eCurrShowBuild == BUILD::END)
		return;

	// 01. 배경을 AlphaDC에 복사
	// ===============================================================
	// 건물이 그려지기에 유효한 위치에 마우스가 있을 경우
	if (m_bValid) {
		TransparentBlt(
			m_AlphaDC,
			0, 0,
			m_tBuildInfoArr[(int)m_eCurrShowBuild].iWidth,
			m_tBuildInfoArr[(int)m_eCurrShowBuild].iHeight,
			m_ValidDC,
			0, 0, 300, 300,
			RGB(255, 255, 255)
		);
	}
	// 건물이 그려지기에 유효하지 않은 위치에 마우스가 있을 경우
	else {
		TransparentBlt(
			m_AlphaDC,
			0, 0,
			m_tBuildInfoArr[(int)m_eCurrShowBuild].iWidth,
			m_tBuildInfoArr[(int)m_eCurrShowBuild].iHeight,
			m_InValidDC,
			0, 0, 300, 300,
			RGB(255, 255, 255)
		);
	}
	// ===============================================================

	// 02. 배경 위에 그릴 건물 복사
	// ===============================================================
	TransparentBlt(
		m_AlphaDC,
		0, 0,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].iWidth,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].iHeight,
		
		m_ArrDC[(int)m_eCurrShowBuild],
		(m_tBuildInfoArr[(int)m_eCurrShowBuild].iWidth - m_tBuildInfoArr[(int)m_eCurrShowBuild].iRealWidth) * 0.5,
		(m_tBuildInfoArr[(int)m_eCurrShowBuild].iHeight - m_tBuildInfoArr[(int)m_eCurrShowBuild].iRealHeight) * 0.5,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].iRealWidth,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].iRealHeight,
		RGB(255, 255, 255)
	);
	// ===============================================================

	// 03. 백버퍼에 완성된 알파블랜드 DC를 보냄
	// ===============================================================
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 50;
	bf.AlphaFormat = 0;
	POINT pt = CMouse::Get_Instance()->Get_Pos();
	AlphaBlend(
		hDC,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tRect.left,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tRect.top,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fCX,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].m_tInfo.fCX,
		m_AlphaDC,
		0, 0,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].iWidth,
		m_tBuildInfoArr[(int)m_eCurrShowBuild].iHeight,
		bf);
	// ===============================================================
}

void CBuildMgr::Release(void)
{
}

void CBuildMgr::create_Build(BUILD _eBuild, SCENEID _eSceneID)
{
	CBuild* pObj = nullptr;
	pObj = new CBuild(m_tBuildInfoArr[(int)_eBuild]);
	
	POINT pt = CMouse::Get_Instance()->Get_Pos();
	pt.x += CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y += CScrollMgr::Get_Instance()->Get_ScrollY();

	pObj->Set_Pos(pt);
	pObj->Set_Size(80, 100);
	pObj->Select_Unit_byUser(false);

	pObj->Initialize();
	pObj->Update();
	CObjMgr::Get_Instance()->Add_Object(_eSceneID, OBJID::BUILD, pObj);
}

void CBuildMgr::create_Build(BUILD _eBuild, float _fX, float _fY, SCENEID _eSceneID)
{
	CBuild* pObj = nullptr;
	pObj = new CBuild(m_tBuildInfoArr[(int)_eBuild]);
	pObj->Set_Pos(_fX, _fY);
	pObj->Select_Unit_byUser(false);
	pObj->Initialize();

	CObjMgr::Get_Instance()->Add_Object(_eSceneID, OBJID::BUILD, pObj);
}

void CBuildMgr::create_Build(BUILD _eBuild, POINT pt, SCENEID _eSceneID)
{
	create_Build(_eBuild, pt.x, pt.y, _eSceneID);
}

void CBuildMgr::Set_BuildInfo(BUILD _eBuild, int _iWidth, int _iHeight)
{
	m_tBuildInfoArr[(int)_eBuild].m_eBuild = _eBuild;
	m_tBuildInfoArr[(int)_eBuild].m_DC = m_ArrDC[(int)_eBuild];
	m_tBuildInfoArr[(int)_eBuild].m_Create_AfterDC = m_ArrCreate_AfterDC[(int)_eBuild];

	m_tBuildInfoArr[(int)_eBuild].iWidth = _iWidth;
	m_tBuildInfoArr[(int)_eBuild].iHeight = _iHeight;
}

void CBuildMgr::Init_BuildInfo(BUILD _eBuild)
{
	switch (_eBuild)
	{
	case BUILD::Arbiter_Tribunal:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 200;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 150;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 60000;	// 60초

		// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 500;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 500;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 96;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 90;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 96, 128);
	}
	break;

	case BUILD::Assimilator:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 100;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 40000;	// 40초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 450;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 450;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 450;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 450;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 4;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 130;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 124;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 192, 192);
	}
	break;

	case BUILD::Citadel_of_Adun:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 100;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 60000;	// 60초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 450;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 450;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 450;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 450;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 100;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 104;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 160, 128);
	}
	break;

	case BUILD::Cybernetics_Core:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 200;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 60000;	// 60초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 500;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 500;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 90;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 110;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 96, 128);
	}
	break;

	case BUILD::Fleet_Beacon:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 300;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 200;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 60000;	// 60초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 500;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 500;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 132;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 108;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 192, 160);
	}
	break;

	case BUILD::Forge:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 45000;	// 45초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 550;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 550;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 550;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 550;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 120;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 110;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 160, 128);
	}
	break;

	case BUILD::Gateway:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 60000;	// 60초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 500;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 500;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 4;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 3;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 128;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 122;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 128, 160);
	}
	break;

	case BUILD::Nexus:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 400;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 120000;	// 120초

		// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 750;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 750;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 750;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 750;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 4;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 3;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 150;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 158;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 192, 224); 
	}
	break;

	case BUILD::Observatory:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 50;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 100;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 30000;	// 30초

		// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 250;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 250;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 250;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 250;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 96;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 98;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 96, 128);
	}
	break;

	case BUILD::Photon_Cannon:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 50000;	// 50초

		// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 100;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 100;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 100;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 100;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 2;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 64;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 102;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 64, 128);
	}
	break;

	case BUILD::Pylon:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 100;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 30000;	// 30초

		// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 300;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 300;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 300;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 300;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 2;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 58;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 64;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 64, 64);
	}
	break;

	case BUILD::Robotics_Facility:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 200;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 200;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 80000;	// 80초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 500;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 500;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 96;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 116;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 96, 128);
	}
	break;

	case BUILD::Robotics_Support_Bay:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 100;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 30000;	// 30초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 450;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 450;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 450;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 450;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 92;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 108;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 160, 128);
	}
	break;

	case BUILD::Shield_Battery:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 100;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 0;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 30000;	// 30초

		// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 200;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 200;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 200;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 200;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 88;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 62;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 96, 64);
	}
	break;

	case BUILD::Stargate:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 150;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 70000;	// 70초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 600;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 600;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 600;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 600;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 4;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 3;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 124;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 136;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 128, 160);
	}
	break;

	case BUILD::Tempar_Archives:
	{
		// 생성 cost
		m_tBuildInfoArr[(int)_eBuild].m_iCostMineral = 150;
		m_tBuildInfoArr[(int)_eBuild].m_iCostGas = 200;

		// 생성 속도
		m_tBuildInfoArr[(int)_eBuild].m_dwBuildTime = 60000;	// 60초

																// 최대 체력
		m_tBuildInfoArr[(int)_eBuild].m_iMaxHP = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iHP = 500;

		// 최대 쉴드
		m_tBuildInfoArr[(int)_eBuild].m_iMaxSheild = 500;
		m_tBuildInfoArr[(int)_eBuild].m_iSheild = 500;

		// 이미지가 인게임에서 그려지는 정보
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCX = BUILD_STANDARD * 3;
		m_tBuildInfoArr[(int)_eBuild].m_tInfo.fCY = BUILD_STANDARD * 2;

		// 실제 이미지의 실제 판정정보
		m_tBuildInfoArr[(int)_eBuild].iRealWidth = 126;
		m_tBuildInfoArr[(int)_eBuild].iRealHeight = 144;

		// 이미지의 정보
		Set_BuildInfo(_eBuild, 160, 192);
	}
	break;

	case BUILD::END:
		break;
	default:
		break;
	}
}

void CBuildMgr::Set_ShowBuildMouse(BUILD _eBuild)
{
	// 마우스를 따라다니며 보이는 건물의 정보를 설정
	m_eCurrShowBuild = _eBuild;
}
