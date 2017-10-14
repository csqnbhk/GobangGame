/******************************************************************

              fuuction:this file is used to create base thread handle
			  author:Demon
			  Time:2017/10/2

******************************************************************/
#include"thread.h"
my_namespace_begin
/*****************  ��̬��Ա���� *********************************/
 DWORD WINAPI thread:: _Entry(LPVOID lpvoid)
{
	thread*ptr = (thread*)lpvoid;
	ptr->Entry();
	return 0;
}
/****************************************************************/
thread::thread()
{
	this->ThreadHandle = nullptr;
	this->ThreadID = 0;
	this->flags = false;

}
thread::~thread()
{
	::CloseHandle(this->ThreadHandle);
	
}
bool thread::GetFlags()
{
	return this->flags;
}
void thread::Create()
{

	this->ThreadHandle = ::CreateThread(0, 0, _Entry, (LPVOID)this, 0, 0);
	this->ThreadID = ::GetThreadId(this->ThreadHandle);

}
DWORD thread::GetThreadID()
{
	 return this->ThreadID;
	//return ::GetThreadId(this->ThreadHandle);
}


/*****************************************************************************************************
                           io_thread class
******************************************************************************************************/
io_thread::io_thread(HANDLE handle)
{

	this->Cond = handle;
	this->existflags = true;
}
io_thread::~io_thread()
{

}
BOOL io_thread::SetCondSignal()
{
	return ::SetEvent(this->Cond);
}
void io_thread::Entry() 
{

	while (this->existflags)
	 {
		
		DWORD err=::WaitForSingleObject(this->Cond, INFINITE);
		if (err == WAIT_FAILED)
		{
			 //������
		}
		//����io������1.FD_READ 2.FD_WRITE)
		cout << "log_cond ����" << endl;
		SetEvent(this->Cond);
	}

}


/****************************************************************************************************** 
                                log_thread class
*******************************************************************************************************/
/*******************************           ��̬��ʼ��     *********************************************/
log_thread*log_thread::Log_Instance = nullptr;
log_thread *log_thread::GetInstance()
{
	if (Log_Instance == nullptr)
		Log_Instance = new log_thread();
	return Log_Instance;

}
 /*****************************************************************************************************/
log_thread::log_thread()
{
	//::InitializeCriticalSection(&this->cs);
	this->Cond = CreateEvent(nullptr, false, false, nullptr);
	this->existflags = true;
	memset(this->buffer, 0, sizeof(this->buffer));

	
}
log_thread::~log_thread()
{
	//::DeleteCriticalSection(&this->cs);
}
BOOL log_thread::SetCondSignal()
{
	return SetEvent(Cond);
}

void log_thread::out_log_txt(char const*txt,DWORD err)
{

	sprintf(buffer,"�������:%d,",err);
	strcat(buffer, txt);
	SetEvent(Cond);
}
void log_thread::Entry()
{

	while (this->existflags)
	{  
		WaitForSingleObject(Cond, INFINITE);	
		SYSTEMTIME st;
		GetLocalTime(&st);
		//EnterCriticalSection(&this->cs);
		cout << st.wYear << "/" << st.wMonth << "/" << st.wDay << "  " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
		cout <<buffer<< endl;
		//LeaveCriticalSection(&this->cs);
	}

}




my_namespace_end