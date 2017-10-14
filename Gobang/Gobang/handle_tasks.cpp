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


//��ʼ��Ϸ
void handle_tasks::HandleSartGame()                                                   
{

}

//������Ϸ
void handle_tasks::HandleEndGame()                                                    
{

}

//����һ��
void handle_tasks::HandleTryAgain()                                                    
{

}

//��������
void handle_tasks::HanldeTakeNext(msg_location enemy_location)                         
{
	GobangMap[enemy_location.gobang_x][enemy_location.gobang_y] = -1;
	ptr_site->admin = true;
}

//�������
bool handle_tasks::HandleBegPeace()                                                    
{

	return true;
}

//ͬ�����
void handle_tasks::HandleAgreeBegPeace(Socket*w_h_socket)                            
{
	w_h_socket->GetRecvPack()->code = msg_peace_succeed;
	w_h_socket->SendMsgPack();
}

//��ͬ�����
void  handle_tasks::HandleDisagreeBegPeace(Socket*w_h_socket)                         
{
	w_h_socket->GetRecvPack()->code=msg_peace_failed;
	w_h_socket->SendMsgPack();
}

//�������
bool handle_tasks::HandleBegBack()                                                   
{
	return true;
}

//ͬ�����
void  handle_tasks::HandleAgreeBegBack(Socket*w_h_socket)                             
{
	w_h_socket->GetRecvPack()->code = msg_back_succeed;
	w_h_socket->SendMsgPack();
	Gobang_Task_Back(ptr_site);
}

//��ͬ�����
void handle_tasks::HandleDisagreeBegBack(Socket*w_h_socket)                          
{
	w_h_socket->SendMsgPack();
	w_h_socket->GetRecvPack()->code = msg_back_failed;
}

//����Ӯ��
void handle_tasks::HandleWin()                                                       
{

}

//��������
void handle_tasks::HandleLose()                                                      
{

}

my_namespace_end