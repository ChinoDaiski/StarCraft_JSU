#include "stdafx.h"
#include "EffectMgr.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "BitmapMgr.h"

CEffectMgr::CEffectMgr()
{
}


CEffectMgr::~CEffectMgr()
{
}

void CEffectMgr::Initialize(void)
{
	for (int i = 0; i < (int)EFFECT::END; ++i) {
		Init_Effect_Frame_Info(EFFECT(i));
	}
}

int CEffectMgr::Update(void)
{
	return 0;
}

void CEffectMgr::Late_Update(void)
{
}

void CEffectMgr::Render(HDC hDC)
{
}

void CEffectMgr::Release(void)
{
}

void CEffectMgr::Show_DeadEffect(UNIT_NAME _eName, int _fX, int _fY)
{

}

void CEffectMgr::Create_Effect(EFFECT _eEffect, int _fX, int _fY, int _fCX, int _fCY)
{
	INFO info;
	info.fX = _fX;
	info.fY = _fY;
	info.fCX = _fCX;
	info.fCY = _fCY;

	CObj* pObj = new CEffect;
	pObj->Initialize();
	pObj->Set_Info(info);
	dynamic_cast<CEffect*>(pObj)->Set_EffectInfo(m_EffectDC[(int)_eEffect], m_tEffectFrame[(int)_eEffect]);

	CObjMgr::Get_Instance()->Add_Object(SCENEID::SINGLEPLAY, OBJID::EFFECT, pObj);
}

void CEffectMgr::Show_Create_After_Effect(CREATE_AFTER _eEffect, int _fX, int _fY)
{

}

void CEffectMgr::Init_Effect_Frame_Info(EFFECT _eEffect)
{
	switch (_eEffect)
	{
	case EFFECT::BALL:
		break;
	case EFFECT::BALL_EXPLO:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 14, 30, 40, 40);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"BulletExplosion");
		break;
	case EFFECT::SCARAB:
		break;
	case EFFECT::SCARAB_EXPLO:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 10, 50, 80, 80);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Scarab_Explosion");
		break;
	case EFFECT::SCARAB_MOVE:
		break;
	case EFFECT::SCOUT_AIR:
		break;
	case EFFECT::SCOUT_GROUND:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 8, 60, 40, 40);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Scout_Ground");
		CSoundMgr::Get_Instance()->PlaySoundW(L"blastgn2.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::SHOCKBALL:
		break;
	case EFFECT::SHOCKWAVE:
		break;
	case EFFECT::CORSAIR_SPLASH:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 7, 50, 64, 64);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Corsair_Splash");
		CSoundMgr::Get_Instance()->PlaySoundW(L"pcorlasr1.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::WEB:
		break;
	case EFFECT::INTERCEP_EXPLO:
		break;
	case EFFECT::INTERCEP_BULLET:
		break;
	case EFFECT::FROZEN:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 13, 60, 80, 80);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Frozen");
		break;
	case EFFECT::RECALL:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 19, 50, 100, 100);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Recall");
		break;
	case EFFECT::STASIS:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 9, 30, 128, 128);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Stasis");
		break;
	case EFFECT::HALLUCI:
		break;
	case EFFECT::STORM:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 14, 80, 224, 224); 
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Storm");
		CSoundMgr::Get_Instance()->PlaySoundW(L"PTeSto00.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::FEEDBACK:
		break;
	case EFFECT::MAELSTORM:
		break;
	case EFFECT::MINDCONTROL:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 20, 30, 64, 64);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"MindControl");
		CSoundMgr::Get_Instance()->PlaySoundW(L"mind.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::PROBE_ATTACK:
		break;
	case EFFECT::EXPLOSION_L:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 14, 100, 252, 200);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Explosion_Big");
		CSoundMgr::Get_Instance()->PlaySoundW(L"explo5.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::EXPLOSION_M:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 10, 100, 200, 200);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Explosion_Middle");
		CSoundMgr::Get_Instance()->PlaySoundW(L"explo4.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::EXPLOSION_S:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 9, 100, 128, 128);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Explosion_Small");
		CSoundMgr::Get_Instance()->PlaySoundW(L"explo3.wav", CHANNELID::EFFECT, UNIT_SOUND);
		break;
	case EFFECT::CREATE_BUILD:
		break;
	case EFFECT::VESTIGE:
		break;
	case EFFECT::DARK_TEMPLAR_DEAD:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 7, 100, 128, 128);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"DarkTemplar_Dead");
		break;
	case EFFECT::HIGH_TEMPLAR_DEAD:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 7, 100, 128, 128);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"HighTemplar_Dead");
		break;
	case EFFECT::ARCHON_DEAD:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 7, 100, 128, 128);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Zealot_Dead");
		break;
	case EFFECT::DARK_ARCHON_DEAD:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 15, 100, 120, 120);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"DarkArchon_Dead");
		break;
	case EFFECT::ZEALOT_DEAD:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 7, 100, 128, 128);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Zealot_Dead");
		break;
	case EFFECT::DRAGON_DEAD:
		Set_FrameInfo(m_tEffectFrame[(int)_eEffect], 7, 100, 96, 96);
		m_EffectDC[(int)_eEffect] = CBitmapMgr::Get_Instance()->Find_Image(L"Dragon_Dead");
		break;
	case EFFECT::END:
		break;
	default:
		break;
	}

}

void CEffectMgr::Init_Create_After_Frame_Info(CREATE_AFTER _eEffect)
{
	switch (_eEffect)
	{
	case CREATE_AFTER::Arbiter_Tribunal:
		break;
	case CREATE_AFTER::Assimilator:
		break;
	case CREATE_AFTER::Citadel_of_Adun:
		break;
	case CREATE_AFTER::Cybernetics_Core:
		break;
	case CREATE_AFTER::Fleet_Beacon:
		break;
	case CREATE_AFTER::Forge:
		break;
	case CREATE_AFTER::Gateway:
		break;
	case CREATE_AFTER::Nexus:
		break;
	case CREATE_AFTER::Observatory:
		break;
	case CREATE_AFTER::Photon_Cannon:
		break;
	case CREATE_AFTER::Pylon:
		break;
	case CREATE_AFTER::Robotics_Facility:
		break;
	case CREATE_AFTER::Robotics_Support_Bay:
		break;
	case CREATE_AFTER::Shield_Battery:
		break;
	case CREATE_AFTER::Stargate:
		break;
	case CREATE_AFTER::Tempar_Archives:
		break;
	case CREATE_AFTER::END:
		break;
	default:
		break;
	}
}

void CEffectMgr::Set_FrameInfo(FRAME& _tFrame, int _iEndScene, DWORD _dwSpeed, int _iWidth, int _iHeight)
{
	_tFrame.dwFrameTime = 0;
	_tFrame.iFrameStart = 0;
	_tFrame.iFrameCurr = 0;
	_tFrame.iFrameEnd = _iEndScene;
	_tFrame.dwFrameSpeed = _dwSpeed;
	_tFrame.iWidth = _iWidth;
	_tFrame.iHeight = _iHeight;
}
