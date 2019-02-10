// JOI Open Contest 2018 - Xylophone
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "xylophone.h"

using namespace std;

const int maxn = 5e3+10;

int n;
int num[maxn];
int dif[maxn][maxn];

bool maior[maxn];

void getQ(void)
{
	for (int i = 1; i < n; i++)
	{
		dif[i][i+1] = query(i, i+1);
		if (i < n-1) dif[i][i+2] = query(i, i+2);
	}
}

void getMaior(void)
{
	for (int i = 3; i <= n; i++)
	{
		if (!maior[i-1])
		{
			if (dif[i-2][i-1] == dif[i-2][i]) maior[i] = 1;
			else if (dif[i-2][i-1] > dif[i-2][i]) maior[i] = 0;
			else
			{
				if (dif[i-2][i] > dif[i-1][i]) maior[i] = 0;
				else maior[i] = 1;
			}
		}
		else
		{
			if (dif[i-2][i-1] == dif[i-2][i]) maior[i] = 0;
			else if (dif[i-2][i-1] > dif[i-2][i]) maior[i] = 1;
			else
			{
				if (dif[i-2][i] > dif[i-1][i]) maior[i] = 1;
				else maior[i] = 0;
			}
		}
	}
}

void getNumbers(void)
{
	int ind;

	for (int i = 1; i <= n; i++)
	{
		if (!maior[i]) continue;

		int x = dif[i-1][i];
		bool ok = 1;
		for (int j = i-1; j > 1; j--)
		{
			if (maior[j]) x += dif[j-1][j];
			else x -= dif[j-1][j];

			if (x < 0) ok = 0;
		}

		if (!ok) continue;

		if (maior[i+1]) continue;

		x = dif[i][i+1];
		ok = 1;
		for (int j = i+2; j <= n; j++)
		{
			if (maior[j]) x -= dif[j-1][j];
			else x += dif[j-1][j];

			if (x < 0) ok = 0;
		}

		if (ok)
		{
			ind = i;
			break;
		}
	}

	num[ind] = n;

	for (int i = ind-1; i >= 1; i--)
	{
		if (maior[i+1]) num[i] = num[i+1]-dif[i][i+1];
		else num[i] = num[i+1]+dif[i][i+1];
	}

	for (int i = ind+1; i <= n; i++)
	{
		if (maior[i]) num[i] = num[i-1]+dif[i-1][i];
		else num[i] = num[i-1]-dif[i-1][i];
	}
}

void solve(int N)
{
	n = N;

	getQ();

	maior[1] = maior[2] = 1;

	getMaior();
	getNumbers();

	bool get1 = 0, ok = 1;
	for (int i = 1; i <= n; i++)
	{
		if (num[i] == 1) get1 = 1;

		if (num[i] == n && !get1) ok = 0;
	}


	if (!ok)
	{
		maior[2] = 0;
		getMaior();
		getNumbers();
	}

	for (int i = 1; i <= n; i++)
		answer(i, num[i]);
}
