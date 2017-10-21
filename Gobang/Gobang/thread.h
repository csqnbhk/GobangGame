/*************************************************************

      function:this file is used to create some threads
	  author:Demon
	  Time:2017/10/2

*************************************************************/
#include"precompiled_header.h"
#pragma once

my_namespace_begin

class thread
{

public:
	thread();
	virtual ~thread() noexcept;
	virtual void Entry() = 0;
	void  Create();
	DWORD GetThreadID();
	bool  GetFlags();
protected:

private:
	static DWORD WINAPI _Entry(LPVOID lpvoid);
	HANDLE ThreadHandle;
	DWORD ThreadID;
	bool flags;
};

//handle FD_WRITE and FD_WRITE
class io_thread:public thread
{
 public:
	explicit io_thread(HANDLE handle=nullptr);
	virtual ~io_thread() noexcept;
    virtual void Entry() override;
public:

	BOOL SetCondSignal();
 protected:

 private:
	 HANDLE Cond;
	 
	 bool existflags;
};

//handle log_txt
class log_thread :public thread
{
public:
	log_thread();
	virtual ~log_thread() noexcept;
	virtual void Entry() override;
	
public:
	BOOL SetCondSignal();
 	void out_log_txt(char const*log,DWORD err=0);
	static log_thread*GetInstance();
	
protected:
private:
	static log_thread*Log_Instance;
	 char buffer[512];
	 HANDLE Cond;
	//CRITICAL_SECTION cs;
	bool existflags;
};

my_namespace_end
