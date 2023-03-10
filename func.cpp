#include"func.h"
using namespace std;

unsigned long long GetOneHash(int i, int j)
{
	int temp = 0;
	if (board[i][j] > 0)
	{
		temp = 7 + board[i][j];
	}
	else if(board[i][j] < 0)
	{
		temp = -board[i][j];
	}
	if (temp == 0)
		return 0;
	return RAND[(9*i+j)*15+temp];
}

unsigned long long MyHashes()
{
	unsigned long long temp = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(board[i][j]!=0)
				temp ^= GetOneHash(i, j);
		}
	}
	return temp;
}

unsigned long long GetOneVerify(int i, int j)
{
	int temp = 0;
	if (board[i][j] > 0)
	{
		temp = 7 + board[i][j];
	}
	else if (board[i][j] < 0)
	{
		temp = -board[i][j];
	}
	if (temp == 0)
		return 0;
	return V_RAND[(9 * i + j) * 15 + temp];
}

unsigned long long MyVerifyCode()
{
	unsigned long long temp = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(board[i][j]!=0)
				temp ^= GetOneVerify(i, j);
		}
	}
	return temp;
}
Stage::Stage()
{
	depth = 0;
	value = 0;
	verify = 0;

}
Stage::Stage(char a, short b, unsigned long long c)
{
	depth = a;
	value = b;
	verify = c;
}

movechess::movechess(char a, char b, char c, char d, short e) : x(a), y(b), move_x(c), move_y(d), val(e)
{

}
bool movechess::operator<(movechess a) const
{
	return val > a.val;
}

bool isdefeat(int flag)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if (board[i][j] == 5 * flag) return false;
	return true;
}
bool ismeet()/* 判断两边老将是否碰面  */
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

bool isin(int i, int j)
{
	return 0 <= i && i < 10 && 0 <= j && j < 9;
}
void show_move()
{
	int q = abs(type);
	if (side == RED)
	{
		cout << "红方" << " ";
		cout << chess_names[q] << 9 - n  << "到" << 9 - n - toy << endl;
	}
		
	else
	{
		cout << "黑方" << " ";
		cout << chess_names[q] << n + 1 << "到" << n + toy + 1 << endl;
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
//渴望搜索
int eager_find(int layer, int target, int lwindow, int rwindow, int flag)
{
	clock_t time_start = clock();
	mylayer = layer;
	int q = find(flag, 0, target - lwindow, target + rwindow);
	if (q <= -9900 || q >= 9900)
	{
		clock_t time_end = clock();
		cout << layer << "层time use:" << 1000 * (int)(time_end - time_start) / (double)CLOCKS_PER_SEC << "ms " << layer << "层估值：" << q << endl;
		show_move();
		show();
		cout << endl;
		return q;
	}
	if (q <= target - lwindow)
	{
		REDValues.clear();
		BLACKValues.clear();
		cout << layer << "层搜索值为:" << q << "  再搜索一次区间左侧" << endl;
		q = find(flag, 0, -10000, target - lwindow);
		
	}
	else if (q >= target + rwindow)
	{
		REDValues.clear();
		BLACKValues.clear();
		cout << layer << "层搜索值为:" << q << "再搜索一次区间右侧" << endl;
		q = find(flag, 0, target + rwindow, 10000);
	}
	clock_t time_end = clock();
	cout << layer << "层time use:" << 1000 * (int)(time_end - time_start) / (double)CLOCKS_PER_SEC << "ms " << layer << "层估值：" << q << endl;
	if (q <= -9900 || q >= 9900)
	{
		show_move();
		show();
		cout << endl;
		return q;
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
	//时间超过2秒就停止继续深入寻找
	if (1000 * (int)(time_end - time_start) / (double)CLOCKS_PER_SEC >= 2000)
	{
		show_move();
		show();
		cout << endl;
		return q;
	}
	else
	{
		int temp = (70 - 15 * layer) > 30 ? (70 - 15 * layer) : 30;
		return eager_find(layer + 2, q, temp, temp, flag);
	}
		
}