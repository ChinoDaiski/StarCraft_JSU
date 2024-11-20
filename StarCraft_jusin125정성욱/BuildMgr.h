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
	// ���ڷ� ���� �ǹ��� �����Ͽ� ������Ʈ �Ŵ����� �־��ִ� �Լ�
	void create_Build(BUILD _eBuild, SCENEID _eSceneID);
	void create_Build(BUILD _eBuild, float _fX, float _fY, SCENEID _eSceneID);
	void create_Build(BUILD _eBuild, POINT pt, SCENEID _eSceneID);
	void Set_BuildInfo(BUILD _eBuild, int _iWidth, int _iHeight);
	void Init_BuildInfo(BUILD _eBuild);

	// ���ڷ� ���� �ǹ��� ���콺�� ��ǥ�� �׷��ִ� �Լ�
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

	// ���� ���콺�� ����ٴϸ� ���̴� �ǹ��� ����, ���� ��� BUILD::END���� ������.
	BUILD		m_eCurrShowBuild;

	// �ʷ�/���� ��� �̹��� DC
	HDC			m_AlphaDC;		// ���ĺ��带 ���� ����� �̹���
	HDC			m_ValidDC;		// �ʷϻ� ����̹���
	HDC			m_InValidDC;	// ������ ����̹���
	bool		m_bValid;		// ���� ���콺�� ��ġ�� �ǹ��� �����Ǵ� Ÿ���� ��ȿ���� �ƴ��� Ȯ���ϴ� ����
								// ��ȿ�� ��� true, �ƴ� ��� false���� ������.

	
};

