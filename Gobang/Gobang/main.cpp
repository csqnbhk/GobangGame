#include"precompiled_header.h"
#include"singleton_pattern.h"
#include"windows_handle.h"
#include"client.h"
#include"thread.h"
#include"resource.h"
#include"Dialog_handle.h"

use_mynamespace

int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE prehinstance,LPSTR lpCmdLine,int nCmdShow)
{
	
	RegisterWindow(hinstance, prehinstance, lpCmdLine, nCmdShow);
	freopen("log.txt", "a", stdout);

	Singleton<log_thread>::InitInstance();
	static log_thread*ptr_log = log_thread::GetInstance();
	ptr_log->Create();
	
	//连接服务器对话框
	
	DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG_CONNECT_SERVER),0, (DLGPROC)DialogProc);
	InitDialog();
	
	Socket*main_socket = Socket::GetInstance();
	
	/*
	main_socket->InitEnvironment();
	main_socket->SetServerIp(ServerIP);
	main_socket->SetServerPort(atoi(ServerPort));
	main_socket->ConnectServer();
	*/
	
	
	MSG msg = { 0 };
	while (GetMessage(&msg, 0,0, 0))
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//释放其它资源
	main_socket->CloseConnect();
	main_socket->ClearResource();
	//释放全局资源
	DelGlobalResource();
	return 0;

}

