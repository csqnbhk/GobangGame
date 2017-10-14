/***********************************************************************

                function:this file is used to get the LAN info
				author:Demon
				Time:2017/10/14

***********************************************************************/
#pragma once
#include<windows.h>
#include<iostream>
#include<string>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Mpr.lib")
using namespace std;
void GetSelfInfo();
void GetLANInfo();

/*
   主要使用的几个API
   WNetOpenEnum
   WNetEnumResource
   WNeCloseEnum


*/

void GetSelfInfo()
{
	WSADATA wsadata;
	int err=WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0)
	return;
	if (LOBYTE(wsadata.wVersion) != 2 ||HIBYTE(wsadata.wHighVersion) != 2)
	{
		WSACleanup();
		return;
	}
	char hostname[20] = { 0 };
	struct hostent*pHost;
	char hostIP[30] = { 0 };
	gethostname(hostname, sizeof(hostname));
	cout << "hostname=" << hostname << endl;
	pHost = gethostbyname(hostname);
	cout << "pHost=" << pHost << endl;
	sprintf(hostIP,"%d.%d.%d.%d", (pHost->h_addr_list[0][0] & 0x00ff), \
		                          (pHost->h_addr_list[0][1] & 0x00ff), \
		                          (pHost->h_addr_list[0][2] & 0x00ff), \
		                          (pHost->h_addr_list[0][3] & 0x00ff));
	cout << "主机名:" << hostname << endl;
	cout << hostIP << endl;
	
	int flags=WSACleanup();
	if (flags != 0)
	cout << "Call WSACleanup() failed" << endl;
}


void GetLANInfo()
{
	WSADATA wsadata;
	int err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0)
		return;
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		WSACleanup();
		return;
	}

	DWORD Count = 0x000003E8, Buffsize = 4096, Res;

	NETRESOURCE *nRes = nullptr;
	NETRESOURCE*nRes1 = nullptr;
	NETRESOURCE*nRes2 = nullptr;
	HANDLE lphEnum;
	LPVOID Buf = new char[4096];
    LPVOID Buf1 = new char[4096];
    LPVOID Buf2 = new char[4096];
	TCHAR* Computer_Name = new TCHAR[20];
	TCHAR *Computer_IP   =new TCHAR[30];
	char*p_Name = new char[100];
	char*p_IP = new char[100];
	
	Res = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY,RESOURCEUSAGE_CONTAINER, NULL, &lphEnum);
	Res = WNetEnumResource(lphEnum, &Count, Buf, &Buffsize);
	nRes = (NETRESOURCE*)Buf;
	for (DWORD n = 0;n < Count; n++,nRes++)
	{
		DWORD Count1 = 0x000003E8;
		Res = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, RESOURCEUSAGE_CONTAINER, nRes, &lphEnum);
		Res = WNetEnumResource(lphEnum, &Count1, Buf1, &Buffsize);
		nRes1 = (NETRESOURCE*)Buf1;
		for (DWORD i = 0;i < Count1;i++, nRes1++)
		{
			DWORD Count2 = 0x000003E8;
			Res = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, RESOURCEUSAGE_CONTAINER, nRes1, &lphEnum);
			Res = WNetEnumResource(lphEnum, &Count2, Buf2, &Buffsize);
			nRes2 = (NETRESOURCE*)Buf2;
			for (DWORD j = 0;j < Count2;j++, nRes2++)
			{

				


				 Computer_Name= nRes2->lpRemoteName;
				/* 
				 cout << "Computer_Name=" << nRes2->lpRemoteName << endl;
				 cout << "Computer_Name=" << Computer_Name << endl;
				 */
				 sprintf(p_Name, "%S", Computer_Name+2);
				 cout << "p_Name=" << p_Name << endl;
			    struct hostent*pHost;
				pHost = gethostbyname(p_Name);
				sprintf(p_IP, "%d.%d.%d.%d", (pHost->h_addr_list[0][0] & 0x00ff),          \
					                                  (pHost->h_addr_list[0][1] & 0x00ff),  \
					                                  (pHost->h_addr_list[0][2] & 0x00ff),   \
					                                  (pHost->h_addr_list[0][3] & 0x00ff));
				 cout << "Computer:" << p_Name<<"  " <<"IP:"<<p_IP<< endl;
				 
				 
          }
	   }

	}
	
	int flags = WSACleanup();
	if (flags != 0)
	cout << "Call WSACleanup() failed" << endl;
	WNetCloseEnum(lphEnum);
	delete Buf;
	delete Buf1;
	delete Buf2;
	delete[] p_Name;
	delete[] p_IP;
	delete[] Computer_Name;
	delete[] Computer_IP;
};

