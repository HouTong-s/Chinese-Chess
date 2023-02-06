#include"func.h"
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
			if (b[i][j] == 5 * side)//帅估值
			{
				int nu = 10000;
				if (side == 1)
					nu -= (9 - i) * 15;
				else
					nu -= i * 15;
				v1 += nu;
			}
			if (b[i][j] == -5 * side)//将估值
			{
				int nu = 10000;
				side = -side;
				if (side == 1)
					nu -= (9 - i) * 15;
				else
					nu -= i * 15;
				side = -side;
				v2 += nu;
			}
			if (b[i][j] == side)/* 车估值开始 */
			{
				int nu = 600;
				int g;
				for (g = 1; g < 10; g++)
				{
					if (isin(i + g, j) && b[i + g][j] * side > 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (isin(i + g, j) && b[i + g][j] * side > 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (isin(i, j + g) && b[i][j + g] * side > 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (isin(i, j + g) && b[i][j + g] * side > 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
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
			else if (b[i][j] == -side)//车估值开始
			{
				side = -side;
				int nu = 600;
				int g;
				for (g = 1; g < 10; g++)
				{
					if (isin(i + g, j) && b[i + g][j] * side > 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -10; g--)
				{
					if (isin(i + g, j) && b[i + g][j] * side > 0) nu += 2;
					if (!isin(i + g, j) || b[i + g][j] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = 1; g < 9; g++)
				{
					if (isin(i, j + g) && b[i][j + g] * side > 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				for (g = -1; g > -9; g--)
				{
					if (isin(i, j + g) && b[i][j + g] * side > 0) nu += 2;
					if (!isin(i, j + g) || b[i][j + g] * side > 0) break;
					else
					{
						if (b[i + g][j] * side < 0)
						{
							nu += 9;
							break;
						}
						nu += 3;
					}
				}
				v2 += nu;
				if ((i != 0 || j != 0) && (i != 0 || j != 8) && (i != 9 || j != 0) && (i != 9 || j != 8)) v2 += 15;
				side = -side;
			}/* 车估值结束*/
			else if (b[i][j] == 2 * side)/* 马估值开始*/
			{
				int nu = 270 - number;
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && b[i + 2][j + 1] * side <= 0)
					{
						if (side == -1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i + 2, j + 1) && b[i + 2][j + 1] * side > 0)
					{
						if (side == -1)
							nu += 6;
						else
							nu += 5;
					}
					if (isin(i + 2, j - 1) && b[i + 2][j - 1] * side <= 0)
					{
						if (side == -1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i + 2, j - 1) && b[i + 2][j - 1] * side > 0)
					{
						if (side == -1)
							nu += 6;
						else
							nu += 5;
					}
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && b[i - 2][j + 1] * side <= 0)
					{
						if (side == 1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i - 2, j + 1) && b[i - 2][j + 1] * side > 0)
					{
						if (side == 1)
							nu += 6;
						else
							nu += 5;
					}
					if (isin(i - 2, j - 1) && b[i - 2][j - 1] * side <= 0)
					{
						if (side == 1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i - 2, j - 1) && b[i - 2][j - 1] * side > 0)
					{
						if (side == 1)
							nu += 6;
						else
							nu += 5;
					}
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && b[i - 1][j - 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j - 2) && b[i - 1][j - 2] * side > 0)
					{
						nu += 5;
					}
					if (isin(i + 1, j - 2) && b[i + 1][j - 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i + 1, j - 2) && b[i + 1][j - 2] * side > 0)
					{
						nu += 5;
					}
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && b[i - 1][j + 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j + 2) && b[i - 1][j + 2] * side > 0)
					{
						nu += 5;
					}
					if (isin(i + 1, j + 2) && b[i + 1][j + 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i + 1, j + 2) && b[i + 1][j + 2] * side > 0)
					{
						nu += 5;
					}
				}
				if (side == 1)
				{
					nu += 4 * (9 - abs(i - 1));
				}
				else
				{
					nu += 4 * (9 - abs(i - 8));
				}
				v1 += nu;
			}/*马估值到此为止*/
			else if (b[i][j] == -2 * side)/* 马估值开始*/
			{
				side = -side;
				int nu = 270 - number;
				if (isin(i + 1, j) && b[i + 1][j] == 0)
				{
					if (isin(i + 2, j + 1) && b[i + 2][j + 1] * side <= 0)
					{
						if (side == -1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i + 2, j + 1) && b[i + 2][j + 1] * side > 0)
					{
						if (side == -1)
							nu += 6;
						else
							nu += 5;
					}
					if (isin(i + 2, j - 1) && b[i + 2][j - 1] * side <= 0)
					{
						if (side == -1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i + 2, j - 1) && b[i + 2][j - 1] * side > 0)
					{
						if (side == -1)
							nu += 6;
						else
							nu += 5;
					}
				}
				if (isin(i - 1, j) && b[i - 1][j] == 0)
				{
					if (isin(i - 2, j + 1) && b[i - 2][j + 1] * side <= 0)
					{
						if (side == 1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i - 2, j + 1) && b[i - 2][j + 1] * side > 0)
					{
						if (side == 1)
							nu += 6;
						else
							nu += 5;
					}
					if (isin(i - 2, j - 1) && b[i - 2][j - 1] * side <= 0)
					{
						if (side == 1)
							nu += 7;
						else
							nu += 5;
					}
					else if (isin(i - 2, j - 1) && b[i - 2][j - 1] * side > 0)
					{
						if (side == 1)
							nu += 6;
						else
							nu += 5;
					}
				}
				if (isin(i, j - 1) && b[i][j - 1] == 0)
				{
					if (isin(i - 1, j - 2) && b[i - 1][j - 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j - 2) && b[i - 1][j - 2] * side > 0)
					{
						nu += 5;
					}
					if (isin(i + 1, j - 2) && b[i + 1][j - 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i + 1, j - 2) && b[i + 1][j - 2] * side > 0)
					{
						nu += 5;
					}
				}
				if (isin(i, j + 1) && b[i][j + 1] == 0)
				{
					if (isin(i - 1, j + 2) && b[i - 1][j + 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i - 1, j + 2) && b[i - 1][j + 2] * side > 0)
					{
						nu += 5;
					}
					if (isin(i + 1, j + 2) && b[i + 1][j + 2] * side <= 0)
					{
						nu += 6;
					}
					else if (isin(i + 1, j + 2) && b[i + 1][j + 2] * side > 0)
					{
						nu += 5;
					}
				}
				if (side == 1)
				{
					nu += 4 * (9 - abs(i - 1));
				}
				else
				{
					nu += 4 * (9 - abs(i - 8));
				}
				v2 += nu;
				side = -side;
			}/* 马估值结束*/
			else if (b[i][j] == 3 * side)/* 象估值开始*/
			{
				int nu = 110;
				if (isin(i + 1, j + 1) && b[i + 1][j + 1] == 0 && (side == 1 && i + 2 >= 5 || side == -1 && i + 2 < 5))/* 象不过河 */
				{
					if (b[i + 2][j + 2] * side < 0)
						nu += 5;
					else if (b[i + 2][j + 2] == 0)
						nu += 2;
					else if (b[i + 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i + 1, j - 1) && b[i + 1][j - 1] == 0 && (side == 1 && i + 2 >= 5 || side == -1 && i + 2 < 5))
				{
					if (b[i + 2][j - 2] * side < 0)
						nu += 5;
					else if (b[i + 2][j - 2] == 0)
						nu += 2;
					else if (b[i + 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j + 1) && b[i - 1][j + 1] == 0 && (side == 1 && i - 2 >= 5 || side == -1 && i - 2 < 5))
				{
					if (b[i - 2][j + 2] * side < 0)
						nu += 5;
					else if (b[i - 2][j + 2] == 0)
						nu += 2;
					else if (b[i - 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j - 1) && b[i - 1][j - 1] == 0 && (side == 1 && i - 2 >= 5 || side == -1 && i - 2 < 5))
				{
					if (b[i - 2][j - 2] * side < 0)
						nu += 5;
					else if (b[i - 2][j - 2] == 0)
						nu += 2;
					else if (b[i - 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				v1 += nu;
			}/* 象估值到此为止*/
			else if (b[i][j] == -3 * side)/* 象估值开始*/
			{
				int nu = 110;
				side = -side;
				if (isin(i + 1, j + 1) && b[i + 1][j + 1] == 0 && (side == 1 && i + 2 >= 5 || side == -1 && i + 2 < 5))/* 象不过河 */
				{
					if (b[i + 2][j + 2] * side < 0)
						nu += 5;
					else if (b[i + 2][j + 2] == 0)
						nu += 2;
					else if (b[i + 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i + 1, j - 1) && b[i + 1][j - 1] == 0 && (side == 1 && i + 2 >= 5 || side == -1 && i + 2 < 5))
				{
					if (b[i + 2][j - 2] * side < 0)
						nu += 5;
					else if (b[i + 2][j - 2] == 0)
						nu += 2;
					else if (b[i + 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j + 1) && b[i - 1][j + 1] == 0 && (side == 1 && i - 2 >= 5 || side == -1 && i - 2 < 5))
				{
					if (b[i - 2][j + 2] * side < 0)
						nu += 5;
					else if (b[i - 2][j + 2] == 0)
						nu += 2;
					else if (b[i - 2][j + 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				if (isin(i - 1, j - 1) && b[i - 1][j - 1] == 0 && (side == 1 && i - 2 >= 5 || side == -1 && i - 2 < 5))
				{
					if (b[i - 2][j - 2] * side < 0)
						nu += 5;
					else if (b[i - 2][j - 2] == 0)
						nu += 2;
					else if (b[i - 2][j - 2] == b[i][j])
						nu += 6;
					else
						nu += 2;
				}
				side = -side;
				v2 += nu;
			}/* 象估值结束*/
			else if (b[i][j] == 4 * side)//士估值开始
			{
				int nu = 110;
				if (i + 1 >= 7 && i + 1 <= 9 && j + 1 >= 3 && j + 1 <= 5 && side == 1 || i + 1 >= 0 && i + 1 <= 2 && j + 1 >= 3 && j + 1 <= 5 && side == -1)
				{
					if (b[i + 1][j + 1] <= 0)
						nu += 3;
					else if (b[i + 1][j + 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j + 1 >= 3 && j + 1 <= 5 && side == 1 || i - 1 >= 0 && i - 1 <= 2 && j + 1 >= 3 && j + 1 <= 5 && side == -1)
				{
					if (b[i - 1][j + 1] <= 0)
						nu += 3;
					else if (b[i - 1][j + 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				if (i + 1 >= 7 && i + 1 <= 9 && j - 1 >= 3 && j - 1 <= 5 && side == 1 || i + 1 >= 0 && i + 1 <= 2 && j - 1 >= 3 && j - 1 <= 5 && side == -1)
				{
					if (b[i + 1][j - 1] <= 0)
						nu += 3;
					else if (b[i + 1][j - 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j - 1 >= 3 && j - 1 <= 5 && side == 1 || i - 1 >= 0 && i - 1 <= 2 && j - 1 >= 3 && j - 1 <= 5 && side == -1)
				{
					if (b[i - 1][j - 1] <= 0)
						nu += 3;
					else if (b[i - 1][j - 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				v1 += nu;
			}//士估值到此为止
			else if (b[i][j] == -4 * side)/* 士估值开始*/
			{
				int nu = 110;
				side = -side;
				if (i + 1 >= 7 && i + 1 <= 9 && j + 1 >= 3 && j + 1 <= 5 && side == 1 || i + 1 >= 0 && i + 1 <= 2 && j + 1 >= 3 && j + 1 <= 5 && side == -1)
				{
					if (b[i + 1][j + 1] <= 0)
						nu += 3;
					else if (b[i + 1][j + 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j + 1 >= 3 && j + 1 <= 5 && side == 1 || i - 1 >= 0 && i - 1 <= 2 && j + 1 >= 3 && j + 1 <= 5 && side == -1)
				{
					if (b[i - 1][j + 1] <= 0)
						nu += 3;
					else if (b[i - 1][j + 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				if (i + 1 >= 7 && i + 1 <= 9 && j - 1 >= 3 && j - 1 <= 5 && side == 1 || i + 1 >= 0 && i + 1 <= 2 && j - 1 >= 3 && j - 1 <= 5 && side == -1)
				{
					if (b[i + 1][j - 1] <= 0)
						nu += 3;
					else if (b[i + 1][j - 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				if (i - 1 >= 7 && i - 1 <= 9 && j - 1 >= 3 && j - 1 <= 5 && side == 1 || i - 1 >= 0 && i - 1 <= 2 && j - 1 >= 3 && j - 1 <= 5 && side == -1)
				{
					if (b[i - 1][j - 1] <= 0)
						nu += 3;
					else if (b[i - 1][j - 1] == b[i][j])
						nu += 4;
					else
						nu += 1;
				}
				side = -side;
				v2 += nu;
			}/* 士估值结束*/
			else if (b[i][j] == 7 * side)/* 兵估值*/
			{
				int nu = 135 - 3 * number;
				if (side == 1)
				{
					nu += soldier_red[i][j];
				}
				else if (side == -1)
				{
					nu += soldier_black[i][j];
				}
				v1 += nu;
			}
			else if (b[i][j] == -7 * side)/* 兵估值*/
			{
				int nu = 135 - 3 * number;
				side = -side;
				if (side == 1)
				{
					nu += soldier_red[i][j];
				}
				else if (side == -1)
				{
					nu += soldier_black[i][j];
				}
				side = -side;
				v2 += nu;
			}
			else if (b[i][j] == 6 * side)/* 炮估值开始 */
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
					if (num == 0 && b[i + g][j] == -5 * side)
					{
						v1 += 5 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i + g][j] * side < 0)
							v1 = v1 + evaluate[abs(b[i + g][j])] / pow(2, num - 1);
					}
				}
				for (g = -1, num = 0; g > -10; g--)
				{

					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == -5 * side)
					{
						v1 += 5 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i + g][j] * side < 0)
							v1 = v1 + evaluate[abs(b[i + g][j])] / pow(2, num - 1);
					}
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == -5 * side)
					{
						v1 += 5 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i][j + g] * side < 0)
							v1 = v1 + evaluate[abs(b[i][j + g])] / pow(2, num - 1);
					}
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == -5 * side)
					{
						v1 += 5 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i][j + g] * side < 0)
							v1 = v1 + evaluate[abs(b[i][j + g])] / pow(2, num - 1);
					}
				}
			}
			else if (b[i][j] == -6 * side)
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
				side = -side;
				for (g = 1, num = 0; g < 10; g++)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == -5 * side)
					{
						v2 += 5 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i + g][j] * side < 0)
							v2 = v2 + evaluate[abs(b[i + g][j])] / pow(2, num - 1);
					}
				}
				for (g = -1, num = 0; g > -10; g--)
				{
					if (!isin(i + g, j)) break;
					if (num == 0 && b[i + g][j] == -5 * side)
					{
						v2 += 5 * number;
					}
					if (b[i + g][j] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i + g][j] * side < 0)
							v2 = v2 + evaluate[abs(b[i + g][j])] / pow(2, num - 1);
					}
				}
				for (g = 1, num = 0; g < 9; g++)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == -5 * side)
					{
						v2 += 5 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i][j + g] * side < 0)
							v2 = v2 + evaluate[abs(b[i][j + g])] / pow(2, num - 1);
					}
				}
				for (g = -1, num = 0; g > -9; g--)
				{
					if (!isin(i, j + g)) break;
					if (num == 0 && b[i][j + g] == -5 * side)
					{
						v2 += 5 * number;
					}
					if (b[i][j + g] != 0)
					{
						num++;
					}
					if (num >= 2)
					{
						if (b[i][j + g] * side < 0)
							v2 = v2 + evaluate[abs(b[i][j + g])] / pow(2, num - 1);
					}
				}
				side = -side;
			}/* 炮估值结束 */
		}
	return v1 - v2 + 120;
}