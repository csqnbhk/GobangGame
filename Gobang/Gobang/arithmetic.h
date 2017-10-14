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
//遍历查看
void Gobang_Array_Draw();
//悔棋
void Gobang_Task_Back(ptr_late_site ptr);
//判断输赢(返回值代表赢家）
int Gobang_Jude_Win();

my_namespace_end
