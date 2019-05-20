// USACO 2014-2015 - Marathon
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e2+10;
const int inf = 1e9+10;

int n, k;

int dp[maxn][maxn];

int x[maxn], y[maxn];

int dist(int i, int j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

int solve(int i, int j)
{
	if (i == n) return 0;
	if (dp[i][j] != -1) return dp[i][j];

	int ans = inf;

	for (int nxt = i+1; nxt <= n; nxt++)
	{
		if (nxt-i-1 > j) break;

		int v = j-(nxt-i-1);

		ans = min(ans, dist(i, nxt)+solve(nxt, v));
	}

	return dp[i][j] = ans;
}

int main(void)
{
	FILE *fin = fopen("marathon.in", "r");
	FILE *fout = fopen("marathon.out", "w");

	fscanf(fin, "%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d %d", &x[i], &y[i]);

	memset(dp, -1, sizeof dp);

	fprintf(fout, "%d\n", solve(1, k));
}
