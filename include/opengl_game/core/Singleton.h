#pragma once
#include "Ref.h"
#include <type_traits>
#include <mutex>
//单例模板
template<class T>
class Singleton : public Ref
{
public:
	static T* getInstance()
	{
		if (ptr == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			ptr = new (std::nothrow)T();
			if (std::is_base_of<Ref, T>::value)
			{
				auto ptrRef = dynamic_cast<Ref*>(ptr);
				ptrRef->autorelease();
				ptrRef->retain();
			}
		}
		return ptr;
	}
	virtual ~Singleton() {};
protected:
	Singleton() {};
	static T* ptr;
	static std::mutex m_mutex;
};

template<class T>
T* Singleton<T>::ptr = nullptr;

template<class T>
std::mutex Singleton<T>::m_mutex;