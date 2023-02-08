#ifndef _STD_H_
#define _STD_H_
#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include <algorithm>
#include<string>
#endif
#ifndef _FUNC_H_
#define _FUNC_H_
#define me 1
#define opp -1
extern int evaluate[8];
extern int soldier_red[10][9];
extern int soldier_black[10][9];
extern char b[10][9];
extern int m, n;
extern int tox, toy;
extern int type;
extern int redx;
extern int redy;
extern int blackx;
extern int blacky;
extern int side;
extern int mylayer;
extern int firststep;
extern std::vector<std::string> name1;

void show();
bool isdefeat(int flag);
bool ismeet();
bool isin(int i, int j);
void cut(int layer, int r, int i, int j, int& aslpha, int& beta, int a, int b, int ty, int& current);
int find(char flag, int layer, int alpha, int beta);
int eager_find(int layer, int target, int lwindow, int rwindow, int flag);
//int failsoft_find(char flag, int layer, int alpha, int beta);
int getvalue();
void show_AND_make_move();
struct movechess
{
	int i;
	int j;
	int x;
	int y;
	int val;
	movechess(int a, int b, int c, int d, int e) : i(a), j(b), x(c), y(d), val(e)
	{

	}
	bool operator<(movechess a) const
	{
		return val > a.val;
	}
};
#endif
