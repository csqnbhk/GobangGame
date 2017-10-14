#include"client.h"
my_namespace_begin

/***************** 静态成员初始区     *******************/

log_thread*Socket::socket_log = log_thread::GetInstance();
Socket*Socket::SocketInstance=nullptr;

/*******************************************************/

 Socket*Socket::GetInstance()
 {
	 if (SocketInstance == nullptr)
		 SocketInstance = new Socket();
	 return SocketInstance;

 }

/***************************************************/
Socket::Socket(char const*pIp, u_short const port)
{
	ZeroMemory(&this->sockaddr, sizeof(this->sockaddr));
	this->pRecBuffer = new char  [SOCKET_BUFFER];
	this->pSendBuffer = new char [SOCKET_BUFFER];
	this->tempbuffer1 = new TCHAR[TEMP_BUFFER];
	this->tempbuffer2 = new TCHAR[TEMP_BUFFER];
	this->tempbuffer3 = new TCHAR[TEMP_BUFFER];
	this->tempbuffer4 = new char[TEMP_BUFFER*2+1];
	this->tempbuffer5 = new TCHAR[TEMP_BUFFER];
    this->tempbuffer4[TEMP_BUFFER]='\0';
	
	this->sin_addr.S_un.S_addr = inet_addr(pIp);
	this->sin_port = htons(port);

	this->SendPack = new msg_pack();
	this->RecvPack = new msg_pack();

    //创建socket
	this->listensocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listensocket == INVALID_SOCKET)
	{
		DWORD err = GetLastError();
		this->error(TEXT("socket()"), TEXT(" INVALID_SOCKET handle"));
		socket_log->out_log_txt(this->tempbuffer4, err);
		
	}


} 
Socket::~Socket()
{
	//这两要个注意释放的时候
	my_delete(this->tempbuffer3);//普通数组delete和delete[]一样，对象数组就要用delete[]
	delete[]this->tempbuffer4;
	delete[]this->tempbuffer5;
}

void Socket::error( TCHAR const*lpText, TCHAR const*lpCaption)
{  

	/*
	my_zero(this->tempbuffer1);
	my_zero(this->tempbuffer2);
	my_zero(this->tempbuffer3);
	my_zero(this->tempbuffer4);
	auto error_no = WSAGetLastError();
	*/
	wsprintf(this->tempbuffer1,TEXT("Call %s failed"),lpText);
 	//wsprintf(this->tempbuffer2,TEXT("%s,the error code was:%d"), lpCaption,error_no);
	//wsprintf(this->tempbuffer3, TEXT("%s,%s"),this->tempbuffer2, this->tempbuffer1);
	wcstombs(this->tempbuffer4, this->tempbuffer1, TEMP_BUFFER * 2);
	MessageBox(0, this->tempbuffer1,this->tempbuffer1, MB_OK | MB_ICONWARNING);
}
//错误处理
void Socket::error(char const*file, char const*func, int const line)
{

	wsprintf(this->tempbuffer1, TEXT("文件:%s,函数:%s,出错行数:%d"), file, line);

}

//初始化Socket环境
bool Socket::InitEnvironment()
{

	WSADATA wsadata = { 0 };
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested,&wsadata)!=0)
	{
		this->error(TEXT("WSAStartup()"), TEXT("Could not find a usable  WinSock DLL"));
		//this->out_log_txt("call WSAStartup() failed,Could not find a usable  WinSock DLL");
		//socket_log->out_log_txt("call WSAStartup() failed,Could not find a usable  WinSock DLL");
		socket_log->out_log_txt(this->tempbuffer4, GetLastError());
		return false;
	}
	if (2 != LOBYTE(wsadata.wVersion) || 2 != HIBYTE(wsadata.wHighVersion))
	{
		this->error(TEXT("Socket Version"), TEXT("wVersion and wHighVersion is not right"));
		//this->out_log_txt("Socket' wVersion and wHighVersion is not right");
		//socket_log->out_log_txt("Socket wVersion and wHighVersion is not right");
		DWORD err = GetLastError();
		socket_log->out_log_txt(this->tempbuffer4,err);
		return false;
	}
	return true;
}

//绑定化服务器信息（客户端只能绑定local地址，否则会出错。此处主要做服务器时使用）
bool Socket::BindServer()
{
	
	memset(&this->sockaddr, 0, sizeof(this->sockaddr));
	this->sockaddr.sin_family = AF_INET;
	this->sockaddr.sin_addr.S_un.S_addr =this->sin_addr.S_un.S_addr;
	this->sockaddr.sin_port = this->sin_port;
	int bind_flag=::bind(this->listensocket, (SOCKADDR*)&this->sockaddr, sizeof(this->sockaddr));
	if (bind_flag == SOCKET_ERROR)
	{   
		this->error(TEXT("bind()"),TEXT( "return SOCKET_ERROR"));
		//this->out_log_txt("bind() return SOCKET_ERROR");
		//socket_log->out_log_txt("bind() return SOCKET_ERROR");
		socket_log->out_log_txt(this->tempbuffer4, GetLastError());
		return false;
	}
	return true;

}

