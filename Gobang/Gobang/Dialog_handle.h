/**************************************************************************

              function:this file is used to handle the Dialog Message
			  author:Demon
			  Time:2017/10/9

***************************************************************************/
#pragma once
#include"precompiled_header.h"
#include"commctrl.h"
my_namespace_begin
BOOL CALLBACK DialogProc(HWND hDlg, UINT Message, WPARAM wparam, LPARAM lparam);
void InitDialog();
void GetClientIP_and_Port();
void GetLANIP_and_Port();
//初始化对话框
void InitDialog()
{


}




//登录服务器对话框
BOOL CALLBACK DialogProc(HWND hDlg, UINT Message, WPARAM wparam, LPARAM lparam)
{
	

	BOOL return_flags = TRUE;
	switch (Message)
	{

	 case WM_COMMAND:
	 {
		switch (wparam)
		{
		   case IDC_BUTTON_CONNECT_SERVER:
		   {
			   HWND h_server_ip   = GetDlgItem(hDlg, IDC_IPADDRESS_SERVER_IP);
			   HWND h_server_port = GetDlgItem(hDlg, IDC_EDIT_SERVER_PORT); 
			   HWND h_client_ip   = GetDlgItem(hDlg, IDC_IPADDRESS_CLIENT_IP);
			   HWND h_client_port = GetDlgItem(hDlg, IDC_EDIT_CLIENT_PORT);
			  
			   GetWindowTextA(h_server_ip,ServerIP, 50);
			   GetWindowTextA(h_server_port,ServerPort, 50);
			   GetWindowTextA(h_client_ip, ClientIP, 50);
			   GetWindowTextA(h_client_port,ClientPort, 50);
			   break;
		   }

		   case WM_DESTROY:
		   {
			EndDialog(hDlg, IDD_DIALOG_CONNECT_SERVER);
			break;
		   }
		   default:
		   {
			   return_flags = FALSE;
			   break;
		   }
	   }
    break;
    }
	default:
	{
		return_flags = FALSE;
		break;
	}

    }

	return return_flags;
	
}

my_namespace_end
