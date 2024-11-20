#pragma once

#include "Singleton.h"
#include "Include.h"

enum class CHANNELID { BGM, Alliance, Enemy, EFFECT, UI, Bullet, Build, Mouse, Button, MAXCHANNEL };

class CSoundMgr : public CSingleton<CSoundMgr>
{
public: // 최대 32 채널까지 동시 재생이 가능
	CSoundMgr();
	~CSoundMgr();

public:
	virtual void Initialize(void) override;

	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

	virtual void Release(void) override;

public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(TCHAR* pSoundKey, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);

public:
	void LoadSoundFile(); 

private:
	static CSoundMgr* m_pInstance; 

	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[(int)CHANNELID::MAXCHANNEL];

	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem; 



};

