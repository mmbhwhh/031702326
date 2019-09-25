#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
using namespace std;

int gg[10][10];
int type;

void reset()
{
	memset(gg, 0, sizeof(gg));

}
bool check(int u, int t);
bool dfs(int u)
{
	if (u > type*type)	return true;
	int x, y;
	x = (u - 1) / type + 1;
	y = (u - 1) % type + 1;
	if (gg[x][y])	return dfs(u + 1);
	else {
		for (int i = 1; i <= type; i++)
		{
			if (check(u, i))
			{

				gg[x][y] = i;
				if (dfs(u + 1))return true;
				gg[x][y] = 0;
			}
		}
		return false;
	}
}

bool check(int u, int t)
{
	int x, y;
	x = (u - 1) / type + 1;
	y = (u - 1) % type + 1;
	for (int i = 1; i <= type; i++)
	{
		if (gg[x][i] == t && i != y)	return false;
		if (gg[i][y] == t && i != x)   return false;

	}

	if (type == 4 || type == 6 || type == 8 || type == 9)
	{
		int xs, ys;
		int beginx, beginy;//当前坐标所在宫格的左上角坐标，可当做起始坐标
		switch (type)//判断宫格的规模
		{
		case 4:
			xs = 2;
			ys = 2;
			break;
		case 6:
			xs = 2;
			ys = 3;
			break;
		case 8:
			xs = 4;
			ys = 2;
			break;
		case 9:
			xs = 3;
			ys = 3;
			break;
		}
		int flogx = xs;
		int flogy = ys;
		beginx = (x - 1) / xs * xs + 1;
		beginy = (y - 1) / ys * ys + 1;
		for (int i = beginx; flogx > 0; flogx--, i++)
		{

			for (int j = beginy; flogy > 0; flogy--, j++)
			{
				if (t == gg[i][j] && (x != i || y != j))	return false;
			}
			flogy = ys;
		}
		flogy = xs;
	}

	return true;

}

int main(int argc, char *argv[])
{
	type = atoi(argv[2]);
	int	n = atoi(argv[4]);
	fstream infile(argv[6], ios::in);
	fstream outfile(argv[8], ios::out);
	while (n)
	{

		reset();//重置棋盘
		for (int i = 1; i <= type; i++)
		{
			for (int j = 1; j <= type; j++)
			{
				infile >> gg[i][j];
			}
		}//输入数据 
		dfs(1);
		
		int i, j;
		for (i = 1; i <= type; i++)
		{
			for (j = 1; j < type; j++)
			{
				outfile << gg[i][j] << ' ';

			}
			outfile << gg[i][j] << endl;
		}
		outfile << endl;
		n--;

	}
	return 0;
}
