#include "stdafx.h"
#include "UnitMgr.h"
#include "BitmapMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "EditorUI.h"
#include "Mouse.h"
#include "User.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

// Protoss
#include "Probe.h"
#include "Arbiter.h"
#include "Scout.h"
#include "Carrier.h"
#include "Corsair.h"
#include "Zealot.h"
#include "Dragon.h"
#include "High_Templar.h"
#include "Dark_Templar.h"
#include "Reaver.h"
#include "Archon.h"
#include "Dark_Archon.h"

CUnitMgr::CUnitMgr()
{
}

CUnitMgr::~CUnitMgr()
{
}

void CUnitMgr::Initialize(void)
{
	// 좌상단
	m_tRectMove[0].left = 1570;
	m_tRectMove[0].top = 1600;
	m_tRectMove[0].right = 1640;
	m_tRectMove[0].bottom = 1750;

	// 좌하단
	m_tRectMove[1].left = 1570;
	m_tRectMove[1].top = 2350;
	m_tRectMove[1].right = 1700;
	m_tRectMove[1].bottom = 2430;

	// 우하단
	m_tRectMove[2].left = 2580;
	m_tRectMove[2].top = 2300;
	m_tRectMove[2].right = 2660;
	m_tRectMove[2].bottom = 2430;

	// 우상단
	m_tRectMove[3].left = 2500;
	m_tRectMove[3].top = 1600;
	m_tRectMove[3].right = 2660;
	m_tRectMove[3].bottom = 1680;
}

int CUnitMgr::Update(void)
{
	if (SCENEID::EDITOR == CSceneMgr::Get_Instance()->Get_SceneID()) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			RECT rt = CEditorUI::Get_Instance()->Get_Rect();
			POINT pt = CMouse::Get_Instance()->Get_Pos();
			pt.x += CScrollMgr::Get_Instance()->Get_ScrollX();
			pt.y += CScrollMgr::Get_Instance()->Get_ScrollY();

			if ((pt.y - CScrollMgr::Get_Instance()->Get_ScrollY()) < (rt.top - 20)) {
				Create_Unit(CUser::Get_Instance()->Get_BInfo().eUnit, (float)pt.x, (float)pt.y, SCENEID::EDITOR);
			}
		}
	}

	/*for (auto& unit : *CObjMgr::Get_Instance()->Get_ObjList(SCENEID::EDITOR, OBJID::UNIT)) {
		dynamic_cast<CUnit*>(unit)->Move(600, 400);
	}*/

	if (SCENEID::SINGLEPLAY == CSceneMgr::Get_Instance()->Get_SceneID()) {
		list<CObj*> lst = *CObjMgr::Get_Instance()->Get_ObjList(SCENEID::SINGLEPLAY, OBJID::ENEMY);

		for (auto& enemy : lst) {
			POINT pt;
			pt.x = enemy->Get_Info().fX;
			pt.y = enemy->Get_Info().fY;

			// 좌상단
			if (PtInRect(&m_tRectMove[0], pt)) {
				enemy->Set_Dir(DIR::BOTTOM);
			}
			// 좌하단
			else if (PtInRect(&m_tRectMove[1], pt)) {
				enemy->Set_Dir(DIR::RIGHT);
			}
			// 우하단
			else if (PtInRect(&m_tRectMove[2], pt)) {
				enemy->Set_Dir(DIR::TOP);
			}
			// 우상단
			else if (PtInRect(&m_tRectMove[3], pt)) {
				enemy->Set_Dir(DIR::LEFT);
			}
		}
	}
	return 0;
}

void CUnitMgr::Late_Update(void)
{
}

void CUnitMgr::Render(HDC hDC)
{
	float fX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//for (int i = 0; i < 4; ++i)
	//	Rectangle(hDC, m_tRectMove[i].left - fX, m_tRectMove[i].top - fY, m_tRectMove[i].right - fX, m_tRectMove[i].bottom - fY);
}

void CUnitMgr::Release(void)
{
}

