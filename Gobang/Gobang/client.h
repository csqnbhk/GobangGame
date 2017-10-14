/***********************************************************************

function:this file is used to handle basic socket events
author:Demon
Time:2017/10/1

***********************************************************************/
#pragma once
#include"precompiled_header.h"
#include"thread.h"

my_namespace_begin
class Socket:public SOCKADDR_IN //,public log_thread
{

	public: 
	Socket(char const*pIp="127.0.0.1",u_short const port=1660);
	virtual~Socket() noexcept;

	inline u_short GetPort()const 
	{
		return ntohs(this->sin_port);
	}
	inline char* GetIp()const
	{
		return inet_ntoa(this->sin_addr);
	}
public:
	void error(TCHAR const*lpText,TCHAR const*lpCaption=TEXT(""));
	void error(char const*file, char const*func, int const line);
public:
	inline void SetServerPort(u_short port)
	{
		this->sin_port =htons(port);
	}
	inline void SetServerIp(char const*pIp)
	{
		this->sin_addr.S_un.S_addr = inet_addr(pIp);
	}
public:

	bool InitEnvironment();
	bool BindServer();
	bool ConnectServer();
	int Send();
	int Recv();
	int SendMsgPack();
	int RecvMsgPack();
public:
	static Socket*GetInstance();
public:
	void CloseConnect();
	void ClearResource();

public:
	bool socket_connect_windows();
public:
	inline ptr_msg_pack GetSendPack()
	{
		return this->SendPack;
	}
	inline ptr_msg_pack GetRecvPack()
	{
		return this->RecvPack;
	}
private:
	static log_thread*socket_log;
	static Socket*SocketInstance;
	SOCKET listensocket;
	SOCKADDR_IN sockaddr;
	char*pSendBuffer;
	char*pRecBuffer;

	ptr_msg_pack SendPack;
	ptr_msg_pack RecvPack;

	TCHAR*tempbuffer1;
	TCHAR*tempbuffer2;
	TCHAR*tempbuffer3;
	char*tempbuffer4;
	TCHAR*tempbuffer5;

};
my_namespace_end
