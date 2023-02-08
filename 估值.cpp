#include"func.h"
//估值函数是以红方视角来看的
int getvalue()
{
	int v1 = 0;
	int v2 = 0;
	int number = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if (b[i][j] != 0) number++;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
		{
			if (b[i][j] == 5)//帅估值
			{
				v1 += 10000 - (9-i) * 15;
			}
			if (b[i][j] == -5)//将估值
			{
				v2 += 10000 - i * 15;
			}
			if (b[i][j] == 1)/* 红车估值开始 */
			{
				int nu = 600;
				int g;
				for (g = 1; g < 10; g++)
				{
					if (isin(i + g, j) && b[i + g][j]> 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j]> 0) break;
					else
					{
						if (b[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (isin(i + g, j) && b[i + g][j] > 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] > 0) break;
					else
					{
						if (b[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (isin(i, j + g) && b[i][j + g] > 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] > 0) break;
					else
					{
						if (b[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (isin(i, j + g) && b[i][j + g] > 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] > 0) break;
					else
					{
						if (b[i + g][j] < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				v1 += nu;
				if ((i != 0 || j != 0) && (i != 0 || j != 8) && (i != 9 || j != 0) && (i != 9 || j != 8)) v1 += 15;
			}/*车估值到此为止 */
			else if (b[i][j] == -1)//黑车估值开始
			{
				int nu = 600;
				int g;
				for (g = 1; g < 10; g++)
				{
					if (isin(i + g, j) && b[i + g][j] < 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] < 0) break;
					else
					{
						if (b[i + g][j] > 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (isin(i + g, j) && b[i + g][j] < 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] < 0) break;
					else
					{
						if (b[i + g][j] > 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (isin(i, j + g) && b[i][j + g] < 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] < 0) break;
					else
					{
						if (b[i + g][j] > 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (isin(i, j + g) && b[i][j + g] < 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] < 0) break;
					else
					{
						if (b[i + g][j] > 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				v2 += nu;
				if ((i != 0 || j != 0) && (i != 0 || j != 8) && (i != 9 || j != 0) && (i != 9 || j != 8)) v2 += 15;
			}/* 黑车估值结束*/
			else if (b[i][j] == 2)/* 红马估值开始*/
			{
				int nu = 270 - number;
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && b[i + 2][j + 1]  <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 2, j + 1) && b[i + 2][j + 1]  > 0)
					{
						nu += 5;
					}
					if (isin(i + 2, j - 1) && b[i + 2][j - 1]  <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 2, j - 1) && b[i + 2][j - 1] > 0)
					{
						nu += 5;
					}
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && b[i - 2][j + 1] <= 0)
					{
						nu += 7;
					}
					else if (isin(i - 2, j + 1) && b[i - 2][j + 1] > 0)
					{
						nu += 6;
					}
					if (isin(i - 2, j - 1) && b[i - 2][j - 1] <= 0)
					{
						nu += 7;
					}
					else if (isin(i - 2, j - 1) && b[i - 2][j - 1] > 0)
					{
						nu += 6;
					}
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && b[i - 1][j - 2] <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j - 2) && b[i - 1][j - 2] > 0)
					{
						nu += 6;
					}
					if (isin(i + 1, j - 2) && b[i + 1][j - 2] <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 1, j - 2) && b[i + 1][j - 2] > 0)
					{
						nu += 5;
					}
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && b[i - 1][j + 2] <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j + 2) && b[i - 1][j + 2] > 0)
					{
						nu += 6;
					}
					if (isin(i + 1, j + 2) && b[i + 1][j + 2] <= 0)
					{
						nu += 5;
					}
					else if (isin(i + 1, j + 2) && b[i + 1][j + 2] > 0)
					{
						nu += 5;
					}
				}
				nu += 4 * (9 -i);
				v1 += nu;
			}/*红马估值到此为止*/
			else if (b[i][j] == -2)/* 黑马估值开始*/
			{
				int nu = 270 - number;
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && b[i + 2][j + 1] >= 0)
					{
						nu += 7;
					}
					else if (isin(i + 2, j + 1) && b[i + 2][j + 1] < 0)
					{
						nu += 6;
					}
					if (isin(i + 2, j - 1) && b[i + 2][j - 1] >= 0)
					{
						nu += 7;
					}
					else if (isin(i + 2, j - 1) && b[i + 2][j - 1] < 0)
					{
						nu += 6;
					}
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && b[i - 2][j + 1] >= 0)
					{
						nu += 5;
					}
					else if (isin(i - 2, j + 1) && b[i - 2][j + 1] < 0)
					{
						nu += 5;
					}
					if (isin(i - 2, j - 1) && b[i - 2][j - 1] >= 0)
					{
						nu += 5;
					}
					else if (isin(i - 2, j - 1) && b[i - 2][j - 1] < 0)
					{
						nu += 5;
					}
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && b[i - 1][j - 2] >= 0)
					{
						nu += 5;
					}
					else if (isin(i - 1, j - 2) && b[i - 1][j - 2] < 0)
					{
						nu += 5;
					}
					if (isin(i + 1, j - 2) && b[i + 1][j - 2] >= 0)
					{
						nu += 6;
					}
					else if (isin(i + 1, j - 2) && b[i + 1][j - 2] < 0)
					{
						nu += 6;
					}
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && b[i - 1][j + 2] >= 0)
					{
						nu += 5;
					}
					else if (isin(i - 1, j + 2) && b[i - 1][j + 2] < 0)
					{
						nu += 5;
					}
					if (isin(i + 1, j + 2) && b[i + 1][j + 2] >= 0)
					{
						nu += 6;
					}
					else if (isin(i + 1, j + 2) && b[i + 1][j + 2] < 0)
					{
						nu += 6;
					}
				}
				nu += 4 * i;
				v2 += nu;
			}/* 黑马估值结束*/
			else if (b[i][j] == 3 )/* 红象估值开始*/
			{
				int nu = 110;
				if (isin(i + 1, j + 1) && b[i + 1][j + 1] == 0 && i + 2 >= 5 )/* 象不过河 */
				{
					if (b[i + 2][j + 2]  < 0)
						nu += 5;
					else if (b[i + 2][j + 2] == 0)
						nu += 2;
					else if (b[i + 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i + 1, j - 1) && b[i + 1][j - 1] == 0 && i + 2 >= 5 )
				{
					if (b[i + 2][j - 2]  < 0)
						nu += 5;
					else if (b[i + 2][j - 2] == 0)
						nu += 2;
					else if (b[i + 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j + 1) && b[i - 1][j + 1] == 0 &&  i - 2 >= 5 )
				{
					if (b[i - 2][j + 2]  < 0)
						nu += 5;
					else if (b[i - 2][j + 2] == 0)
						nu += 2;
					else if (b[i - 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j - 1) && b[i - 1][j - 1] == 0 && i - 2 >= 5 )
				{
					if (b[i - 2][j - 2] < 0)
						nu += 5;
					else if (b[i - 2][j - 2] == 0)
						nu += 2;
					else if (b[i - 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				v1 += nu;
			}/* 红象估值到此为止*/
			else if (b[i][j] == -3)/* 黑象估值开始*/
			{
				int nu = 110;
				if (isin(i + 1, j + 1) && b[i + 1][j + 1] == 0 &&  i + 2 < 5)/* 象不过河 */
				{
					if (b[i + 2][j + 2] > 0)
						nu += 5;
					else if (b[i + 2][j + 2] == 0)
						nu += 2;
					else if (b[i + 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i + 1, j - 1) && b[i + 1][j - 1] == 0 &&  i + 2 < 5)
				{
					if (b[i + 2][j - 2] > 0)
						nu += 5;
					else if (b[i + 2][j - 2] == 0)
						nu += 2;
					else if (b[i + 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j + 1) && b[i - 1][j + 1] == 0  && i - 2 < 5)
				{
					if (b[i - 2][j + 2] > 0)
						nu += 5;
					else if (b[i - 2][j + 2] == 0)
						nu += 2;
					else if (b[i - 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j - 1) && b[i - 1][j - 1] == 0 && i - 2 < 5)
				{
					if (b[i - 2][j - 2] > 0)
						nu += 5;
					else if (b[i - 2][j - 2] == 0)
						nu += 2;
					else if (b[i - 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				v2 += nu;
			}/* 黑象估值结束*/
			else if (b[i][j] == 4)//红士估值开始
			{
				int nu = 110;
				if (i + 1 >= 7 && i + 1 <= 9 && j + 1 >= 3 && j + 1 <= 5 )
				{
					if (b[i + 1][j + 1] <= 0)
						nu += 4;
					else if (b[i + 1][j + 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j + 1 >= 3 && j + 1 <= 5 )
				{
					if (b[i - 1][j + 1] <= 0)
						nu += 4;
					else if (b[i - 1][j + 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i + 1 >= 7 && i + 1 <= 9 && j - 1 >= 3 && j - 1 <= 5 )
				{
					if (b[i + 1][j - 1] <= 0)
						nu += 4;
					else if (b[i + 1][j - 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j - 1 >= 3 && j - 1 <= 5 )
				{
					if (b[i - 1][j - 1] <= 0)
						nu += 4;
					else if (b[i - 1][j - 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				v1 += nu;
			}//红士估值到此为止
			else if (b[i][j] == -4 )/* 黑士估值开始*/
			{
				int nu = 110;
				if (i + 1 >= 0 && i + 1 <= 2 && j + 1 >= 3 && j + 1 <= 5 )
				{
					if (b[i + 1][j + 1] <= 0)
						nu += 4;
					else if (b[i + 1][j + 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i - 1 >= 0 && i - 1 <= 2 && j + 1 >= 3 && j + 1 <= 5 )
				{
					if (b[i - 1][j + 1] <= 0)
						nu += 4;
					else if (b[i - 1][j + 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if ( i + 1 >= 0 && i + 1 <= 2 && j - 1 >= 3 && j - 1 <= 5 )
				{
					if (b[i + 1][j - 1] <= 0)
						nu += 4;
					else if (b[i + 1][j - 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				if (i - 1 >= 0 && i - 1 <= 2 && j - 1 >= 3 && j - 1 <= 5 )
				{
					if (b[i - 1][j - 1] <= 0)
						nu += 4;
					else if (b[i - 1][j - 1] == b[i][j])
						nu += 6;
					else
						nu += 3;
				}
				v2 += nu;
			}/* 黑士估值结束*/
			else if (b[i][j] == 7 )/* 红兵估值*/
			{
				int nu = 135 - 3 * number;
				nu += soldier_value[i][j];
				v1 += nu;
			}
			else if (b[i][j] == -7 )/* 黑卒估值*/
			{
				int nu = 135 - 3 * number;
				nu += soldier_value[9-i][j];
				v2 += nu;
			}
			else if (b[i][j] == 6 )/* 红炮估值开始 */
			{
				int nu = 190;
				nu += number * 4;
				v1 += nu;
				int num = 0;
				int g;
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					v1 += 4;
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					v1 += 4;
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					v1 += 4;
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					v1 += 4;
				}
				for (g = 1, num = 0; g < 10; g++)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == -5 )
					{
						v1 += 4 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
						if (num == 1)
						{
							v1 += 3;
						}
						if (num >= 2)
						{
							if (b[i + g][j] < 0)
								v1 += 8 / pow(2, num - 2);
							else if (b[i + g][j] > 0 && num == 2)
							{
								v1 += 5;
							}
						}
					}
				}
				for (g = -1, num = 0; g > -10; g--)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == -5)
					{
						v1 += 4 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
						if (num == 1)
						{
							v1 += 3;
						}
						if (num >= 2)
						{
							if (b[i + g][j] < 0)
								v1 += 8 / pow(2, num - 2);
							else if (b[i + g][j] > 0 && num == 2)
							{
								v1 += 5;
							}
						}
					}
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == -5)
					{
						v1 += 4 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
						if (num == 1)
						{
							v1 += 3;
						}
						if (num >= 2)
						{
							if (b[i][j + g] < 0)
								v1 += 8 / pow(2, num - 2);
							else if (b[i][j + g] > 0 && num == 2)
							{
								v1 += 5;
							}
						}
					}
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == -5)
					{
						v1 += 4 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
						if (num == 1)
						{
							v1 += 3;
						}
						if (num >= 2)
						{
							if (b[i][j + g] < 0)
								v1 += 8 / pow(2, num - 2);
							else if (b[i][j + g] > 0 && num == 2)
							{
								v1 += 5;
							}
						}
					}
				}
			}
			else if (b[i][j] == -6) //黑炮估值
			{
				int nu = 190;
				nu += number * 4;
				v2 += nu;
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					v2 += 4;
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					v2 += 4;
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					v2 += 4;
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					v2 += 4;
				}
				int num = 0;
				int g;
				for (g = 1, num = 0; g < 10; g++)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == 5)
					{
						v2 += 4 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
						if (num == 1)
						{
							v2 += 3;
						}
						if (num >= 2)
						{
							if (b[i + g][j] > 0)
								v2 += 8 / pow(2, num - 2);
							else if (b[i + g][j] < 0 && num == 2)
							{
								v2 += 5;
							}
						}
					}
				}
				for (g = -1, num = 0; g > -10; g--)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == -5)
					{
						v2 += 4 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
						if (num == 1)
						{
							v2 += 3;
						}
						if (num >= 2)
						{
							if (b[i + g][j] > 0)
								v2 += 8 / pow(2, num - 2);
							else if (b[i + g][j] < 0 && num == 2)
							{
								v2 += 5;
							}
						}
					}
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == 5)
					{
						v2 += 4 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
						if (num == 1)
						{
							v2 += 3;
						}
						if (num >= 2)
						{
							if (b[i][j + g] > 0)
								v2 += 8 / pow(2, num - 2);
							else if (b[i][j + g] < 0 && num == 2)
							{
								v2 += 5;
							}
						}
					}
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == 5)
					{
						v2 += 4 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
						if (num == 1)
						{
							v2 += 3;
						}
						if (num >= 2)
						{
							if (b[i][j + g] > 0 )
								v2 += 8 / pow(2, num - 2);
							else if (b[i][j + g] < 0 && num == 2)
							{
								v2 += 5;
							}
						}
					}

				}
			}/* 黑炮估值结束 */
		}
	if(side == RED)
		return v1 - v2 + 120;
	else
		return v2 - v1;
}