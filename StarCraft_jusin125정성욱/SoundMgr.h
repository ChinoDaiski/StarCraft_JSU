#pragma once

#include "Singleton.h"
#include "Include.h"

enum class CHANNELID { BGM, Alliance, Enemy, EFFECT, UI, Bullet, Build, Mouse, Button, MAXCHANNEL };

class CSoundMgr : public CSingleton<CSoundMgr>
{
public: // �ִ� 32 ä�α��� ���� ����� ����
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

	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[(int)CHANNELID::MAXCHANNEL];

	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem; 



};

