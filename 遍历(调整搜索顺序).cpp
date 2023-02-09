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
	origin = board[i->x + i->move_x][i->y + i->move_y];
	prechess = board[i->x][i->y];
	board[i->x + i->move_x][i->y + i->move_y] = board[i->x][i->y];
	board[i->x][i->y] = 0;
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
	if (isdefeat(flag))
	{
		return -side * (int)flag * 10000;
	}
	if (isdefeat(-flag))
	{
		return side * (int)flag * 10000;
	}
	//老将见面
	if (ismeet())
	{
		return side * (int)flag * 10000;
	}
	if (layer == mylayer)/*      最底层估值函数         */
	{
		return getvalue();
	}
	if (layer == 0)
	{
		is_firststep = 0;
	}
	short current;
	if (layer % 2 == 0)
		current = -20000;
	else
		current = 20000;
	int r;
	int origin;
	vector<movechess> arr;
	generateMove(arr, flag);
	int prechess;
	if (layer % 2 == 0)
		sort(arr.begin(), arr.end());
	else
		sort(arr.rbegin(), arr.rend());
	for (auto i = arr.begin(); i != arr.end(); i++)
	{	
		MakeMove(i, origin, prechess, flag);
		r = find(-flag, layer + 1, alpha, beta);
		UnMove(i, origin, prechess, flag);
		cut(layer, r, i->x, i->y, alpha, beta, i->move_x, i->move_y, board[i->x][i->y], current);
		if (beta <= alpha) break;
	}
	return current;
}