#include"func.h"
using namespace std;
bool isdefeat(int flag)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if (board[i][j] == 5 * flag) return false;
	return true;
}
bool ismeet()/* �ж������Ͻ��Ƿ�����  */
{
	if (red_y != black_y) return false;
	else
	{
		for (int i = black_x + 1; i < red_x; i++)
		{
			if (board[i][red_y] != 0) return false;
		}
		return true;
	}
}
void cut(int layer, int r, int i, int j, int& alpha, int& beta, int a, int b, int ty, int& current)
{
	if (layer == 0)/*    ��һ�㷵����һ���з�����һ�㲻�����з�֧�����������betaΪ���(���Ϊ���������㷨�����п��ܻ��֦)  */
	{
		//��һ��ѡ��
		if (is_firststep == 0)
		{
			m = i;
			n = j;
			tox = a;
			toy = b;
			type = ty;
			is_firststep = 1;
		}
		else if (r > current)
		{
			m = i;
			n = j;
			tox = a;
			toy = b;
			type = ty;
		}
		/*		if (r == current)
				{
					cout << ty<<" "<<""<<j+1<<"��"<<j+1+b<<"��"<<i+a+1<<" "<<r << endl;
				}*/
		else if (r == current)
		{
			if (rand() % 200 == 0)
			{
				m = i;
				n = j;
				tox = a;
				toy = b;
				type = ty;
			}
		}
		current = current > r ? current : r;
		alpha = alpha > r ? alpha : r;/*    alpha��֦      */
	}
	else if (layer % 2 == 0)
	{
		current = current > r ? current : r;
		alpha = alpha > r ? alpha : r;/*    alpha��֦      */
	}
	else
	{
		current = current < r ? current : r;
		beta = r < beta ? r : beta;/*    beta��֦      */
	}
}
bool isin(int i, int j)
{
	return 0 <= i && i < 10 && 0 <= j && j < 9;
}
void show_AND_make_move()
{
	int q = abs(type);
	if (side == RED)
	{
		cout << "�췽" << " ";
		cout << chess_names[q] << 9 - n  << "��" << 9 - n - toy << endl;
	}
		
	else
	{
		cout << "�ڷ�" << " ";
		cout << chess_names[q] << n + 1 << "��" << n + toy + 1 << endl;
	}
	
	board[m][n] = 0;
	board[m + tox][n + toy] = type;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 5)
			{
				red_y = j;
				red_x = i;
			}
			else if (board[i][j] == -5)
			{
				black_y = j;
				black_x = i;
			}
		}
}

void show()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{		
			if(board[i][j]<0)
				cout << "\033[30;1m"<< chess_names[-board[i][j]] <<"\033[0m"<< " ";
			else
			{
				cout << "\033[31;1m" << chess_names[board[i][j]] << "\033[0m" << " ";
			}
		}
		cout << endl;
	}
}
//��������
int eager_find(int layer, int target, int lwindow, int rwindow, int flag)
{
	clock_t time_start = clock();
	mylayer = layer;
	int q = find(flag, 0, target - lwindow, target + rwindow);
	if (q == -10000)
	{
		if (side == RED)
			cout << "�췽";
		else
			cout << "�ڷ�";
		cout << "���䣡";
		return -10000;
	}
	if (q <= target - lwindow)
	{
		cout << layer << "������ֵΪ:" << q << "  ������һ���������" << endl;
		q = find(flag, 0, -10000, target - lwindow);
	}
	else if (q >= target + rwindow)
	{
		cout << layer << "������ֵΪ:" << q << "������һ�������Ҳ�" << endl;
		q = find(flag, 0, target + rwindow, 10000);
	}
	clock_t time_end = clock();
	cout << layer << "��time use:" << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms " << layer << "���ֵ��" << q << endl;
	if (q == -10000)
	{
		if (side == RED)
			cout << "�췽";
		else
			cout << "�ڷ�";
		cout << "���䣡";
		return -10000;
	}
	/*
	if (layer == 4)
	{
		show_AND_make_move();
		show();
		cout << endl;
		return q;
	}
	*/
	//ʱ�䳬��2.5���ֹͣ��������Ѱ��
	if (1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC >= 2500)
	{
		show_AND_make_move();
		show();
		cout << endl;
		return q;
	}
	else
	{
		int temp = (80 - 15 * layer) > 10 ? (80 - 15 * layer) : 10;
		return eager_find(layer + 2, q, temp, temp, flag);
	}
		
}