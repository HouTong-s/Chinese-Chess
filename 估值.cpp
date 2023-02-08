#include"func.h"

//��ֵ�������Ժ췽�ӽ�������
int getRED_value(int total_chess,char temp_board[10][9])
{
	int result = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
		{
			if (temp_board[i][j] == 5)//˧��ֵ
			{
				result += 10000 - (9 - i) * 15;
			}
			if (temp_board[i][j] == 1)/* �쳵��ֵ��ʼ */
			{
				int nu = 600;
				int g;
				for (g = 1; g < 10; g++)
				{
					if (isin(i + g, j) && temp_board[i + g][j] > 0) nu += 2;
					if (!isin(i + g, j) || temp_board[i + g][j] > 0) break;
					else
					{
						if (temp_board[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (isin(i + g, j) && temp_board[i + g][j] > 0) nu += 2;
					if (!isin(i + g, j) || temp_board[i + g][j] > 0) break;
					else
					{
						if (temp_board[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (isin(i, j + g) && temp_board[i][j + g] > 0) nu += 2;
					if (!isin(i, j + g) || temp_board[i][j + g] > 0) break;
					else
					{
						if (temp_board[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (isin(i, j + g) && temp_board[i][j + g] > 0) nu += 2;
					if (!isin(i, j + g) || temp_board[i][j + g] > 0) break;
					else
					{
						if (temp_board[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				result += nu;
				if ((i != 0 || j != 0) && (i != 0 || j != 8) && (i != 9 || j != 0) && (i != 9 || j != 8)) result += 20;
			}/*����ֵ����Ϊֹ */
			else if (temp_board[i][j] == 2)/* �����ֵ��ʼ*/
			{
				int nu = 300 - 2 * total_chess;
				if (isin(i + 1, j) && temp_board[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && temp_board[i + 2][j + 1] <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 2, j + 1) && temp_board[i + 2][j + 1] > 0)
					{
						nu += 5;
					}
					if (isin(i + 2, j - 1) && temp_board[i + 2][j - 1] <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 2, j - 1) && temp_board[i + 2][j - 1] > 0)
					{
						nu += 5;
					}
				}
				if (isin(i - 1, j) && temp_board[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && temp_board[i - 2][j + 1] <= 0)
					{
						nu += 7;
					}
					else if (isin(i - 2, j + 1) && temp_board[i - 2][j + 1] > 0)
					{
						nu += 6;
					}
					if (isin(i - 2, j - 1) && temp_board[i - 2][j - 1] <= 0)
					{
						nu += 7;
					}
					else if (isin(i - 2, j - 1) && temp_board[i - 2][j - 1] > 0)
					{
						nu += 6;
					}
				}
				if (isin(i, j - 1) && temp_board[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && temp_board[i - 1][j - 2] <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j - 2) && temp_board[i - 1][j - 2] > 0)
					{
						nu += 6;
					}
					if (isin(i + 1, j - 2) && temp_board[i + 1][j - 2] <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 1, j - 2) && temp_board[i + 1][j - 2] > 0)
					{
						nu += 5;
					}
				}
				if (isin(i, j + 1) && temp_board[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && temp_board[i - 1][j + 2] <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j + 2) && temp_board[i - 1][j + 2] > 0)
					{
						nu += 6;
					}
					if (isin(i + 1, j + 2) && temp_board[i + 1][j + 2] <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 1, j + 2) && temp_board[i + 1][j + 2] > 0)
					{
						nu += 5;
					}
				}
				nu += 4 * (9 - i);
				result += nu;
			}/*�����ֵ����Ϊֹ*/
			else if (temp_board[i][j] == 3)/* �����ֵ��ʼ*/
			{
				int nu = 110;
				if (isin(i + 1, j + 1) && temp_board[i + 1][j + 1] == 0 && i + 2 >= 5)/* �󲻹��� */
				{
					if (temp_board[i + 2][j + 2] < 0)
						nu += 5;
					else if (temp_board[i + 2][j + 2] == 0)
						nu += 2;
					else if (temp_board[i + 2][j + 2] == temp_board[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i + 1, j - 1) && temp_board[i + 1][j - 1] == 0 && i + 2 >= 5)
				{
					if (temp_board[i + 2][j - 2] < 0)
						nu += 5;
					else if (temp_board[i + 2][j - 2] == 0)
						nu += 2;
					else if (temp_board[i + 2][j - 2] == temp_board[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j + 1) && temp_board[i - 1][j + 1] == 0 && i - 2 >= 5)
				{
					if (temp_board[i - 2][j + 2] < 0)
						nu += 5;
					else if (temp_board[i - 2][j + 2] == 0)
						nu += 2;
					else if (temp_board[i - 2][j + 2] == temp_board[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j - 1) && temp_board[i - 1][j - 1] == 0 && i - 2 >= 5)
				{
					if (temp_board[i - 2][j - 2] < 0)
						nu += 5;
					else if (temp_board[i - 2][j - 2] == 0)
						nu += 2;
					else if (temp_board[i - 2][j - 2] == temp_board[i][j])
						nu += 6;
					else
						nu += 2;
				}
				result += nu;
			}/* �����ֵ����Ϊֹ*/
			else if (temp_board[i][j] == 4)//��ʿ��ֵ��ʼ
			{
				int nu = 110;
				if (i + 1 >= 7 && i + 1 <= 9 && j + 1 >= 3 && j + 1 <= 5)
				{
					if (temp_board[i + 1][j + 1] <= 0)
						nu += 4;
					else if (temp_board[i + 1][j + 1] == temp_board[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j + 1 >= 3 && j + 1 <= 5)
				{
					if (temp_board[i - 1][j + 1] <= 0)
						nu += 4;
					else if (temp_board[i - 1][j + 1] == temp_board[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i + 1 >= 7 && i + 1 <= 9 && j - 1 >= 3 && j - 1 <= 5)
				{
					if (temp_board[i + 1][j - 1] <= 0)
						nu += 4;
					else if (temp_board[i + 1][j - 1] == temp_board[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j - 1 >= 3 && j - 1 <= 5)
				{
					if (temp_board[i - 1][j - 1] <= 0)
						nu += 4;
					else if (temp_board[i - 1][j - 1] == temp_board[i][j])
						nu += 6;
					else
						nu += 3;
				}
				result += nu;
			}//��ʿ��ֵ����Ϊֹ
			else if (temp_board[i][j] == 7)/* �����ֵ*/
			{
				int nu = 135 - 3 * total_chess;
				nu += soldier_value[i][j];
				result += nu;
			}
			else if (temp_board[i][j] == 6)/* ���ڹ�ֵ��ʼ */
			{
				int nu = 190;
				nu += total_chess * 3;
				result += nu;
				int num = 0;
				int g;
				if (isin(i + 1, j) && temp_board[i + 1][j] == 0)
				{
					result += 6;
				}
				if (isin(i - 1, j) && temp_board[i - 1][j] == 0)
				{
					result += 6;
				}
				if (isin(i, j + 1) && temp_board[i][j + 1] == 0)
				{
					result += 6;
				}
				if (isin(i, j - 1) && temp_board[i][j - 1] == 0)
				{
					result += 6;
				}
				for (g = 1, num = 0; g < 10; g++)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && temp_board[i + g][j] == -5)
					{
						result += 3 * total_chess;
					}
					if (temp_board[i + g][j] != 0)
					{
						num++;
						if (num > 3)
							break;
						if (num == 1)
						{
							result += 4;
						}
						if (num >= 2)
						{
							if (temp_board[i + g][j] < 0)
								result += 8 / pow(2, num - 2);
							else if (temp_board[i + g][j] > 0 && num == 2)
							{
								result += 5;
							}
						}
					}
				}
				for (g = -1, num = 0; g > -10; g--)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && temp_board[i + g][j] == -5)
					{
						result += 3 * total_chess;
					}
					if (temp_board[i + g][j] != 0)
					{
						num++;
						if (num > 3)
							break;
						if (num == 1)
						{
							result += 4;
						}
						if (num >= 2)
						{
							if (temp_board[i + g][j] < 0)
								result += 8 / pow(2, num - 2);
							else if (temp_board[i + g][j] > 0 && num == 2)
							{
								result += 5;
							}
						}
					}
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && temp_board[i][j + g] == -5)
					{
						result += 3 * total_chess;
					}
					if (temp_board[i][j + g] != 0)
					{
						num++;
						if (num > 3)
							break;
						if (num == 1)
						{
							result += 4;
						}
						if (num >= 2)
						{
							if (temp_board[i][j + g] < 0)
								result += 8 / pow(2, num - 2);
							else if (temp_board[i][j + g] > 0 && num == 2)
							{
								result += 5;
							}
						}
					}
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && temp_board[i][j + g] == -5)
					{
						result += 3 * total_chess;
					}
					if (temp_board[i][j + g] != 0)
					{
						num++;
						if (num > 3)
							break;
						if (num == 1)
						{
							result += 4;
						}
						if (num >= 2)
						{
							if (temp_board[i][j + g] < 0)
								result += 8 / pow(2, num - 2);
							else if (temp_board[i][j + g] > 0 && num == 2)
							{
								result += 5;
							}
						}
					}
				}
			}
		}
	return result;
}
int getvalue()
{
	int v1 = 0;
	int v2 = 0;
	int number = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if (board[i][j] != 0) number++;
	v1 = getRED_value(number,board);
	//��ת���̣����������v2���Ǻڷ��Ĺ�ֵ
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tempboard[9-i][j] = -board[i][j];
		}
	}
	v2 = getRED_value(number, tempboard);
	if(side == RED)
		return v1 - v2 + 120;
	else
		return v2 - v1;
}