//call WSAAsyncSelect（），设置相关信息
bool Socket::socket_connect_windows()
{
	int WSA_Flag=WSAAsyncSelect(this->listensocket,hwnd, WM_SOCKET, FD_WRITE|FD_READ | FD_CLOSE);
	if (WSA_Flag == SOCKET_ERROR)
	{
		this->error(TEXT("WSAAsyncSelect()"), TEXT("return SOCKET_ERROR"));
		//this->out_log_txt("WSAAsyncSelect(),return SOCKET_ERROR");
		//socket_log->out_log_txt("WSAAsyncSelect(),return SOCKET_ERROR");
	    
		socket_log->out_log_txt(this->tempbuffer4, GetLastError());
		return false;
	}
	return true;
}

//连接服务器
bool Socket::ConnectServer()
{
	
	memset(&this->sockaddr, 0, sizeof(this->sockaddr));
	this->sockaddr.sin_family = AF_INET;
	this->sockaddr.sin_addr.S_un.S_addr = this->sin_addr.S_un.S_addr;
	this->sockaddr.sin_port = this->sin_port;
	int connect_flag=::connect(this->listensocket, (SOCKADDR*)&this->sockaddr, sizeof(SOCKADDR));
	if (connect_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("connect()"),TEXT( "return SOCKET_ERROR"));
		//this->out_log_txt("connect() failed,return SOCKET_ERROR");
		//socket_log->out_log_txt("connect() failed,return SOCKET_ERROR");
		//ErrorLocation(this->tempbuffer5);
		
		socket_log->out_log_txt(this->tempbuffer4, err);
		return false;
	}
	return true;
}
/************************************************************************************************************************************/
int Socket::Send()
{

	int send_flag = ::send(this->listensocket, this->pSendBuffer, strlen(this->pRecBuffer), 0);
	if (send_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("send()"), TEXT("return SOCKET_ERROR"));
		//this->out_log_txt("send() failed,return SCOKET_ERROR");
		//socket_log->out_log_txt("send() failed,return SCOKET_ERROR");
		//socket_log->out_log_txt(this->tempbuffer4, GetLastError());
		
		socket_log->out_log_txt(this->tempbuffer4, err);
		return -1;
	}


	return send_flag;

	
}
//发送消息包
int Socket::SendMsgPack()
{
	int send_flag = ::send(this->listensocket, (char const*)this->SendPack,sizeof(msg_pack), 0);
	if (send_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("send()"), TEXT("return SOCKET_ERROR"));
		//this->out_log_txt("send() failed,return SCOKET_ERROR");
		//socket_log->out_log_txt("send() failed,return SCOKET_ERROR");
		socket_log->out_log_txt(this->tempbuffer4, err);
		return -1;
	}


	return send_flag;
}

int Socket::Recv()
{ 
	my_zero(this->pRecBuffer);
	auto recv_flag = ::recv(this->listensocket, this->pRecBuffer,SOCKET_BUFFER, 0);
	if (recv_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("recv()"),TEXT( "return SOCKET_ERROR"));
		//this->out_log_txt("recv() failed,return SOCKET_ERROR");
		//socket_log->out_log_txt("recv() failed,return SOCKET_ERROR
		socket_log->out_log_txt(this->tempbuffer4, err);
		return -1;
	}
	return recv_flag;

}
//接收消息包
int Socket::RecvMsgPack()
{
	memset(this->RecvPack, 0, sizeof(msg_pack));

	auto recv_flag = ::recv(this->listensocket,(char*) this->RecvPack,sizeof(msg_pack), 0);
	if (recv_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("recv()"), TEXT("return SOCKET_ERROR"));
		//this->out_log_txt("recv() failed,return SOCKET_ERROR");
		//socket_log->out_log_txt("recv() failed,return SOCKET_ERROR
		socket_log->out_log_txt(this->tempbuffer4,err);
		return -1;
	}
	return recv_flag;

}

/****************************************************************************************************************************************************/

//关闭连接
void Socket::CloseConnect()
{
	if (this->listensocket!= INVALID_SOCKET)
	{
		DWORD err = GetLastError();
		auto close_flag=::closesocket(this->listensocket);
		if (close_flag == SOCKET_ERROR)
		{
			this->error(TEXT("closesocket()"), TEXT("return SOCKET_ERROR"));
			//this->out_log_txt("closesocket() failed,return SOCKET_ERROR");
			//socket_log->out_log_txt("closesocket() failed,return SOCKET_ERROR");
			socket_log->out_log_txt(this->tempbuffer4,err);
			return;
		}
		this->listensocket = INVALID_SOCKET;
	}
}

//是否资源
void Socket::ClearResource()
{
	my_delete(this->pSendBuffer);
	my_delete(this->pRecBuffer);
	my_delete(this->tempbuffer1);
	my_delete(this->tempbuffer2);
	
}
my_namespace_end