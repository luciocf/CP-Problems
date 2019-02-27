// IOI 2010 - Quality of Living
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "quality.h"

using namespace std;

const int maxn = 3e3+10;

int n, m, a, b;
int num[maxn][maxn], soma[maxn][maxn];

bool ok(int x)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			soma[i][j] = soma[i][j-1]+soma[i-1][j]-soma[i-1][j-1];
			if (num[i][j] > x) soma[i][j]++;
			else if (num[i][j] < x) soma[i][j]--;
		}
	}

	for (int i = a; i <= n; i++)
		for (int j = b; j <= m; j++)
			if (soma[i][j]-soma[i-a][j]-soma[i][j-b]+soma[i-a][j-b] <= 0)
				return true;

	return false;
}

int busca(void)
{
	int ini = 1, fim = n*m, ans = fim+1;
	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001])
{
	n = R, m = C, a = H, b = W;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			num[i+1][j+1] = Q[i][j];

	return busca();
}
