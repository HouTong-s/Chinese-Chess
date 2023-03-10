#include"func.h"
using namespace std;

void MakeMove(std::vector<movechess>::iterator i,int& origin,int & prechess,char flag)
{
	if (board[i->x][i->y] == 5 * flag)//如果是遍历的老将，要改变记录老将的横纵坐标，以确定两边老将是否相遇
	{
		if (flag == 1)
		{
			red_y = i->y + i->move_y;
			red_x = i->x + i->move_x;
		}
		else
		{
			black_y = i->y + i->move_y;
			black_x = i->x + i->move_x;
		}
	}
	boardkey ^= GetOneHash(i->x, i->y);
	boardkey ^= GetOneHash(i->x + i->move_x , i->y + i->move_y);
	verifykey ^= GetOneVerify(i->x, i->y);
	verifykey ^= GetOneVerify(i->x + i->move_x, i->y + i->move_y);
	origin = board[i->x + i->move_x][i->y + i->move_y];
	prechess = board[i->x][i->y];
	board[i->x + i->move_x][i->y + i->move_y] = board[i->x][i->y];
	board[i->x][i->y] = 0;
	boardkey ^= GetOneHash(i->x + i->move_x, i->y + i->move_y);
	verifykey ^= GetOneVerify(i->x + i->move_x, i->y + i->move_y);
}
void UnMove(std::vector<movechess>::iterator i, int origin, int prechess, char flag)
{
	board[i->x][i->y] = prechess;
	board[i->x + i->move_x][i->y + i->move_y] = origin;
	if (board[i->x][i->y] == 5 * flag)//如果是遍历的老将，要回溯老将的横纵坐标，以确定两边老将是否相遇
	{
		if (flag == 1)
		{
			red_y = i->y;
			red_x = i->x;
		}
		else
		{
			black_y = i->y;
			black_x = i->x;
		}
	}
}
void generateMove(vector<movechess>& arr,char flag)
{
	int origin, g;
	for (char i = 0; i < 10; i++)/* 随机取点开始 */
	{
		for (char j = 0; j < 9; j++)
		{
			if (board[i][j] == flag)/*     车遍历方法开始(四个方向)      */
			{
				for (g = 1; g < 10; g++)
				{
					if (!isin(i + g, j) || board[i + g][j] * flag > 0) break;
					if (isin(i + g, j))
					{
						origin = board[i + g][j];
						board[i + g][j] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						board[i][j] = flag;
						board[i + g][j] = origin;
						if (board[i + g][j] * flag < 0) break;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (!isin(i + g, j) || board[i + g][j] * flag > 0) break;
					if (isin(i + g, j))
					{
						origin = board[i + g][j];
						board[i + g][j] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						board[i][j] = flag;
						board[i + g][j] = origin;
						if (board[i + g][j] * flag < 0) break;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (!isin(i, j + g) || board[i][j + g] * flag > 0) break;
					if (isin(i, j + g))
					{
						origin = board[i][j + g];
						board[i][j + g] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						board[i][j] = flag;
						board[i][j + g] = origin;
						if (board[i][j + g] * flag < 0) break;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (!isin(i, j + g) || board[i][j + g] * flag > 0) break;
					if (isin(i, j + g))
					{
						origin = board[i][j + g];
						board[i][j + g] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						board[i][j] = flag;
						board[i][j + g] = origin;
						if (board[i][j + g] * flag < 0) break;
					}
				}
			}/*      车遍历到此为止       */
			else if (board[i][j] == 2 * flag)/*    马遍历开始(八面威风)      */
			{
				if (isin(i + 1, j) && board[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && board[i + 2][j + 1] * flag <= 0)
					{
						origin = board[i + 2][j + 1];
						board[i + 2][j + 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 2, 1, getvalue()));
						board[i][j] = 2 * flag;
						board[i + 2][j + 1] = origin;
					}
					if (isin(i + 2, j - 1) && board[i + 2][j - 1] * flag <= 0)
					{
						origin = board[i + 2][j - 1];
						board[i + 2][j - 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 2, -1, getvalue()));
						board[i][j] = 2 * flag;
						board[i + 2][j - 1] = origin;
					}
				}
				if (isin(i - 1, j) && board[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && board[i - 2][j + 1] * flag <= 0)
					{
						origin = board[i - 2][j + 1];
						board[i - 2][j + 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, -2, 1, getvalue()));
						board[i][j] = 2 * flag;
						board[i - 2][j + 1] = origin;
					}
					if (isin(i - 2, j - 1) && board[i - 2][j - 1] * flag <= 0)
					{
						origin = board[i - 2][j - 1];
						board[i - 2][j - 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, -2, -1, getvalue()));
						board[i][j] = 2 * flag;
						board[i - 2][j - 1] = origin;
					}
				}
				if (isin(i, j - 1) && board[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && board[i - 1][j - 2] * flag <= 0)
					{
						origin = board[i - 1][j - 2];
						board[i - 1][j - 2] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, -2, getvalue()));
						board[i][j] = 2 * flag;
						board[i - 1][j - 2] = origin;
					}
					if (isin(i + 1, j - 2) && board[i + 1][j - 2] * flag <= 0)
					{
						origin = board[i + 1][j - 2];
						board[i + 1][j - 2] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, -2, getvalue()));
						board[i][j] = 2 * flag;
						board[i + 1][j - 2] = origin;
					}
				}
				if (isin(i, j + 1) && board[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && board[i - 1][j + 2] * flag <= 0)
					{
						origin = board[i - 1][j + 2];
						board[i - 1][j + 2] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, 2, getvalue()));
						board[i][j] = 2 * flag;
						board[i - 1][j + 2] = origin;
					}
					if (isin(i + 1, j + 2) && board[i + 1][j + 2] * flag <= 0)
					{
						origin = board[i + 1][j + 2];
						board[i + 1][j + 2] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, 2, getvalue()));
						board[i][j] = 2 * flag;
						board[i + 1][j + 2] = origin;
					}
				}
			}/*    马遍历结束    */
			else if (board[i][j] == 3 * flag)/*    象遍历开始    */
			{
				if (isin(i + 1, j + 1) && board[i + 1][j + 1] == 0 && board[i + 2][j + 2] * flag <= 0 && (flag == 1 && i + 2 >= 5 || flag == -1 && i + 2 < 5))/* 象不过河 */
				{
					origin = board[i + 2][j + 2];
					board[i + 2][j + 2] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, 2, 2, getvalue()));
					board[i][j] = 3 * flag;
					board[i + 2][j + 2] = origin;
				}
				if (isin(i + 1, j - 1) && board[i + 1][j - 1] == 0 && board[i + 2][j - 2] * flag <= 0 && (flag == 1 && i + 2 >= 5 || flag == -1 && i + 2 < 5))
				{
					origin = board[i + 2][j - 2];
					board[i + 2][j - 2] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, 2, -2, getvalue()));
					board[i][j] = 3 * flag;
					board[i + 2][j - 2] = origin;
				}
				if (isin(i - 1, j + 1) && board[i - 1][j + 1] == 0 && board[i - 2][j + 2] * flag <= 0 && (flag == 1 && i - 2 >= 5 || flag == -1 && i - 2 < 5))
				{
					origin = board[i - 2][j + 2];
					board[i - 2][j + 2] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, -2, 2, getvalue()));
					board[i][j] = 3 * flag;
					board[i - 2][j + 2] = origin;
				}
				if (isin(i - 1, j - 1) && board[i - 1][j - 1] == 0 && board[i - 2][j - 2] * flag <= 0 && (flag == 1 && i - 2 >= 5 || flag == -1 && i - 2 < 5))
				{
					origin = board[i - 2][j - 2];
					board[i - 2][j - 2] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, -2, -2, getvalue()));
					board[i][j] = 3 * flag;
					board[i - 2][j - 2] = origin;
				}
			}/*   象遍历结束   */
			else if (board[i][j] == 4 * flag)/*  士遍历开始 */
			{
				int midx;
				int midy = 4;
				if (flag == 1)	midx = 8;
				else midx = 1;
				if (i == midx && j == midy)
				{
					if (board[i + 1][j + 1] * flag <= 0)
					{
						origin = board[i + 1][j + 1];
						board[i + 1][j + 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, 1, getvalue()));
						board[i][j] = 4 * flag;
						board[i + 1][j + 1] = origin;
					}
					if (board[i - 1][j + 1] * flag <= 0)
					{
						origin = board[i - 1][j + 1];
						board[i - 1][j + 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, 1, getvalue()));
						board[i][j] = 4 * flag;
						board[i - 1][j + 1] = origin;
					}
					if (board[i + 1][j - 1] * flag <= 0)
					{
						origin = board[i + 1][j - 1];
						board[i + 1][j - 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, -1, getvalue()));
						board[i][j] = 4 * flag;
						board[i + 1][j - 1] = origin;
					}
					if (board[i - 1][j - 1] * flag <= 0)
					{
						origin = board[i - 1][j - 1];
						board[i - 1][j - 1] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, -1, getvalue()));
						board[i][j] = 4 * flag;
						board[i - 1][j - 1] = origin;
					}
				}
				else if (board[midx][midy] * flag <= 0)
				{
					origin = board[midx][midy];
					board[midx][midy] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, midx - i, midy - j, getvalue()));
					board[i][j] = 4 * flag;
					board[midx][midy] = origin;
				}
			}/* 士遍历结束 */
			else if (board[i][j] == 5 * flag)/* 将遍历开始 */
			{
				int midx;
				if (flag == 1)	midx = 8;
				else midx = 1;
				if (isin(i + 1, j) && board[i + 1][j] * flag <= 0 && midx - 1 <= i + 1 && i + 1 <= midx + 1)
				{
					origin = board[i + 1][j];
					board[i + 1][j] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, 1, 0, getvalue()));
					board[i][j] = 5 * flag;
					board[i + 1][j] = origin;
				}
				if (isin(i, j + 1) && board[i][j + 1] * flag <= 0 && 3 <= j + 1 && j + 1 <= 5)
				{
					origin = board[i][j + 1];
					board[i][j + 1] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, 0, 1, getvalue()));
					board[i][j] = 5 * flag;
					board[i][j + 1] = origin;
				}
				if (isin(i - 1, j) && board[i - 1][j] * flag <= 0 && midx - 1 <= i - 1 && i - 1 <= midx + 1)
				{
					origin = board[i - 1][j];
					board[i - 1][j] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, -1, 0, getvalue()));
					board[i][j] = 5 * flag;
					board[i - 1][j] = origin;
				}
				if (isin(i, j - 1) && board[i][j - 1] * flag <= 0 && 3 <= j - 1 && j - 1 <= 5)
				{
					origin = board[i][j - 1];
					board[i][j - 1] = board[i][j];
					board[i][j] = 0;
					arr.emplace_back(movechess(i, j, 0, -1, getvalue()));
					board[i][j] = 5 * flag;
					board[i][j - 1] = origin;
				}
			}/* 将遍历结束 */
			else if (board[i][j] == 6 * flag)/* 炮遍历开始*/
			{
				int num = 0;
				for (g = 1, num = 0; g < 10; g++)
				{
					if (!isin(i + g, j)) break;
					if (board[i + g][j] != 0)
					{
						num++;
					}
					if (isin(i + g, j) && (num == 0 || num == 2 && board[i + g][j] * flag < 0))
					{
						origin = board[i + g][j];
						board[i + g][j] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						board[i][j] = 6 * flag;
						board[i + g][j] = origin;
					}
					if (num == 2) break;
				}
				for (g = -1, num = 0; g > -10; g--)
				{
					if (!isin(i + g, j)) break;
					if (board[i + g][j] != 0)
					{
						num++;
					}
					if (isin(i + g, j) && (num == 0 || num == 2 && board[i + g][j] * flag < 0))
					{
						origin = board[i + g][j];
						board[i + g][j] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						board[i][j] = 6 * flag;
						board[i + g][j] = origin;
					}
					if (num == 2) break;
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (board[i][j + g] != 0)
					{
						num++;
					}
					if (isin(i, j + g) && (num == 0 || num == 2 && board[i][j + g] * flag < 0))
					{
						origin = board[i][j + g];
						board[i][j + g] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						board[i][j] = 6 * flag;
						board[i][j + g] = origin;
					}
					if (num == 2) break;
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (board[i][j + g] != 0)
					{
						num++;
					}
					if (isin(i, j + g) && (num == 0 || num == 2 && board[i][j + g] * flag < 0))
					{
						origin = board[i][j + g];
						board[i][j + g] = board[i][j];
						board[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						board[i][j] = 6 * flag;
						board[i][j + g] = origin;
					}
					if (num == 2) break;
				}
			}/* 炮遍历结束*/
			else if (board[i][j] == 7 * flag)/*兵遍历开始 */
			{
				if (flag == 1)
				{
					if (i >= 5)
					{
						if (isin(i - 1, j) && board[i - 1][j] * flag <= 0)
						{
							origin = board[i - 1][j];
							board[i - 1][j] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, -1, 0, getvalue()));
							board[i][j] = 7 * flag;
							board[i - 1][j] = origin;
						}
					}
					else if (i < 5)
					{
						if (isin(i, j - 1) && board[i][j - 1] * flag <= 0)
						{
							origin = board[i][j - 1];
							board[i][j - 1] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, -1, getvalue()));
							board[i][j] = 7 * flag;
							board[i][j - 1] = origin;
						}
						if (isin(i - 1, j) && board[i - 1][j] * flag <= 0)
						{
							origin = board[i - 1][j];
							board[i - 1][j] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, -1, 0, getvalue()));
							board[i][j] = 7 * flag;
							board[i - 1][j] = origin;
						}
						if (isin(i, j + 1) && board[i][j + 1] * flag <= 0)
						{
							origin = board[i][j + 1];
							board[i][j + 1] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, 1, getvalue()));
							board[i][j] = 7 * flag;
							board[i][j + 1] = origin;
						}
					}
				}
				else if (flag == -1)
				{
					if (i < 5)
					{
						if (isin(i + 1, j) && board[i + 1][j] * flag <= 0)
						{
							origin = board[i + 1][j];
							board[i + 1][j] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, 1, 0, getvalue()));
							board[i][j] = 7 * flag;
							board[i + 1][j] = origin;
						}
					}
					else if (i >= 5)
					{
						if (isin(i + 1, j) && board[i + 1][j] * flag <= 0)
						{
							origin = board[i + 1][j];
							board[i + 1][j] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, 1, 0, getvalue()));
							board[i][j] = 7 * flag;
							board[i + 1][j] = origin;
						}
						if (isin(i, j + 1) && board[i][j + 1] * flag <= 0)
						{
							origin = board[i][j + 1];
							board[i][j + 1] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, 1, getvalue()));
							board[i][j] = 7 * flag;
							board[i][j + 1] = origin;
						}
						if (isin(i, j - 1) && board[i][j - 1] * flag <= 0)
						{
							origin = board[i][j - 1];
							board[i][j - 1] = board[i][j];
							board[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, -1, getvalue()));
							board[i][j] = 7 * flag;
							board[i][j - 1] = origin;
						}
					}
				}
			}/* 兵遍历结束 */
		}
	}
}
short find(char flag, int layer, int alpha, int beta)
{
	/*
	Stage now = Stage(flag, board);
	//cout << sizeof(now) << endl;
	auto iter = StageValues.find(now);
	if (iter != StageValues.end())
	{		
		if (iter->second.first >= mylayer - layer)
		{
			//cout << iter->second.second << " ";
			return iter->second.second;
		}
	}
	*/
	if (layer != 0)
	{
		if (flag == RED)
		{
			auto iter = REDValues.find(boardkey);
			if (iter != REDValues.end() && iter->second.verify == verifykey)
			{
				if (iter->second.depth >= mylayer - layer)
				{
					return iter->second.value;
				}
			}
		}
		else
		{
			auto iter = BLACKValues.find(boardkey);
			if (iter != BLACKValues.end() && iter->second.verify == verifykey)
			{
				if (iter->second.depth >= mylayer - layer)
				{
					return iter->second.value;
				}
			}
		}
	}
	if (isdefeat(flag))
	{
		return -10000 +layer;
	}
	//老将见面
	if (ismeet())
	{
		return 10000 -layer;
	}
	if (layer == mylayer)/*      最底层估值函数         */
	{
		return getvalue();
	}
	if (layer == 0)
	{
		is_firststep = 0;
	}
	short current = -20000;
	int value;
	int origin;
	//arr数组用于招法排序
	vector<movechess> arr;
	generateMove(arr, flag);
	int prechess;
	if (layer % 2 == 0)
		sort(arr.begin(), arr.end());
	else
		sort(arr.rbegin(), arr.rend());
	unsigned long long tempHash = boardkey;
	unsigned long long tempVerify = verifykey;
	for (auto i = arr.begin(); i != arr.end(); i++)
	{	
		
		MakeMove(i, origin, prechess, flag);		
		value = -find(-flag, layer + 1, -beta, -alpha);
		UnMove(i, origin, prechess, flag);
		boardkey = tempHash;
		verifykey = tempVerify;
		if (layer == 0)/*    第一层返回下一步招法，第一层不可能有分支被剪掉（如果beta为无穷）(如果为渴望搜索算法，则有可能会剪枝)  */
		{
			//第一步选择
			if (is_firststep == 0)
			{
				m = i->x;
				n = i->y;
				tox = i->move_x;
				toy = i->move_y;
				type = board[i->x][i->y];
				is_firststep = 1;

			}
			//估值更高；(或者估值相等的时候有一定的概率使用该招法，增加一点随机性)
			//
			if (value > current || (value == current && rand() % 100 == 0))
			{
				m = i->x;
				n = i->y;
				tox = i->move_x;
				toy = i->move_y;
				type = board[i->x][i->y];
				current = value;
				if (value > alpha)
				{
					alpha = value;
				}
			}
		}
		else if (value > current)
		{
			current = value;
			if (value > alpha)
			{
				alpha = value;
			}
		}
		if (beta <= alpha) break;
	}
	if (mylayer - layer >= 3)
	{
		Stage a = Stage(mylayer - layer, current, verifykey);
		if (flag == RED)
		{
			REDValues[boardkey] = a;
		}
		else
		{
			BLACKValues[boardkey] = a;
		}
	}
	return current;
}