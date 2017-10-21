/****************************************************************

       function:this file is used to preprocess
	   author:Demon
	   Time:2017/10/1

**************************************************************/
#pragma once
#include<WinSock2.h>
#include<windows.h>
#include<windowsx.h>
#include<iostream>
#include<string>
#include<stdio.h>
#include <stdlib.h>
#include<functional>
#include<memory>
#include"resource.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"msimg32.lib")
#pragma pack(1)
#pragma warning(disable :4996)
using namespace std;

#ifndef my_namespace_begin
#define my_namespace_begin namespace my_namespace {   
#endif                                                
#ifndef my_namespace_end                             
#define my_namespace_end   };                              
#endif //myname_namespace_end

#ifndef use_mynamespace
#define use_mynamespace using namespace  my_namespace ;
#endif //use_mynamespace


/*****************************************************/
my_namespace_begin

#define my_delete(p) {delete p;p=nullptr;}
#define my_zero(p)   { memset(p,0,100);}


#define Row            15
#define Line           15
#define SOCKET_BUFFER  512
#define TEMP_BUFFER    100
#define WM_NOTIFYICON 1666
#define WM_SOCKET     1888
/**************************************************************
                全局变量              
***************************************************************/
extern HWND hwnd;
extern int GobangMap[Row][Line];
extern char* ServerIP;
extern char* ServerPort;
extern char* ClientIP;
extern char* ClientPort;
extern void DelGlobalResource();
/************************************************************/

//字节转化
/*******************************************************************************************/
bool _WideCharToMultiByte(LPCWSTR lpWideCharStr, LPSTR lpMultiByteStr, int cbMultiByte)
{
	int size = WideCharToMultiByte(CP_OEMCP, NULL, lpWideCharStr, -1, NULL, 0, NULL, FALSE);
	if (size > cbMultiByte)
		return false;
	WideCharToMultiByte(CP_OEMCP, NULL, lpWideCharStr, -1, lpMultiByteStr, cbMultiByte, NULL, FALSE);
	return true;
}
bool _MultiByteToWideChar(LPCSTR lpMultiByteStr, LPWSTR lpWideCharStr, int cchWideChar)
{

	int size = MultiByteToWideChar(CP_ACP, 0, lpMultiByteStr, -1, NULL, 0);
	if (size > cchWideChar)
		return false;
	MultiByteToWideChar(CP_ACP, 0, lpMultiByteStr, -1, lpWideCharStr, cchWideChar);
	return true;

}

/********************************************************************************************/


/*
枚举值的意义:

 0：空
-1：对方的棋子
 1：本方的棋子
*/
enum
{
	ENEMY = -1,//绿色棋子
	EMPTY,
	SELF       //黑色棋子

};
//存储最近的下棋位置
typedef struct save_late_site
{
	int enemty_x;
	int enemty_y;
	int self_x;
	int self_y;
	bool admin;
}late_site, *ptr_late_site;

extern ptr_late_site ptr_site;
/*****************************************************************************/

#ifndef UNICODE 
#define UNICODE  
#endif  //UNICODE
#ifndef TCHAR
typedef   wchar_t   TCHAR;
#else     
typedef unsigned   char   TCHAR;
#endif 


#ifndef ErrorLocation 
#define ErrorLocation(describe) { wsprintf(describe,TEXT("文件:%s,函数:%s,行数：%d"),__FILE__,__func__,__LINE__);return describe;  }
#endif //ErrorLocation 


//base type alais
using uint16  = unsigned short;
using int16   = signed short;
using uint32  = unsigned int;
using int32   = signed int;



//define message code
//static HANDLE io_recv_cond  =::CreateEvent(nullptr,false,false,nullptr);
//static HANDLE io_write_cond =::CreateEvent(nullptr, false, false, nullptr);

enum
{
	msg_start_game= -21555,                      //开始游戏
	msg_start_end,                               //游戏结束
	msg_start_again,                             //再来一盘

	msg_take_next,                               //下棋
	msg_beg_peace,                               //请求求和
	msg_beg_back ,                               //请求悔棋

	msg_get_win,                                //赢棋
	mgs_lose_win,                               //输棋

	msg_peace_succeed,                         //同意求和
	msg_peace_failed ,                         //不同意求和
	msg_back_succeed,                          //同意悔棋
	msg_back_failed                            //不同意悔棋

};
using msg_code =int16;

//二维数组的的坐标（x,y)
typedef struct location
{
	int16 gobang_x;
	int16 gobang_y;
}msg_location;

//extra data(还没决定）

typedef struct message_pack
{
	msg_code code;
	msg_location site;
	char data[508];	
}msg_pack,*ptr_msg_pack;



class parse_pack


{
   public:
  parse_pack()
  { 
	  this->ptr = new msg_pack();
	  memset(this->ptr, 0, sizeof(msg_pack));
  }
  virtual ~parse_pack()
  {
	  my_delete(this->ptr);
	  this->ptr = nullptr;
  }

  inline void SetMsgCode(int16 temp)
  {
	  this->ptr->code = temp;

  }
  inline void SeMsgCode(ptr_msg_pack pack)
  {
	  this->ptr->code = pack->code;
  }
  inline void SetMsgSite(int16 xtemp,int16 ytemp)
  {
	  this->ptr->site.gobang_x = xtemp;
	  this->ptr->site.gobang_y = ytemp;
  }
  inline void SetMsgSite(ptr_msg_pack pack)
  {
	  this->ptr->site.gobang_x = pack->site.gobang_x;
	  this->ptr->site.gobang_y = pack->site.gobang_y;
  }
  inline void SetMsgData(char const*temp)
  {
	  strcpy(this->ptr->data, temp);
  }
  inline void SetMsgData(ptr_msg_pack pack)
  {
	  strcpy(this->ptr->data, pack->data);
  }
public:
  inline int16 GetCode()
  {
	  return this->ptr->code;
  }
  inline int16 GetCode(ptr_msg_pack pack)
  {
	  return pack->code;
  }
  inline msg_location GetSite()
  {
	  return this->ptr->site;
  }
  inline msg_location GetSite(ptr_msg_pack pack)
  {
	  return pack->site;
  }
  inline char const*GetData()
  {
	  return this->ptr->data;
  }
  inline char const*GetData(ptr_msg_pack pack)
  {
	  return pack->data;
  }
  protected:



  private:
	  ptr_msg_pack  ptr;

};

my_namespace_end