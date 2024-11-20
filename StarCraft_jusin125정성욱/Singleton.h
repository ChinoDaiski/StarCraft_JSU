#pragma once

#include "Define.h"

__interface baseInterface {
	void Initialize(void) PURE;
	int Update(void) PURE;
	void Late_Update(void) PURE;
	void Render(HDC hDC) PURE;
	void Release(void) PURE;
};


template<typename T>
class CSingleton {
public:
	CSingleton() {}
	virtual ~CSingleton() {}

public:
	virtual void Initialize(void) PURE;
	virtual int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

public:
	static T*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new T;

		return m_pInstance;
	}

	static void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

protected:
	static		T*		m_pInstance;
};

template <typename T>
T*	CSingleton<T>::m_pInstance = nullptr;