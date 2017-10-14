#pragma once
/*****************************************************************************

function:this file is mainly used to handle windows' callback function
author:Demon
Time:2017/10/1~

******************************************************************************/
#include"precompiled_header.h"
#include"client.h"
#include"handle_tasks.h"
#include"image_res.h"
#include"arithmetic.h"
my_namespace_begin
extern int GobangMap[Row][Line];
/******************************************************************/
static NOTIFYICONDATA notify = { 0 };
Socket*w_h_socket = Socket::GetInstance();
handle_tasks*w_h_tasks = handle_tasks::GetInstance();
log_thread*w_h_log = log_thread::GetInstance();
parse_pack*parse_msg = new parse_pack();
/*****************************************************************/
#define IDT_TIMER1  1
#define IDT_TIMER2  2

extern ptr_late_site ptr_site;
static int win_flags = 0;
static msg_location c_p;

 
/*********************************

void CALLBACK  LoadBackGround(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)；
/******************************************************************/


/*****************************************************************/
LRESULT CALLBACK WinProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	
	switch (Message)
	{

	case WM_CLOSE:
	{
		notify.cbSize = sizeof(NOTIFYICONDATA);
		notify.hIcon = LoadIcon(0, MAKEINTRESOURCE(IDI_ICON1));
		notify.hWnd = hwnd;
		notify.uCallbackMessage = WM_NOTIFYICON;
		notify.uID = IDI_ICON1;
		notify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		wcscpy(notify.szTip, TEXT("Gobang is running"));
		Shell_NotifyIcon(NIM_ADD, &notify);
		ShowWindow(hwnd, SW_HIDE);
		break;
	}

	case WM_NOTIFYICON:

	{
		switch (lparam)
		{
		case WM_RBUTTONDOWN:
			if (MessageBox(0, TEXT("你确定要退出游戏吗?"), TEXT("温馨提示"), MB_YESNO | MB_ICONWARNING) == IDYES)
			{
				Shell_NotifyIcon(NIM_DELETE, &notify);
				SendMessage(hwnd, WM_DESTROY, 0, 0);
				break;
			}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		{

			ShowWindow(hwnd, SW_SHOW);
			Shell_NotifyIcon(NIM_DELETE, &notify);
			break;
		}
		default:
			break;
		}
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_SOCKET:
	{
		//SOCKET temp = (SOCKET)wparam;
		int err = HIWORD(lparam);
		int fd_event = LOWORD(lparam);
		switch (fd_event)
		{
		 case FD_WRITE:                   //在这里发送各种命令（一般不）
		 {

			break;
		 }

		case FD_READ:                  //在这里处理各种命令
		{

			w_h_socket->RecvMsgPack();//先用在这里用单线程处理
			int16  return_msg_code=parse_msg->GetCode(w_h_socket->GetRecvPack());
			c_p = parse_msg->GetSite(w_h_socket->GetRecvPack());                     //获取对方坐标点

			switch (return_msg_code)
			{
			  case  msg_start_game :                                                //开始游戏
			  {
				  w_h_tasks->HandleSartGame();
				  break;
			  }
			  case	msg_start_end:                                                  //游戏结束
			  {
				  w_h_tasks->HandleEndGame();
				  break;
			  }
			  case	msg_start_again:                                                //再来一盘
			  {
				  w_h_tasks->HandleTryAgain();
				  break;
			  }

			  case	msg_take_next:                                                  //下棋
			  {
				  
				  w_h_tasks->HanldeTakeNext(c_p);
				  break;
			  }
			  case	msg_beg_peace:                                                  //请求求和
			  {
				  w_h_tasks->HandleBegPeace();
				  break;
			  }
			  case	msg_beg_back:                                                  //请求悔棋
			  {
				  w_h_tasks->HandleBegBack();
				  break;
			  }

			  case	msg_peace_succeed:                                             //同意求和
			  {
				  w_h_tasks->HandleAgreeBegPeace(w_h_socket);
				  break;
			  }
			  case	msg_peace_failed:                                               //不同意求和
			  {
				  w_h_tasks->HandleDisagreeBegPeace(w_h_socket);
				  break;
			  }
			  case	msg_back_succeed:                                               //同意悔棋
			  {
				  w_h_tasks->HandleAgreeBegBack(w_h_socket);
				  break;
			  }
			  case	msg_back_failed :                                              //不同意悔棋
			  {
				  w_h_tasks->HandleDisagreeBegBack(w_h_socket);
				  break;
			  }
			  case	msg_get_win:                                                  //赢棋
			  {
				  w_h_tasks->HandleWin();
				  break;
			  }
			  case	mgs_lose_win:                                                 //输棋
			  {
				  w_h_tasks->HandleLose();
				  break;
			  }

			  default:
			  break;
			}
			break;
		}

		case  FD_CLOSE:
		{
			//Messagebox(0,"对方关闭连接","温馨提示".MB_OK);
			break;
		}
		default:
		break;
		}
		break;
	}

	case WM_TIMER:
	{
		switch (wparam)
		{
		case IDT_TIMER1:
			//LoadBackGround(hwnd,TEXT("myres//background.bmp"), 800, 600);
			DrawAll(hwnd,Message,wparam,lparam);
			break;
		case IDT_TIMER2:
			break;
		default:
			break;
		}
		break;
	}
    
	case WM_MOUSEMOVE:
	{
		//int xPos = GET_X_LPARAM(lparam);
		//int yPos = GET_Y_LPARAM(lparam);
		//if (xPos > 645 && xPos < 745 && yPos>220 && yPos < 250)
		//{

		//	
		//}
		//
		//if (xPos > 645 && xPos < 745 && yPos>275 && yPos <305)
		//{
		//	//LoadBegBack(hwnd, TEXT("myres//begback_2.bmp"), 100, 30, 645, 275);
		//}
		//if (xPos > 645 && xPos < 745 && yPos>350 && yPos <380)
		//{
		//	//LoadBegPeace(hwnd, TEXT("myres//begpeace_2.bmp"), 100, 30, 645, 350);
		//}
		//if (xPos >695 && xPos< 795 && yPos>570 && yPos <600)
		//{ 
		//	//LoadExitGame(hwnd, TEXT("myres//exitgame_2.bmp"), 100, 30, 695, 570);
		//}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		if (win_flags==0&&ptr_site->admin == true)//如果是对方下棋赢，记得要在接收数据（把admin置为false）
		{
			int xPos = GET_X_LPARAM(lparam);
			int yPos = GET_Y_LPARAM(lparam);
			int x = (xPos - 55) / 35;
			int y = (yPos - 55) / 35;
			int x_remainder = (xPos - 55) % 35;
			int y_remainder = (yPos - 55) % 35;
			if (x_remainder < 12 && y_remainder < 12)
			{
				GobangMap[x][y] = 1;
			}
			if (x_remainder > 23 && y_remainder > 23)
			{
				x++;
				y++;
				GobangMap[x][y] = 1;
			}
			if (x_remainder < 12 && y_remainder>23)
			{
				y++;
				GobangMap[x][y] = 1;
			}
			if (x_remainder > 23 && y_remainder < 23)
			{
				x++;
				GobangMap[x][y] = 1;
			}
			//保存最近一次下棋坐标点
			ptr_site->self_x = x;
			ptr_site->self_y = y;
			ptr_site->admin = false;//置为false，等待对方下棋(记得处理这里）
			//判断输赢
			win_flags = Gobang_Jude_Win();//这个主要判断本方的是否赢
			if (win_flags == 1)
			{
				win_flags = 1;
				MessageBox(0, TEXT("你赢了"), TEXT("游戏输赢提示"), MB_OK | MB_ICONWARNING);

			}
			if (win_flags == -1)
			{
				win_flags = -1;
				MessageBox(0, TEXT("你输了"), TEXT("游戏输赢提示"), MB_OK | MB_ICONWARNING);

			}

		}
		/*
		if (xPos > 645 && xPos < 745 && yPos>220 && yPos < 250)
		{
			MessageBox(0, TEXT("开始游戏"), TEXT("提示"), MB_OK);

		}
		if (xPos > 645 && xPos < 745 && yPos>275 && yPos <305)
		{
			//MessageBox(0, TEXT("悔棋"), TEXT("提示"), MB_OK);
		}
		if (xPos > 645 && xPos < 745 && yPos>350 && yPos <380)
		{
			//MessageBox(0, TEXT("求和"), TEXT("提示"), MB_OK);
		}
		if (xPos >695 && xPos< 795 && yPos>570 && yPos <600)
		{
			//MessageBox(0, TEXT("退出游戏"), TEXT("提示"), MB_OK);
		}
		*/
	
		break;
	}
	case WM_LBUTTONUP:
	    {
		   
		    break;
	    }
	case WM_RBUTTONDOWN:
	{
		break;
	}
	case WM_COMMAND:
	{
		break;
	}
	default:
	return DefWindowProc(hwnd, Message, wparam, lparam);
	  
	}

	return 0;
}
void RegisterWindow(HINSTANCE hinstance, HINSTANCE prehinstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	WNDCLASS wnd = { 0 };
	ZeroMemory(&wnd, sizeof(WNDCLASS));
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(0, IDI_APPLICATION);
	wnd.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
	wnd.hInstance = hinstance;
	wnd.lpfnWndProc = &WinProc;
	wnd.lpszClassName = TEXT("myclass");
	wnd.lpszMenuName = 0;
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wnd);
	hwnd = CreateWindow(TEXT("myclass"), TEXT("Gobang"), WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_THICKFRAME, 200, 200, 815,635, 0, 0, hinstance, 0);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	/*******************************************************************
	                     设置定时器
	********************************************************************/
	SetTimer(hwnd, IDT_TIMER1, 50, 0);
	

}

my_namespace_end