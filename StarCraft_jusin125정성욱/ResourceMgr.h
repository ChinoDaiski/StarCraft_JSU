#pragma once

#include "Include.h"

class CResourceMgr : public CSingleton<CResourceMgr> {
public:
	CResourceMgr();
	virtual ~CResourceMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// ó�� ������ ���� �ΰ���� ���µ� �ʿ��� ���ҽ��� ��Ʈ�� �Ŵ����� �ε��ϴ� �Լ�
	void Load_Logo(void);

	// ���ӿ��� ����ϴ� ��� ���ҽ��� ��Ʈ�� �Ŵ����� �ε��ϴ� �Լ�
	void Load_All(void);
};

