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
	// 타일 매니저와 유닛 매니저에서 저장 함수를 따로 만들어 여기서는 가져오기만 한다.
	// 타일과 유닛에 대한 정보만 저장/불러오기 하면 된다.
	// 인자로 저장/불러오기 할 파일의 이름을 받는다.
	void Save(const TCHAR* strFilePath, SCENEID _eID);
	void Load(const TCHAR* strFilePath, SCENEID _eID);
};

