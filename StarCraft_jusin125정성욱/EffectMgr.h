#pragma once

#include "Singleton.h"
#include "Include.h"
#include "Unit.h"


// 건물 생산
enum class BUILD_PRODUCE {
	// 드라군, 공중 업그레이드
	Cybernetics_Core,

	// 포토캐논, 지상 업그레이드
	Forge,

	// 넥서스 - 프로브
	Nexus,

	// 스타게이트 - 스카웃, 커세어, 캐리어, 아비터
	Stargate,

	END
};

// 건물 지어지고 난 뒤의 이펙트
enum class CREATE_AFTER { 
	// 아바타 생산 건물
	Arbiter_Tribunal,

	// 가스 생산 건물
	Assimilator,

	// 발업 연구소
	Citadel_of_Adun,

	// 드라군, 공중 업그레이드
	Cybernetics_Core,

	// 캐리어 연구소
	Fleet_Beacon,

	// 포토캐논, 지상 업그레이드
	Forge,

	// 게이트웨이 - 질럿, 드라군, 하이템플러, 다크템플러
	Gateway,

	// 넥서스 - 프로브
	Nexus,

	// 옵저버
	Observatory,

	// 포토 캐논
	Photon_Cannon,

	// 파일런 - 인구 수
	Pylon,

	// 로보틱스 - 셔틀, 리버, 옵져버
	Robotics_Facility,

	// 옵져버 연구소
	Robotics_Support_Bay,

	// 쉴드 배터리
	Shield_Battery,

	// 스타게이트 - 스카웃, 커세어, 캐리어, 아비터
	Stargate,

	// 하이/다크 템플러, 템플러 연구소
	Tempar_Archives,

	END };

// 기타 이미지가 필요한 건물
enum class BUILD_ITSELF {
	// 파일런 - 인구 수
	Pylon,

	// 포토 캐논
	Photon_Cannon,

	// 쉴드 배터리
	Shield_Battery,
	
	END
};


class CEffectMgr : public CSingleton<CEffectMgr> {
public:
	CEffectMgr();
	~CEffectMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// 인자로 받은 위치에 인자로 받은 유닛의 죽음 모션을 출력한다.
	void Show_DeadEffect(UNIT_NAME _eName, int _fX, int _fY);

	// 인자로 받은 위치에 인자로 받은 이펙트를 출력한다.
	void Create_Effect(EFFECT _eEffect, int _fX, int _fY, int _fCX, int _fCY);

	// 인자로 받은 위치에 인자로 받은 이펙트를 출력한다.
	void Show_Create_After_Effect(CREATE_AFTER _eEffect, int _fX, int _fY);

public:
	// Effect 프레임 정보 초기화
	void Init_Effect_Frame_Info(EFFECT _eEffect);
	// Create After 프레임 정보 초기화
	void Init_Create_After_Frame_Info(CREATE_AFTER _eEffect);

public:
	void Set_FrameInfo(FRAME& _tFrame, int _iEndScene, DWORD _dwSpeed, int _iWidth, int _iHeight);

private:
	HDC		m_EffectDC[(int)EFFECT::END];
	FRAME	m_tEffectFrame[(int)EFFECT::END];

	HDC		m_Create_AfterDC[(int)CREATE_AFTER::END];
	FRAME	m_tCreate_AfterFrame[(int)CREATE_AFTER::END];
};

