#include"arithmetic.h"

my_namespace_begin

//�����鿴
void Gobang_Array_Draw()
{

	for (auto x : GobangMap)
	{
		for (auto val : GobangMap)
			switch (*val)
			{
			case ENEMY:  //���Ƶз�����
				break;
			case EMPTY:  //����������ʱ�����ƶ����˴����У����������ӵı�ͼ��
				break;
			case SELF:   //������������
				break;
			default:
				break;
			}

	}

}

//����
void Gobang_Task_Back(ptr_late_site ptr)
{


	//��һ��������Է��Ѿ����壬������û���£���ʱ�Ǳ����£�����ʱֻҪ�ı�Է��ϲ������壬���ϴε�λ��Ϊ0����������Ȩ�޽����Է���
	if (ptr->admin == true)
	{

		GobangMap[ptr->enemty_x][ptr->enemty_y] = 0;
	}
	//�ڶ������:�����Ѿ����ˣ���ʱ�ֵ��Է��£�����ʱҪ�ı䱾���ϴ�����ͶԷ��ϴε����壬��������Ȩ�޽����Է���
	else
	{
		GobangMap[ptr->enemty_x][ptr->enemty_y] = 0;
		GobangMap[ptr->self_x][ptr->self_y] = 0;
	}
	ptr->admin = false;
}

//�ж���Ӯ
int Gobang_Jude_Win()
{
	for (int x = 0;x<Row;x++)
	{
		for (int y = 0;y<Line;y++)
		{
			
			int val = GobangMap[x][y];

			//1.���
			if (x >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x - 1][y]) && (val == GobangMap[x - 2][y]) && (val == GobangMap[x - 3][y]) && (val == GobangMap[x - 4][y]))
					return GobangMap[x][y];
			}

			//2.�ұ�
			if (x <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x + 1][y]) && (val == GobangMap[x + 2][y]) && (val == GobangMap[x + 3][y]) && (val == GobangMap[x + 4][y]))
					return GobangMap[x][y];
			}

			//3.�ϱ�
			if (y >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x][y - 1]) && (val == GobangMap[x][y - 2]) && (val == GobangMap[x][y - 3]) && (val == GobangMap[x][y - 4]))
					return GobangMap[x][y];
			}

			//4.�±�
			if (y <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x][y + 1]) && (val == GobangMap[x][y + 2]) && (val == GobangMap[x][y + 3]) && (val == GobangMap[x][y + 4]))
					return GobangMap[x][y];
			}

			//5.��б��
			if (x >= 4 && y >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x - 1][y - 1]) && (val == GobangMap[x - 2][y - 2]) && (val == GobangMap[x - 3][y - 3]) && (val == GobangMap[x - 4][y - 4]))
					return GobangMap[x][y];
			}

			//6.��б��
			if (x >= 4 && y <= 10 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x - 1][y + 1]) && (val == GobangMap[x - 2][y + 2]) && (val == GobangMap[x - 3][y + 3]) && (val == GobangMap[x - 4][y + 4]))
					return GobangMap[x][y];
			}

			//7.��б��
			if (x <= 10 && y >= 4 && (GobangMap[x][y] == -1 || GobangMap[x][y] == 1))
			{
				if ((val == GobangMap[x + 1][y - 1]) && (val == GobangMap[x + 2][y - 2]) && (val == GobangMap[x + 3][y - 3]) && (val == GobangMap[x + 4][y - 4]))
					return GobangMap[x][y];

			}

			//8.��б��
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
