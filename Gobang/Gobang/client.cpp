#include"client.h"
my_namespace_begin

/***************** ��̬��Ա��ʼ��     *******************/

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
	this->tempbuffer1 = new TCHAR[TEMP_BUFFER];
	this->tempbuffer4 = new char[TEMP_BUFFER*2+1];
    this->tempbuffer4[TEMP_BUFFER]='\0';
	
	this->sin_addr.S_un.S_addr = inet_addr(pIp);
	this->sin_port = htons(port);

	this->SendPack = new msg_pack();
	this->RecvPack = new msg_pack();

   

} 
Socket::~Socket()
{
	//����Ҫ��ע���ͷŵ�ʱ��
	delete[]this->tempbuffer4;
}


//��ʼ��Socket����
bool Socket::InitEnvironment()
{

	WSADATA wsadata = { 0 };
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested,&wsadata)!=0)
	{
		this->error(TEXT("WSAStartup()"), TEXT("Could not find a usable  WinSock DLL"));
		socket_log->out_log_txt(this->tempbuffer4, GetLastError());
		return false;
	}
	if (2 != LOBYTE(wsadata.wVersion) || 2 != HIBYTE(wsadata.wHighVersion))
	{
		this->error(TEXT("Socket Version"), TEXT("wVersion and wHighVersion is not right"));
		DWORD err = GetLastError();
		socket_log->out_log_txt(this->tempbuffer4,err);
		return false;
	}
	return true;
}
//��ʼ��server
void Socket::InitClientSocket()
{
	//����socket
	this->serversocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serversocket == INVALID_SOCKET)
	{
		DWORD err = GetLastError();
		this->error(TEXT("socket()"), TEXT(" INVALID_SOCKET handle"));
		socket_log->out_log_txt(this->tempbuffer4, err);

	}
	memset(&this->sockaddr, 0, sizeof(this->sockaddr));
	this->sockaddr.sin_family = AF_INET;
	this->sockaddr.sin_addr.S_un.S_addr = this->sin_addr.S_un.S_addr;
	this->sockaddr.sin_port = this->sin_port;
	int WSA_Flag = WSAAsyncSelect(this->serversocket, hwnd, WM_SOCKET, FD_WRITE | FD_READ | FD_CONNECT| FD_CLOSE);
	if (WSA_Flag == SOCKET_ERROR)
	{
		this->error(TEXT("WSAAsyncSelect()"), TEXT("return SOCKET_ERROR"));
		socket_log->out_log_txt(this->tempbuffer4, GetLastError());
		return ;
	}
}


//���ӷ�����
bool Socket::ConnectServer()
{
	
	int connect_flag=connect(this->serversocket, (SOCKADDR*)&this->sockaddr, sizeof(SOCKADDR));
	if (connect_flag != SOCKET_ERROR)//�첽�տ�ʼû��ɣ����ǻ᷵��SOCKET_ERROR
	{
		DWORD err = GetLastError();
		this->error(TEXT("connect()"),TEXT( "return SOCKET_ERROR"));
		socket_log->out_log_txt(this->tempbuffer4, err);
		return false;
	}
	return true;
}

//����SendPack
void Socket::SetSendPack(msg_code code, msg_location site, char *const data)
{
	memset(this->SendPack, 0, sizeof(msg_pack));
	this->SendPack->code =code;
	this->SendPack->site.gobang_x = site.gobang_x;
	this->SendPack->site.gobang_y = site.gobang_y;
	memcpy(this->SendPack->data, data, sizeof(this->SendPack->data));
}

//������Ϣ��
int Socket::SendMsgPack()
{
	int send_flag = ::send(this->serversocket, (char *const)this->SendPack,sizeof(msg_pack), 0);
	if (send_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("send()"), TEXT("return SOCKET_ERROR"));
		socket_log->out_log_txt(this->tempbuffer4, err);
		return -1;
	}


	return send_flag;
}
//������Ϣ��
int Socket::RecvMsgPack()
{
	memset(this->RecvPack, 0, sizeof(msg_pack));

	auto recv_flag = ::recv(this->serversocket,(char*) this->RecvPack,sizeof(msg_pack), 0);
	if (recv_flag == SOCKET_ERROR)
	{
		DWORD err = GetLastError();
		this->error(TEXT("recv()"), TEXT("return SOCKET_ERROR"));
		socket_log->out_log_txt(this->tempbuffer4,err);
		return -1;
	}
	return recv_flag;

}

/****************************************************************************************************************************************************/

//�ر�����
void Socket::CloseConnect()
{
	if (this->serversocket != INVALID_SOCKET)
	{
		DWORD err = GetLastError();
		auto close_flag=::closesocket(this->serversocket);
		if (close_flag == SOCKET_ERROR)
		{
			this->error(TEXT("closesocket()"), TEXT("return SOCKET_ERROR"));
			socket_log->out_log_txt(this->tempbuffer4,err);
			return;
		}
		this->serversocket = INVALID_SOCKET;
	}
}

//�Ƿ���Դ
void Socket::ClearResource()
{
	my_delete(this->tempbuffer1);
}

//������
void Socket::error(TCHAR const*lpText, TCHAR const*lpCaption)
{

	wsprintf(this->tempbuffer1, TEXT("Call %s failed"), lpText);
	wcstombs(this->tempbuffer4, this->tempbuffer1, TEMP_BUFFER * 2);
	MessageBox(0, this->tempbuffer1, this->tempbuffer1, MB_OK | MB_ICONWARNING);
}

void Socket::error(char const*file, char const*func, int const line)
{

	wsprintf(this->tempbuffer1, TEXT("�ļ�:%s,����:%s,��������:%d"), file, line);

}

my_namespace_end