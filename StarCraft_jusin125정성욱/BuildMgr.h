#pragma once

#include "Singleton.h"
#include "Include.h"

class CBuildMgr : public CSingleton<CBuildMgr> {
public:
	CBuildMgr();
	~CBuildMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// 인자로 받은 건물을 생성하여 오브젝트 매니저에 넣어주는 함수
	void create_Build(BUILD _eBuild, SCENEID _eSceneID);
	void create_Build(BUILD _eBuild, float _fX, float _fY, SCENEID _eSceneID);
	void create_Build(BUILD _eBuild, POINT pt, SCENEID _eSceneID);
	void Set_BuildInfo(BUILD _eBuild, int _iWidth, int _iHeight);
	void Init_BuildInfo(BUILD _eBuild);

	// 인자로 받은 건물을 마우스의 좌표에 그려주는 함수
	void Set_ShowBuildMouse(BUILD _eBuild);

public:
	bool Get_Valid(void) const { return m_bValid; }
	void Set_Valid(bool _bValid) { m_bValid = _bValid; };

	BUILD Get_CurrBuild(void) const { return m_eCurrShowBuild; }
	void Set_CurrBuild(BUILD _eCurrShowBuild) { m_eCurrShowBuild = _eCurrShowBuild; };

private:
	HDC			m_ArrDC[(int)BUILD::END];
	HDC			m_ArrCreate_AfterDC[(int)BUILD::END];
	BuildInfo	m_tBuildInfoArr[(int)BUILD::END];

	// 현재 마우스를 따라다니며 보이는 건물의 정보, 없을 경우 BUILD::END값을 가진다.
	BUILD		m_eCurrShowBuild;

	// 초록/빨강 배경 이미지 DC
	HDC			m_AlphaDC;		// 알파블렌드를 위해 사용할 이미지
	HDC			m_ValidDC;		// 초록색 배경이미지
	HDC			m_InValidDC;	// 빨간색 배경이미지
	bool		m_bValid;		// 현재 마우스에 위치한 건물이 생성되는 타일이 유효한지 아닌지 확인하는 변수
								// 유효할 경우 true, 아닐 경우 false값을 가진다.

	
};

