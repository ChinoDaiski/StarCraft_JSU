#pragma once

#include "Unit.h"

enum class BUILD_STATUS {
	Build_Start,			// �ǹ� ���� ������ ���
	Building,				// �ǹ��� ���� �ִ� ���
	Building_Compelete,		// �ǹ��� �ϼ��� ���
	Build_After,			// �ǹ��� ������ ����
	Build_Compelte,			// �ǹ��� �ϼ��� ���
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
	// �ǹ��� �̸��� ���ڷ� �޾� �ش��ϴ� �ǹ��� ��� ������ �����ϴ� �Լ�
	void Set_Build(BUILD _eBuild);

	// ������ �̸��� ���ڷ� �޾� �ش��ϴ� ������ �������ͽ� ������ �����ϴ� �Լ�
	void Set_BuildStatus(BUILD _eBuild);

	// ������ ������ �׷����� WireFrame�� ������ �ٲٴ� �Լ�
	// �������� �޴� �Լ��� �����Ǿ� �ִ�. ��, �� �Լ��� ���״�� �̹����� ������ �����ϴ� �Լ�
	// �������� �̹����� ũ�� 7������ ������ �����Ѵ�.
	void Set_WireFrameInfo(BUILD _eBuild);

	// ��� ������ �ʱ�ȭ �ϴ� �Լ�
	void Set_BuildInfo(BUILD _eBuild);

protected:
	//PortraitInfo		m_tPortrait;			// �ǹ��� �����ϰ� �Ǹ� �ؿ� ������ �ʻ�ȭ
	//StatusFrameInfo	m_tStatusFrameInfo;		// �ǹ��� �����ϰ� �Ǹ� ������ ����â�� ���õ� ����ü

	BUILD_STATUS		m_eBuildStatus;			// ���� �ǹ��� ����
	FRAME				m_tCreateBuildFrame;	// �ǹ��� ���¿� ���� �̹��� Frame ������ ��� �ִ� ����ü
	HDC					m_CreateBuildDC;		// �ǹ��� �����ϴµ� �ʿ��� �̹��� DC
	HDC					m_CreateBuildAfterDC;

	int					m_iRepeatBuildingCnt;	// �ǹ� ���¸�� ���ư��� Ƚ��
};

