
// 버튼 class
// 버튼을 누르면 특정 정보가 반환되는 버튼이다.
// 여기서는 에디터에서 타일이나 유닛에 대한 정보를 가지고 있다.

// 버튼을 누른다. -> 버튼이 가지고 있는 어떤 값이 반환된다. -> 반환된 값에 따라 설정된 타일/오브젝트/유닛/건물을 맵에서 생성할 수 있다.

// 필요한 것 : 타일/오브젝트/유닛/건물을 공통적인 어떤 값으로 설정해야 한다.
// 버튼이 눌렸는지 안눌렸는지 확인해야 한다.

// 여기서는 누른 버튼을 제외한 나머지 버튼을 누르지 않은 것으로 한다. 또는 누르는 순간 해당하는 버튼의 사각형 정보를 가져와 해당하는 곳에
// 사각형을 누른다.

// 전자는 버튼 관련 매니저를 만들어야 함으로, 후자 선택 -> 누르는 사람은 user로 한다. 유저가 버튼을 누르고, 해당 버튼이 눌려졌다면,
// 생성할 수 있는 것을 달라지게 한다.

// 이렇게 하자면 버튼이 가지고 있는 값의 기준을 framekey로 하면 되고 -> X, 추가로 생각할 것이 많음.
// 기준... 기준을 뭐로할까?

// 버튼을 나눈다. 기본 버튼을 기준으로 타일/건물/오브젝트/유닛 버튼을 만든다. 채택!

// 만들어진 버튼을 EditorUI에서 관리하여 출력한다. 채택!

// 아니면, 버튼을 누르면 눌린 버튼을 1개로 설정하여, 마지막에 눌린 버튼의 정보만 가져오는식으로 한다. -> 채택! 이러면 여러 버튼을 만들 필요가 없음.

// 이러면 버튼을 관리할 무언가 필요한데, 그냥 EditorUI에서 관리하는것으로 마무리. 생성도 EditorUI에서 한다.

#pragma once

#include "Obj.h"
#include "stdafx.h"
#include "Enum.h"

class CEditorButton : public CObj {
public:
	CEditorButton();
	virtual ~CEditorButton();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual int			Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	HDC Get_DC(void) const {
		return m_DC;
	}
	const ButtonInfo& Get_BInfo(void) const {
		return m_tBInfo;
	}

	void	Set_Size(int _iWidth, int _iHeight) {
		m_iWidth = _iWidth;
		m_iHeight = _iHeight;
	}
	void	Set_Tile(TERRAIN _Terrain) {
		m_tBInfo.Terrain = _Terrain;
		m_tBInfo.eUnit = UNIT_NAME::END;
		m_tBInfo.eBuild = BUILD::END;
	}
	void	Set_Tile(UNIT_NAME _eUnit) {
		m_tBInfo.eUnit = _eUnit;
		m_tBInfo.Terrain = TERRAIN::END;
		m_tBInfo.eBuild = BUILD::END;
	}
	void	Set_Tile(BUILD _eBuild) {
		m_tBInfo.eBuild = _eBuild;
		m_tBInfo.eUnit = UNIT_NAME::END;
		m_tBInfo.Terrain = TERRAIN::END;
	}

private:
	ButtonInfo		m_tBInfo;	// 버튼 정보
	HDC				m_DC;		// 버튼의 이미지가 있는 DC

	int				m_iWidth;
	int				m_iHeight;
};

