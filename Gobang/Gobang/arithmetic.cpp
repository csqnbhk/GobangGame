#include"arithmetic.h"

my_namespace_begin

//遍历查看
void Gobang_Array_Draw()
{

	for (auto x : GobangMap)
	{
		for (auto val : GobangMap)
			switch (*val)
			{
			case ENEMY:  //绘制敌方棋子
				break;
			case EMPTY:  //不做处理，此时鼠标的移动到此处会有（可以下棋子的变图）
				break;
			case SELF:   //绘制自身棋子
				break;
			default:
				break;
			}

	}

}

//悔棋
void Gobang_Task_Back(ptr_late_site ptr)
{


	//第一种情况：对方已经下棋，本方还没有下（此时是本方下）（此时只要改变对方上步的下棋，置上次的位置为0，并把下棋权限交给对方）
	if (ptr->admin == true)
	{

		GobangMap[ptr->enemty_x][ptr->enemty_y] = 0;
	}
	//第二种情况:本方已经下了（此时轮到对方下）（此时要改变本方上次下棋和对方上次的下棋，并把下棋权限交给对方）
	else
	{
		GobangMap[ptr->enemty_x][ptr->enemty_y] = 0;
		GobangMap[ptr->self_x][ptr->self_y] = 0;
	}
	ptr->admin = false;
}

//判断输赢
int Gobang_Jude_Win()
{
	for (int x = 0;x<Row;x++)
	{
		for (int y = 0;y<Line;y++)
		{
			
			int val = GobangMap[x][y];

			//1.左边
			if (x >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x - 1][y]) && (val == GobangMap[x - 2][y]) && (val == GobangMap[x - 3][y]) && (val == GobangMap[x - 4][y]))
					return GobangMap[x][y];
			}

			//2.右边
			if (x <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x + 1][y]) && (val == GobangMap[x + 2][y]) && (val == GobangMap[x + 3][y]) && (val == GobangMap[x + 4][y]))
					return GobangMap[x][y];
			}

			//3.上边
			if (y >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x][y - 1]) && (val == GobangMap[x][y - 2]) && (val == GobangMap[x][y - 3]) && (val == GobangMap[x][y - 4]))
					return GobangMap[x][y];
			}

			//4.下边
			if (y <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x][y + 1]) && (val == GobangMap[x][y + 2]) && (val == GobangMap[x][y + 3]) && (val == GobangMap[x][y + 4]))
					return GobangMap[x][y];
			}

			//5.左斜上
			if (x >= 4 && y >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x - 1][y - 1]) && (val == GobangMap[x - 2][y - 2]) && (val == GobangMap[x - 3][y - 3]) && (val == GobangMap[x - 4][y - 4]))
					return GobangMap[x][y];
			}

			//6.左斜下
			if (x >= 4 && y <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x - 1][y + 1]) && (val == GobangMap[x - 2][y + 2]) && (val == GobangMap[x - 3][y + 3]) && (val == GobangMap[x - 4][y + 4]))
					return GobangMap[x][y];
			}

			//7.右斜上
			if (x <= 10 && y >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x + 1][y - 1]) && (val == GobangMap[x + 2][y - 2]) && (val == GobangMap[x + 3][y - 3]) && (val == GobangMap[x + 4][y - 4]))
					return GobangMap[x][y];

			}

			//8.右斜下
			if (x <= 10 && y <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x + 1][y + 1]) && (val == GobangMap[x + 2][y + 2]) && (val == GobangMap[x + 3][y + 3]) && (val == GobangMap[x + 4][y + 4]))
				return GobangMap[x][y];
			}
		}

	}
	return 0;

}


my_namespace_end
