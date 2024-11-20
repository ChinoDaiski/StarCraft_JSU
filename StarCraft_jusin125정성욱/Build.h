#pragma once

#include "Unit.h"

enum class BUILD_STATUS {
	Build_Start,			// 건물 짓기 시작할 경우
	Building,				// 건물을 짓고 있는 경우
	Building_Compelete,		// 건물을 완성한 경우
	Build_After,			// 건물이 나오기 직전
	Build_Compelte,			// 건물이 완성된 경우
	END
};

class CBuild : public CObj {
public:
	CBuild();
	CBuild(const BuildInfo& _tBuildInfo);
	virtual ~CBuild();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	void	Set_BuildStatus(BUILD_STATUS _eBuildStatus);
	void	Move_BuildFrame(void);

public:
	const	RELATION&	Get_Relation(void) const { return m_eRelation; }

public:
	// 건물의 이름을 인자로 받아 해당하는 건물의 모든 정보를 설정하는 함수
	void Set_Build(BUILD _eBuild);

	// 유닛의 이름을 인자로 받아 해당하는 유닛의 스테이터스 정보를 설정하는 함수
	void Set_BuildStatus(BUILD _eBuild);

	// 데미지 정보로 그려지는 WireFrame의 정보를 바꾸는 함수
	// 데미지를 받는 함수와 연관되어 있다. 단, 이 함수는 말그대로 이미지의 정보만 세팅하는 함수
	// 데미지의 이미지를 크게 7가지로 나누어 관리한다.
	void Set_WireFrameInfo(BUILD _eBuild);

	// 모든 정보를 초기화 하는 함수
	void Set_BuildInfo(BUILD _eBuild);

protected:
	//PortraitInfo		m_tPortrait;			// 건물을 선택하게 되면 밑에 나오는 초상화
	//StatusFrameInfo	m_tStatusFrameInfo;		// 건물을 선택하게 되면 나오는 스탯창과 관련된 구조체

	BUILD_STATUS		m_eBuildStatus;			// 현재 건물의 상태
	FRAME				m_tCreateBuildFrame;	// 건물의 상태에 따른 이미지 Frame 정보를 담고 있는 구조체
	HDC					m_CreateBuildDC;		// 건물을 생성하는데 필요한 이미지 DC
	HDC					m_CreateBuildAfterDC;

	int					m_iRepeatBuildingCnt;	// 건물 짓는모션 돌아가는 횟수
};