void CUnitMgr::Save_UnitInfo(const TCHAR* strFilePath, SCENEID _eID)
{
	list<CObj*> m_lstUnit = *(CObjMgr::Get_Instance()->Get_ObjList(_eID, OBJID::UNIT));

	HANDLE	hFile = CreateFile(strFilePath,	// 파일의 경로 및 이름 명시	
		GENERIC_WRITE,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		CREATE_ALWAYS,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		MessageBox(g_hWnd, _T("SaveFail"), _T("Fail"), MB_OK);
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;

	for (auto& Unit : m_lstUnit)
	{
		// 유닛의 정보 저장 -> 이름만 저장
		WriteFile(hFile, &(dynamic_cast<CUnit*>(Unit)->Get_UnitInfo().eUnitName), sizeof(UNIT_NAME), &dwByte, nullptr);

		// 유닛의 중점에 대한 정보 저장
		WriteFile(hFile, &Unit->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}

	// 파일 소멸
	CloseHandle(hFile);
}

void CUnitMgr::Load_UnitInfo(const TCHAR* strFilePath, SCENEID _eID)
{
	// 인자로 받은 씬의 유닛을 전부 지우고
	list<CObj*> m_lstUnit = *(CObjMgr::Get_Instance()->Get_ObjList(_eID, OBJID::UNIT));
	if (!m_lstUnit.empty()) {
		for (auto& Unit : m_lstUnit) {
			Unit->Release();
		}
		m_lstUnit.clear();
	}

	// 파일에서 유닛을 받아와서 채운다.

	HANDLE	hFile = CreateFile(strFilePath,	// 파일의 경로 및 이름 명시	
		GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		MessageBox(g_hWnd, _T("LoadFail"), _T("Fail"), MB_OK);
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;
	UNIT_NAME	_eUnitName = UNIT_NAME::END;
	INFO		_tInfo{};

	while (true)
	{
		// 유닛의 이름 불러오기
		ReadFile(hFile, &_eUnitName, sizeof(UNIT_NAME), &dwByte, nullptr);

		// 유닛의 중점 불러오기
		ReadFile(hFile, &_tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		// 유닛을 인자로 받은 점을 중점으로, 특정 씬에 생성한다.
		Create_Unit(_eUnitName, _tInfo.fX, _tInfo.fY, _eID);
	}

	// 파일 소멸
	CloseHandle(hFile);
}

void CUnitMgr::Create_Unit(UNIT_NAME _eUnit, float _fX, float _fY, SCENEID _eSceneID)
{
	CSoundMgr::Get_Instance()->StopSound(CHANNELID::Alliance);

	CObj*	pObj = nullptr;
	switch (_eUnit)
	{
	case UNIT_NAME::Probe:
		pObj = new CProbe;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pprrdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Zealot:
		pObj = new CZealot;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pzeRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Dark_Templar:
		pObj = new CDark_Templar;
		CSoundMgr::Get_Instance()->PlaySoundW(L"PDtRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Dragon:
		pObj = new CDragon;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pdrRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Reaver:
		pObj = new CReaver;
		CSoundMgr::Get_Instance()->PlaySoundW(L"ptrrdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Shuttle:
		break;
	case UNIT_NAME::Scout:
		pObj = new CScout;
		CSoundMgr::Get_Instance()->PlaySoundW(L"PScRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Arbiter:
		pObj = new CArbiter;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pabRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Archon:
		pObj = new CArchon;
		CSoundMgr::Get_Instance()->PlaySoundW(L"parRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Dark_Archon:
		pObj = new CDark_Archon;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pdardy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Observer:
		break;
	case UNIT_NAME::Carrier:
		pObj = new CCarrier;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pcardy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::Interceptor:
		break;
	case UNIT_NAME::Corsair:
		pObj = new CCorsair;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pcordy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::High_Templar:
		pObj = new CHigh_Templar;
		CSoundMgr::Get_Instance()->PlaySoundW(L"pteRdy00.wav", CHANNELID::Alliance, UNIT_SOUND);
		break;
	case UNIT_NAME::END:
		pObj = nullptr;
		break;
	default:
		break;
	}

	if (nullptr != pObj) {
		pObj->Set_Pos(_fX, _fY);
		dynamic_cast<CUnit*>(pObj)->Set_DstPos(_fX, _fY);
		pObj->Initialize();
		pObj->Select_Unit_byUser(false);
		CObjMgr::Get_Instance()->Add_Object(_eSceneID, OBJID::UNIT, pObj);
	}
}


void CUnitMgr::Create_EnemyUnit(UNIT_NAME _eUnit, float _fX, float _fY, SCENEID _eSceneID)
{
	CEffectMgr::Get_Instance()->Create_Effect(EFFECT::RECALL, _fX, _fY, 200, 200);

	CObj*	pObj = nullptr;
	switch (_eUnit)
	{
	case UNIT_NAME::Probe:
		pObj = new CProbe;
		break;
	case UNIT_NAME::Zealot:
		pObj = new CZealot;
		break;
	case UNIT_NAME::Dark_Templar:
		pObj = new CDark_Templar;
		break;
	case UNIT_NAME::Dragon:
		pObj = new CDragon;
		break;
	case UNIT_NAME::Reaver:
		pObj = new CReaver;
		break;
	case UNIT_NAME::Shuttle:
		break;
	case UNIT_NAME::Scout:
		pObj = new CScout;
		break;
	case UNIT_NAME::Arbiter:
		pObj = new CArbiter;
		break;
	case UNIT_NAME::Archon:
		pObj = new CArchon;
		break;
	case UNIT_NAME::Dark_Archon:
		pObj = new CDark_Archon;
		break;
	case UNIT_NAME::Observer:
		break;
	case UNIT_NAME::Carrier:
		pObj = new CCarrier;
		break;
	case UNIT_NAME::Interceptor:
		break;
	case UNIT_NAME::Corsair:
		pObj = new CCorsair;
		break;
	case UNIT_NAME::High_Templar:
		pObj = new CHigh_Templar;
		break;
	case UNIT_NAME::END:
		pObj = nullptr;
		break;
	default:
		break;
	}

	if (nullptr != pObj) {
		pObj->Set_Pos(_fX, _fY);
		dynamic_cast<CUnit*>(pObj)->Set_DstPos(-1, -1);
		pObj->Select_Unit_byUser(false);
		pObj->Initialize();
		CObjMgr::Get_Instance()->Add_Object(_eSceneID, OBJID::ENEMY, pObj);
	}
}
