/***************************************************************
       
	   function:this template file is used to instantiation
       author£ºDemon
	   Time:2017/10/1

***************************************************************/
#pragma once
my_namespace_begin

template<typename T>
class Singleton
{
public:
	template<typename...Args>
	static T*InitInstance(Args&&...args)
	{
		if (Instance == nullptr)
		{
			Instance = new T(std::forward<Args>(args)...);
			
		}
		return Instance;
	}
	static T*GetInstance()
	{
		if (Instance == nullptr)
		throw std::logic_error("The Instance is not init,so that the pointer is nullptr.please call the InitInstance at first");
		return Instance;
	}
	static void DestoryInstance()
	{
		delete Instance;
		Instance = nullptr;
	}
private:
	Singleton();
	virtual~Singleton()noexcept;
	Singleton(const Singleton&);
	Singleton&operator=(const Singleton&);
	static T*Instance;
};
template<class T>
T*Singleton<T>::Instance = nullptr;

my_namespace_end