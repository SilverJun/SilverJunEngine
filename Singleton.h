//
#pragma once
template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		call_once(m_onceFlag, [] 
			{
				m_pInstance.reset(new T);
			}
		);
		return m_pInstance.get();
	}

private:
	static std::shared_ptr<T> Singleton<T>::m_pInstance;
	static std::once_flag m_onceFlag;
};

template <typename T> std::shared_ptr<T> Singleton<T>::m_pInstance = nullptr;

template <typename T> std::once_flag Singleton<T>::m_onceFlag;
//
//#pragma once
//
//template <class T>
//class Singleton
//{
//public:
//	static T *ms_pSingleton;
//
//public:
//	Singleton()
//	{
//		unsigned __int32 ulOffset = (unsigned __int32)((T*)(1)) - (unsigned __int32)((Singleton<T>*)(T*)1);
//
//		ms_pSingleton = (T*)((unsigned __int32)this + ulOffset);
//	}
//
//	virtual ~Singleton()
//	{
//		ms_pSingleton = 0;
//	}
//
//	static T* GetInstance()
//	{
//		return(ms_pSingleton);
//	}
//};
//
//template <class T> T* Singleton<T>::ms_pSingleton = 0;
