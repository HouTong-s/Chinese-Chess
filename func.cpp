#include"func.h"
using namespace std;
bool isdefeat(int flag)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if (b[i][j] == 5 * flag) return false;
	return true;
}
bool ismeet()/* 判断两边老将是否碰面  */
{
	if (redx != blackx) return false;
	else
	{
		for (int i = blacky + 1; i < redy; i++)
		{
			if (b[i][redx] != 0) return false;
		}
		return true;
	}
}
void cut(int layer, int r, int i, int j, int& alpha, int& beta, int a, int b, int ty, int& current)
{
	if (layer == 0)/*    第一层返回下一步招法，第一层不可能有分支被剪掉（如果beta为无穷）(如果为渴望搜索算法，则有可能会剪枝)  */
	{
		//第一步选择
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
					cout << ty<<" "<<""<<j+1<<"到"<<j+1+b<<"和"<<i+a+1<<" "<<r << endl;
				}*/
		else if (r == current)
		{
			if (rand() % 100 == 0)
			{
				m = i;
				n = j;
				tox = a;
				toy = b;
				type = ty;
			}
		}
		current = current > r ? current : r;
		alpha = alpha > r ? alpha : r;/*    alpha剪枝      */
	}
	else if (layer % 2 == 0)
	{
		current = current > r ? current : r;
		alpha = alpha > r ? alpha : r;/*    alpha剪枝      */
	}
	else
	{
		current = current < r ? current : r;
		beta = r < beta ? r : beta;/*    beta剪枝      */
	}
}
bool isin(int i, int j)
{
	return 0 <= i && i < 10 && 0 <= j && j < 9;
}
void show_AND_make_move()
{
	if (side == RED)
		cout << "红方" << " ";
	else
		cout << "黑方" << " ";
	int q = abs(type);
	cout << name1[q] << n + 1 << "到" << n + toy + 1 << endl;
	b[m][n] = 0;
	b[m + tox][n + toy] = type;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
		{
			if (b[i][j] == 5)
			{
				redx = j;
				redy = i;
			}
			else if (b[i][j] == -5)
			{
				blackx = j;
				blacky = i;
			}
		}
}

void show()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{		
			if(b[i][j]<0)
				cout << "\033[30;1m"<< name1[-b[i][j]] <<"\033[0m"<< " ";
			else
			{
				cout << "\033[31;1m" << name1[b[i][j]] << "\033[0m" << " ";
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
	if (q == -10000)
	{
		if (side == RED)
			cout << "红方";
		else
			cout << "黑方";
		cout << "认输！";
		return -10000;
	}
	if (q <= target - lwindow)
	{
		cout << layer << "层搜索值为:" << q << "  再搜索一次区间左侧" << endl;
		q = find(flag, 0, -10000, target - lwindow);
	}
	else if (q >= target + rwindow)
	{
		cout << layer << "层搜索值为:" << q << "再搜索一次区间右侧" << endl;
		q = find(flag, 0, target + rwindow, 10000);
	}
	clock_t time_end = clock();
	cout << layer << "层time use:" << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms " << layer << "层估值：" << q << endl;
	if (q == -10000)
	{
		if (side == RED)
			cout << "红方";
		else
			cout << "黑方";
		cout << "认输！";
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
	if (1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC >= 2000)
	{
		show_AND_make_move();
		show();
		cout << endl;
		return q;
	}
	else
	{
		int temp = (70 - 10 * layer) > 10 ? (70 - 10 * layer) : 10;
		return eager_find(layer + 2, q, 20, 20, flag);
	}
		
}