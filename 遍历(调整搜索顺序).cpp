#include"func.h"
using namespace std;
int find(char flag, int layer, int alpha, int beta)
{
	if (isdefeat(flag))
	{
		return -side * (int)flag * 10000;
	}
	if (isdefeat(-flag))
	{
		return side * (int)flag * 10000;
	}
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
	int current;
	if (layer % 2 == 0)
		current = -20000;
	else
		current = 20000;
	int r;
	int g, origin;
	vector<movechess> arr;

	for (int i = 0; i < 10; i++)/* 随机取点开始 */
	{
		for (int j = 0; j < 9; j++)
		{
			if (b[i][j] == flag)/*     车遍历方法开始(四个方向)      */
			{
				for (g = 1; g < 10; g++)
				{
					if (!isin(i + g, j) || b[i + g][j] * flag > 0) break;
					if (isin(i + g, j))
					{
						origin = b[i + g][j];
						b[i + g][j] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						b[i][j] = flag;
						b[i + g][j] = origin;
						if (b[i + g][j] * flag < 0) break;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (!isin(i + g, j) || b[i + g][j] * flag > 0) break;
					if (isin(i + g, j))
					{
						origin = b[i + g][j];
						b[i + g][j] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						b[i][j] = flag;
						b[i + g][j] = origin;
						if (b[i + g][j] * flag < 0) break;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (!isin(i, j + g) || b[i][j + g] * flag > 0) break;
					if (isin(i, j + g))
					{
						origin = b[i][j + g];
						b[i][j + g] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						b[i][j] = flag;
						b[i][j + g] = origin;
						if (b[i][j + g] * flag < 0) break;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (!isin(i, j + g) || b[i][j + g] * flag > 0) break;
					if (isin(i, j + g))
					{
						origin = b[i][j + g];
						b[i][j + g] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						b[i][j] = flag;
						b[i][j + g] = origin;
						if (b[i][j + g] * flag < 0) break;
					}
				}
			}/*      车遍历到此为止       */
			else if (b[i][j] == 2 * flag)/*    马遍历开始(八面威风)      */
			{
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && b[i + 2][j + 1] * flag <= 0)
					{
						origin = b[i + 2][j + 1];
						b[i + 2][j + 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 2, 1, getvalue()));
						b[i][j] = 2 * flag;
						b[i + 2][j + 1] = origin;
					}
					if (isin(i + 2, j - 1) && b[i + 2][j - 1] * flag <= 0)
					{
						origin = b[i + 2][j - 1];
						b[i + 2][j - 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 2, -1, getvalue()));
						b[i][j] = 2 * flag;
						b[i + 2][j - 1] = origin;
					}
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && b[i - 2][j + 1] * flag <= 0)
					{
						origin = b[i - 2][j + 1];
						b[i - 2][j + 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, -2, 1, getvalue()));
						b[i][j] = 2 * flag;
						b[i - 2][j + 1] = origin;
					}
					if (isin(i - 2, j - 1) && b[i - 2][j - 1] * flag <= 0)
					{
						origin = b[i - 2][j - 1];
						b[i - 2][j - 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, -2, -1, getvalue()));
						b[i][j] = 2 * flag;
						b[i - 2][j - 1] = origin;
					}
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && b[i - 1][j - 2] * flag <= 0)
					{
						origin = b[i - 1][j - 2];
						b[i - 1][j - 2] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, -2, getvalue()));
						b[i][j] = 2 * flag;
						b[i - 1][j - 2] = origin;
					}
					if (isin(i + 1, j - 2) && b[i + 1][j - 2] * flag <= 0)
					{
						origin = b[i + 1][j - 2];
						b[i + 1][j - 2] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, -2, getvalue()));
						b[i][j] = 2 * flag;
						b[i + 1][j - 2] = origin;
					}
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && b[i - 1][j + 2] * flag <= 0)
					{
						origin = b[i - 1][j + 2];
						b[i - 1][j + 2] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, 2, getvalue()));
						b[i][j] = 2 * flag;
						b[i - 1][j + 2] = origin;
					}
					if (isin(i + 1, j + 2) && b[i + 1][j + 2] * flag <= 0)
					{
						origin = b[i + 1][j + 2];
						b[i + 1][j + 2] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, 2, getvalue()));
						b[i][j] = 2 * flag;
						b[i + 1][j + 2] = origin;
					}
				}
			}/*    马遍历结束    */
			else if (b[i][j] == 3 * flag)/*    象遍历开始    */
			{
				if (isin(i + 1, j + 1) && b[i + 1][j + 1] == 0 && b[i + 2][j + 2] * flag <= 0 && (flag == 1 && i + 2 >= 5 || flag == -1 && i + 2 < 5))/* 象不过河 */
				{
					origin = b[i + 2][j + 2];
					b[i + 2][j + 2] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, 2, 2, getvalue()));
					b[i][j] = 3 * flag;
					b[i + 2][j + 2] = origin;
				}
				if (isin(i + 1, j - 1) && b[i + 1][j - 1] == 0 && b[i + 2][j - 2] * flag <= 0 && (flag == 1 && i + 2 >= 5 || flag == -1 && i + 2 < 5))
				{
					origin = b[i + 2][j - 2];
					b[i + 2][j - 2] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, 2, -2, getvalue()));
					b[i][j] = 3 * flag;
					b[i + 2][j - 2] = origin;
				}
				if (isin(i - 1, j + 1) && b[i - 1][j + 1] == 0 && b[i - 2][j + 2] * flag <= 0 && (flag == 1 && i - 2 >= 5 || flag == -1 && i - 2 < 5))
				{
					origin = b[i - 2][j + 2];
					b[i - 2][j + 2] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, -2, 2, getvalue()));
					b[i][j] = 3 * flag;
					b[i - 2][j + 2] = origin;
				}
				if (isin(i - 1, j - 1) && b[i - 1][j - 1] == 0 && b[i - 2][j - 2] * flag <= 0 && (flag == 1 && i - 2 >= 5 || flag == -1 && i - 2 < 5))
				{
					origin = b[i - 2][j - 2];
					b[i - 2][j - 2] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, -2, -2, getvalue()));
					b[i][j] = 3 * flag;
					b[i - 2][j - 2] = origin;
				}
			}/*   象遍历结束   */
			else if (b[i][j] == 4 * flag)/*  士遍历开始 */
			{
				int midx;
				int midy = 4;
				if (flag == 1)	midx = 8;
				else midx = 1;
				if (i == midx && j == midy)
				{
					if (b[i + 1][j + 1] * flag <= 0)
					{
						origin = b[i + 1][j + 1];
						b[i + 1][j + 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, 1, getvalue()));
						b[i][j] = 4 * flag;
						b[i + 1][j + 1] = origin;
					}
					if (b[i - 1][j + 1] * flag <= 0)
					{
						origin = b[i - 1][j + 1];
						b[i - 1][j + 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, 1, getvalue()));
						b[i][j] = 4 * flag;
						b[i - 1][j + 1] = origin;
					}
					if (b[i + 1][j - 1] * flag <= 0)
					{
						origin = b[i + 1][j - 1];
						b[i + 1][j - 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 1, -1, getvalue()));
						b[i][j] = 4 * flag;
						b[i + 1][j - 1] = origin;
					}
					if (b[i - 1][j - 1] * flag <= 0)
					{
						origin = b[i - 1][j - 1];
						b[i - 1][j - 1] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, -1, -1, getvalue()));
						b[i][j] = 4 * flag;
						b[i - 1][j - 1] = origin;
					}
				}
				else if (b[midx][midy] * flag <= 0)
				{
					origin = b[midx][midy];
					b[midx][midy] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, midx - i, midy - j, getvalue()));
					b[i][j] = 4 * flag;
					b[midx][midy] = origin;
				}
			}/* 士遍历结束 */
			else if (b[i][j] == 5 * flag)/* 将遍历开始 */
			{
				int midx;
				if (flag == 1)	midx = 8;
				else midx = 1;
				if (isin(i + 1, j) && b[i + 1][j] * flag <= 0 && midx - 1 <= i + 1 && i + 1 <= midx + 1)
				{
					origin = b[i + 1][j];
					b[i + 1][j] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, 1, 0, getvalue()));
					b[i][j] = 5 * flag;
					b[i + 1][j] = origin;
				}
				if (isin(i, j + 1) && b[i][j + 1] * flag <= 0 && 3 <= j + 1 && j + 1 <= 5)
				{
					origin = b[i][j + 1];
					b[i][j + 1] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, 0, 1, getvalue()));
					b[i][j] = 5 * flag;
					b[i][j + 1] = origin;
				}
				if (isin(i - 1, j) && b[i - 1][j] * flag <= 0 && midx - 1 <= i - 1 && i - 1 <= midx + 1)
				{
					origin = b[i - 1][j];
					b[i - 1][j] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, -1, 0, getvalue()));
					b[i][j] = 5 * flag;
					b[i - 1][j] = origin;
				}
				if (isin(i, j - 1) && b[i][j - 1] * flag <= 0 && 3 <= j - 1 && j - 1 <= 5)
				{
					origin = b[i][j - 1];
					b[i][j - 1] = b[i][j];
					b[i][j] = 0;
					arr.emplace_back(movechess(i, j, 0, -1, getvalue()));
					b[i][j] = 5 * flag;
					b[i][j - 1] = origin;
				}
			}/* 将遍历结束 */
			else if (b[i][j] == 6 * flag)/* 炮遍历开始*/
			{
				int num = 0;
				for (g = 1, num = 0; g < 10; g++)
				{
					if (!isin(i + g, j)) break;
					if (b[i + g][j] != 0)
					{
						num++;
					}
					if (isin(i + g, j) && (num == 0 || num == 2 && b[i + g][j] * flag < 0))
					{
						origin = b[i + g][j];
						b[i + g][j] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						b[i][j] = 6 * flag;
						b[i + g][j] = origin;
					}
					if (num == 2) break;
				}
				for (g = -1, num = 0; g > -10; g--)
				{
					if (!isin(i + g, j)) break;
					if (b[i + g][j] != 0)
					{
						num++;
					}
					if (isin(i + g, j) && (num == 0 || num == 2 && b[i + g][j] * flag < 0))
					{
						origin = b[i + g][j];
						b[i + g][j] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, g, 0, getvalue()));
						b[i][j] = 6 * flag;
						b[i + g][j] = origin;
					}
					if (num == 2) break;
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (b[i][j + g] != 0)
					{
						num++;
					}
					if (isin(i, j + g) && (num == 0 || num == 2 && b[i][j + g] * flag < 0))
					{
						origin = b[i][j + g];
						b[i][j + g] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						b[i][j] = 6 * flag;
						b[i][j + g] = origin;
					}
					if (num == 2) break;
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (b[i][j + g] != 0)
					{
						num++;
					}
					if (isin(i, j + g) && (num == 0 || num == 2 && b[i][j + g] * flag < 0))
					{
						origin = b[i][j + g];
						b[i][j + g] = b[i][j];
						b[i][j] = 0;
						arr.emplace_back(movechess(i, j, 0, g, getvalue()));
						b[i][j] = 6 * flag;
						b[i][j + g] = origin;
					}
					if (num == 2) break;
				}
			}/* 炮遍历结束*/
			else if (b[i][j] == 7 * flag)/*兵遍历开始 */
			{
				if (flag == 1)
				{
					if (i >= 5)
					{
						if (isin(i - 1, j) && b[i - 1][j] * flag <= 0)
						{
							origin = b[i - 1][j];
							b[i - 1][j] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, -1, 0, getvalue()));
							b[i][j] = 7 * flag;
							b[i - 1][j] = origin;
						}
					}
					else if (i < 5)
					{
						if (isin(i, j - 1) && b[i][j - 1] * flag <= 0)
						{
							origin = b[i][j - 1];
							b[i][j - 1] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, -1, getvalue()));
							b[i][j] = 7 * flag;
							b[i][j - 1] = origin;
						}
						if (isin(i - 1, j) && b[i - 1][j] * flag <= 0)
						{
							origin = b[i - 1][j];
							b[i - 1][j] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, -1, 0, getvalue()));
							b[i][j] = 7 * flag;
							b[i - 1][j] = origin;
						}
						if (isin(i, j + 1) && b[i][j + 1] * flag <= 0)
						{
							origin = b[i][j + 1];
							b[i][j + 1] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, 1, getvalue()));
							b[i][j] = 7 * flag;
							b[i][j + 1] = origin;
						}
					}
				}
				else if (flag == -1)
				{
					if (i < 5)
					{
						if (isin(i + 1, j) && b[i + 1][j] * flag <= 0)
						{
							origin = b[i + 1][j];
							b[i + 1][j] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, 1, 0, getvalue()));
							b[i][j] = 7 * flag;
							b[i + 1][j] = origin;
						}
					}
					else if (i >= 5)
					{
						if (isin(i + 1, j) && b[i + 1][j] * flag <= 0)
						{
							origin = b[i + 1][j];
							b[i + 1][j] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, 1, 0, getvalue()));
							b[i][j] = 7 * flag;
							b[i + 1][j] = origin;
						}
						if (isin(i, j + 1) && b[i][j + 1] * flag <= 0)
						{
							origin = b[i][j + 1];
							b[i][j + 1] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, 1, getvalue()));
							b[i][j] = 7 * flag;
							b[i][j + 1] = origin;
						}
						if (isin(i, j - 1) && b[i][j - 1] * flag <= 0)
						{
							origin = b[i][j - 1];
							b[i][j - 1] = b[i][j];
							b[i][j] = 0;
							arr.emplace_back(movechess(i, j, 0, -1, getvalue()));
							b[i][j] = 7 * flag;
							b[i][j - 1] = origin;
						}
					}
				}
			}/* 兵遍历结束 */
		}
	}
	int prechess;
	if (layer % 2 == 0)
		sort(arr.begin(), arr.end());
	else
		sort(arr.rbegin(), arr.rend());
	int j = 0;
	for (auto i = arr.begin(); i != arr.end(); i++)
	{
		if (b[i->i][i->j] == 5 * flag)//如果是遍历的老将，要改变记录老将的横纵坐标，以确定两边老将是否相遇
		{
			if (flag == 1)
			{
				redx = i->j + i->y;
				redy = i->i + i->x;
			}
			else
			{
				blackx = i->j + i->y;
				blacky = i->i + i->x;
			}
		}
		origin = b[i->i + i->x][i->j + i->y];
		prechess = b[i->i][i->j];
		b[i->i + i->x][i->j + i->y] = b[i->i][i->j];
		b[i->i][i->j] = 0;
		r = find(-flag, layer+1, alpha, beta);
		b[i->i][i->j] = prechess;
		b[i->i + i->x][i->j + i->y] = origin;
		if (b[i->i][i->j] == 5 * flag)//如果是遍历的老将，要回溯老将的横纵坐标，以确定两边老将是否相遇
		{
			if (flag == 1)
			{
				redx = i->j;
				redy = i->i;
			}
			else
			{
				blackx = i->j;
				blacky = i->i;
			}
		}
		cut(layer, r, i->i, i->j, alpha, beta, i->x, i->y, b[i->i][i->j], current);
		if (beta <= alpha) break;
	}
	return current;
}