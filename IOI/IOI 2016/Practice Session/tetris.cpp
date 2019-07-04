// IOI 2016 Practice Session - Mini Tetris
// Lúcio Cardoso

// Solution is equal to this one: https://github.com/Rockbet/Problems/blob/master/IOI/2016/Day%200/Mini%20Tetris.cpp

#include <bits/stdc++.h>
#include "tetris.h"

using namespace std;

int type;

void init(int n) 
{
	type = 0;
}

int position;
int rotation;

void new_figure(int figure)
{
	if (type == 0)
	{
		if (figure == 1) position = rotation = 0, type = 0;
		if (figure == 2) position = rotation = 0, type = 2;
		if (figure == 3) position = rotation = 0, type = 1;
	}
	else if (type == 1)
	{
		if (figure == 1) position = rotation = 0, type = 1;
		if (figure == 2) position = 1, rotation = 0, type = 2;
		if (figure == 3) position = 1, rotation = 2, type = 0;
	}
	else if (type == 2)
	{
		if (figure == 1) position = rotation = 0, type = 2;
		if (figure == 2) position = 2, rotation = 1, type = 4;
		if (figure == 3) position = 1, rotation = 2, type = 3;
	}
	else if (type == 3)
	{
		if (figure == 1) position = rotation = 0, type = 3;
		if (figure == 2) position = 0, rotation = 1, type = 5;
		if (figure == 3) position = 0, rotation = 3, type = 2;
	}
	else if (type == 4)
	{
		if (figure == 1) position = rotation = 0, type = 4;
		if (figure == 2) position = rotation = 0, type = 0;
		if (figure == 3) position = rotation = 0, type = 5;
	}
	else
	{
		if (figure == 1) position = rotation = 0, type = 5;
		if (figure == 2) position = 1, rotation = 0, type = 0;
		if (figure == 3) position = rotation = 1, type = 4;
	}
}

int get_position()
{
	return position;
}

int get_rotation() 
{
	return rotation;
}

