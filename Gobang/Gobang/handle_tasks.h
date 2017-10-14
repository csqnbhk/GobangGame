
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
//	msg_start_game = -21555,                  //��ʼ��Ϸ
//	msg_start_end,                           //��Ϸ����
//	msg_start_again,                         //����һ��
//
//	msg_take_next,                           //����
//	msg_beg_peace,                           //�������
//	msg_beg_back,                            //�������
//
//	msg_get_win,                            //Ӯ��
//	mgs_lose_win,                           //����
//
//	msg_peace_succeed,                      //ͬ�����
//	msg_peace_failed,                       //��ͬ�����
//	msg_back_succeed,                      //ͬ�����
//	msg_back_failed                        //��ͬ�����
//
//};

class handle_tasks
{

public:
	handle_tasks();
	virtual ~handle_tasks() noexcept;

public:
	void HandleSartGame();                                     //��ʼ��Ϸ
	void HandleEndGame();                                      //������Ϸ
	void HandleTryAgain();                                     //����һ��
	void HanldeTakeNext(msg_location enemy_location);          //��������

	bool HandleBegPeace();                                     //�������
	void HandleAgreeBegPeace(Socket*w_h_socket);               //ͬ�����
	void HandleDisagreeBegPeace(Socket*w_h_socket);            //��ͬ�����

	bool HandleBegBack();                                      //�������
	void HandleAgreeBegBack(Socket*w_h_socket);                //ͬ�����
	void HandleDisagreeBegBack(Socket*w_h_socket);             //��ͬ�����
	void HandleWin();                                          //����Ӯ��
	void HandleLose();                                         //��������
public:
	static handle_tasks*GetInstance();
private:
	static handle_tasks*ptr_tasks;


};
my_namespace_end