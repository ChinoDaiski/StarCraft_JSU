#pragma once

#include "Unit.h"
#include "Build.h"

class CProbe : public CUnit {
public:
	CProbe();
	virtual ~CProbe();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	// 인자로 받은 건물을 인자로 받은 위치에 생성하는 함수
	void	Create_Build(BUILD _eBuild, POINT _tPos);

public:
	void	Update_State(void) override;

public:
	virtual void		Attack(CObj* _pObj) override;

private:
	POINT			m_tBuildPos;
	BUILD			m_eBuild;

	HDC				m_PlgDC;
	HDC				m_ResetDC;
};

