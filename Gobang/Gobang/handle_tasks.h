
/****************************************************************

function:this file is used to handle messages
author:Demon
Time:2017/10/2

***************************************************************/
#pragma once
#include"precompiled_header.h"
#include"arithmetic.h"
#include"client.h"
my_namespace_begin
//enum
//{
//	msg_start_game = -21555,                  //开始游戏
//	msg_start_end,                           //游戏结束
//	msg_start_again,                         //再来一盘
//
//	msg_take_next,                           //下棋
//	msg_beg_peace,                           //请求求和
//	msg_beg_back,                            //请求悔棋
//
//	msg_get_win,                            //赢棋
//	mgs_lose_win,                           //输棋
//
//	msg_peace_succeed,                      //同意求和
//	msg_peace_failed,                       //不同意求和
//	msg_back_succeed,                      //同意悔棋
//	msg_back_failed                        //不同意悔棋
//
//};

class handle_tasks
{

public:
	handle_tasks();
	virtual ~handle_tasks() noexcept;

public:
	void HandleSartGame();                                     //开始游戏
	void HandleEndGame();                                      //结束游戏
	void HandleTryAgain();                                     //再来一盘
	void HanldeTakeNext(msg_location enemy_location);          //处理下棋

	bool HandleBegPeace();                                     //请求求和
	void HandleAgreeBegPeace(Socket*w_h_socket);               //同意求和
	void HandleDisagreeBegPeace(Socket*w_h_socket);            //不同意求和

	bool HandleBegBack();                                      //请求悔棋
	void HandleAgreeBegBack(Socket*w_h_socket);                //同意悔棋
	void HandleDisagreeBegBack(Socket*w_h_socket);             //不同意悔棋
	void HandleWin();                                          //处理赢棋
	void HandleLose();                                         //处理输棋
public:
	static handle_tasks*GetInstance();
private:
	static handle_tasks*ptr_tasks;


};
my_namespace_end