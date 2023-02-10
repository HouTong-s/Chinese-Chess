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
#define RED 1
#define BLACK -1
extern int evaluate[8];
extern int soldier_value[10][9];
//extern int soldier_black[10][9];
extern char board[10][9];
//tempboard¥Ê¥¢æµœÒ∆Â≈Ã
extern char tempboard[10][9];
extern int m, n;
extern int tox, toy;
extern int type;
extern int red_y;
extern int red_x;
extern int black_y;
extern int black_x;
extern int side;
extern int mylayer;
extern int is_firststep;
extern std::vector<std::string> chess_names;

struct movechess
{
	char x;
	char y;
	char move_x;
	char move_y;
	short val;
	movechess(char a, char b, char c, char d, short e);
	bool operator<(movechess a) const;
};

void show();
bool isdefeat(int flag);
bool ismeet();
bool isin(int i, int j);
short find(char flag, int layer, int alpha, int beta);
int eager_find(int layer, int target, int lwindow, int rwindow, int flag);
short getvalue();
void show_AND_make_move();
short getRED_value(int total_chess,char arr[10][9]);
void generateMove(std::vector<movechess>& arr, char flag);
void MakeMove(std::vector<movechess>::iterator, int&, int&, char);
void UnMove(std::vector<movechess>::iterator, int, int, char);




#endif
