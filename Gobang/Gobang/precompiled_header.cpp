#include"precompiled_header.h"
my_namespace_begin

HWND hwnd = nullptr;
int GobangMap[Row][Line] = { 0 };
ptr_late_site ptr_site   = new late_site{ 0,0,0,0,true };
char* ServerIP   =new char [50];
char* ServerPort = new char[50];
char* ClientIP   = new char[50];
char* ClientPort = new char[50];

void DelGlobalResource()

{
	if (ServerIP != nullptr)
	{
		delete[] ServerIP;
		ServerIP = nullptr;
	}
	if (ServerPort != nullptr)
	{
		delete[] ServerPort;
		ServerPort = nullptr;
	}
	if (ClientIP != nullptr)
	{
		delete[] ClientIP;
		ClientIP = nullptr;
	}
	if (ClientPort != nullptr)
	{
		delete[] ClientPort;
		ClientPort = nullptr;
	}
}

my_namespace_end