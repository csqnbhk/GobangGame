/***********************************************************************

              function:this file is used to realize Gobang's arithmetic
			  author:Demon
			  Time:2017/10/5~

*************************************************************************/
#pragma once
#include"precompiled_header.h"
extern int GobangMap[Row][Line];

my_namespace_begin
/*************************************************************************/
//�����鿴
void Gobang_Array_Draw();
//����
void Gobang_Task_Back(ptr_late_site ptr);
//�ж���Ӯ(����ֵ����Ӯ�ң�
int Gobang_Jude_Win();

my_namespace_end
