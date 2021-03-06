#include"handle_tasks.h"
my_namespace_begin
///**************************************************************************/
 handle_tasks*handle_tasks::ptr_tasks=nullptr;
 handle_tasks*handle_tasks::GetInstance()
{
	if (ptr_tasks == nullptr)
	ptr_tasks = new handle_tasks();
	return ptr_tasks;
}

/************************************************************************/
 handle_tasks::handle_tasks()
 {


 }

 handle_tasks::~handle_tasks()
 {



 }


//开始游戏
void handle_tasks::HandleSartGame()                                                   
{

}

//结束游戏
void handle_tasks::HandleEndGame()                                                    
{

}

//再来一盘
void handle_tasks::HandleTryAgain()                                                    
{

}

//处理下棋
void handle_tasks::HanldeTakeNext(msg_location enemy_location)                         
{
	GobangMap[enemy_location.gobang_x][enemy_location.gobang_y] = -1;
	ptr_site->admin = true;
}

//请求求和
bool handle_tasks::HandleBegPeace(Socket*w_h_socket)
{
	if (MessageBox(0, TEXT("对方向你发出求和请求，是否同意？"), TEXT("求和提示"), MB_YESNO | MB_ICONWARNING) == IDYES)
	{
		this->HandleAgreeBegPeace(w_h_socket);
		return true;
	}
	else
	{
		this->HandleDisagreeBegPeace(w_h_socket);
		return false;
	}
}

//同意求和
void handle_tasks::HandleAgreeBegPeace(Socket*w_h_socket)                            
{
	w_h_socket->GetRecvPack()->code = msg_peace_succeed;
	w_h_socket->SendMsgPack();
}

//不同意求和
void  handle_tasks::HandleDisagreeBegPeace(Socket*w_h_socket)                         
{
	w_h_socket->GetRecvPack()->code=msg_peace_failed;
	w_h_socket->SendMsgPack();
}

//请求悔棋
bool handle_tasks::HandleBegBack(Socket*w_h_socket)
{
	if (MessageBox(0, TEXT("对方向你发出悔棋请求，是否同意？"), TEXT("悔棋提示"), MB_YESNO | MB_ICONWARNING) == IDYES)
	{
		this->HandleAgreeBegBack(w_h_socket);
		return true;
	}
	else
	{
		this->HandleDisagreeBegBack(w_h_socket);
		return false;
	}
}

//同意悔棋
void  handle_tasks::HandleAgreeBegBack(Socket*w_h_socket)                             
{
	w_h_socket->GetRecvPack()->code = msg_back_succeed;
	w_h_socket->SendMsgPack();
	Gobang_Task_Back(ptr_site);
}

//不同意悔棋
void handle_tasks::HandleDisagreeBegBack(Socket*w_h_socket)                          
{
	w_h_socket->SendMsgPack();
	w_h_socket->GetRecvPack()->code = msg_back_failed;
}

//处理赢棋
void handle_tasks::HandleWin()                                                       
{

}

//处理输棋
void handle_tasks::HandleLose()                                                      
{

}

my_namespace_end