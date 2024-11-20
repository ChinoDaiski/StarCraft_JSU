#pragma once

#include "Singleton.h"
#include "Include.h"

class CSaveLoadMgr : public CSingleton<CSaveLoadMgr> {
public:
	CSaveLoadMgr();
	~CSaveLoadMgr();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	// Ÿ�� �Ŵ����� ���� �Ŵ������� ���� �Լ��� ���� ����� ���⼭�� �������⸸ �Ѵ�.
	// Ÿ�ϰ� ���ֿ� ���� ������ ����/�ҷ����� �ϸ� �ȴ�.
	// ���ڷ� ����/�ҷ����� �� ������ �̸��� �޴´�.
	void Save(const TCHAR* strFilePath, SCENEID _eID);
	void Load(const TCHAR* strFilePath, SCENEID _eID);
};

