#include "stdafx.h"
#include "Exit.h"
#include "BitmapMgr.h"
#include "BuildMgr.h"
#include "EffectMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "ResourceMgr.h"
#include "SaveLoadMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "UIMgr.h"
#include "UnitMgr.h"
#include "SoundMgr.h"

CExit::CExit()
	: CScene(SCENEID::EXIT)
{
}


CExit::~CExit()
{
}

void CExit::Initialize(void)
{
	DestroyWindow(g_hWnd);
	//CSoundMgr::Get_Instance()->Release();
	//CSceneMgr::Get_Instance()->Release();
}

void CExit::Update(void)
{
}

void CExit::Late_Update(void)
{
}

void CExit::Render(HDC _DC)
{
}

void CExit::Release(void)
{
}

void CExit::Key_Input(void)
{
}
