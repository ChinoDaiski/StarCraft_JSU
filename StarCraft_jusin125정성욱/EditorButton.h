
// ��ư class
// ��ư�� ������ Ư�� ������ ��ȯ�Ǵ� ��ư�̴�.
// ���⼭�� �����Ϳ��� Ÿ���̳� ���ֿ� ���� ������ ������ �ִ�.

// ��ư�� ������. -> ��ư�� ������ �ִ� � ���� ��ȯ�ȴ�. -> ��ȯ�� ���� ���� ������ Ÿ��/������Ʈ/����/�ǹ��� �ʿ��� ������ �� �ִ�.

// �ʿ��� �� : Ÿ��/������Ʈ/����/�ǹ��� �������� � ������ �����ؾ� �Ѵ�.
// ��ư�� ���ȴ��� �ȴ��ȴ��� Ȯ���ؾ� �Ѵ�.

// ���⼭�� ���� ��ư�� ������ ������ ��ư�� ������ ���� ������ �Ѵ�. �Ǵ� ������ ���� �ش��ϴ� ��ư�� �簢�� ������ ������ �ش��ϴ� ����
// �簢���� ������.

// ���ڴ� ��ư ���� �Ŵ����� ������ ������, ���� ���� -> ������ ����� user�� �Ѵ�. ������ ��ư�� ������, �ش� ��ư�� �������ٸ�,
// ������ �� �ִ� ���� �޶����� �Ѵ�.

// �̷��� ���ڸ� ��ư�� ������ �ִ� ���� ������ framekey�� �ϸ� �ǰ� -> X, �߰��� ������ ���� ����.
// ����... ������ �����ұ�?

// ��ư�� ������. �⺻ ��ư�� �������� Ÿ��/�ǹ�/������Ʈ/���� ��ư�� �����. ä��!

// ������� ��ư�� EditorUI���� �����Ͽ� ����Ѵ�. ä��!

// �ƴϸ�, ��ư�� ������ ���� ��ư�� 1���� �����Ͽ�, �������� ���� ��ư�� ������ �������½����� �Ѵ�. -> ä��! �̷��� ���� ��ư�� ���� �ʿ䰡 ����.

// �̷��� ��ư�� ������ ���� �ʿ��ѵ�, �׳� EditorUI���� �����ϴ°����� ������. ������ EditorUI���� �Ѵ�.

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
	ButtonInfo		m_tBInfo;	// ��ư ����
	HDC				m_DC;		// ��ư�� �̹����� �ִ� DC

	int				m_iWidth;
	int				m_iHeight;
};

