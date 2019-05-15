// USACO 2015-2016 - 248
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 250;
const int inf = 1e9+10;

int n;
int a[maxn];

int dp[maxn][maxn];

int solve(int l, int r)
{
	if (l > r) return -inf;;
	if (l == r) return a[l];
	if (dp[l][r] != -1) return dp[l][r];

	int ans = 0;
	for (int i = l; i < r; i++)
	{
		int a = solve(l, i);
		int b = solve(i+1, r);

		if (a == b)
			ans = max(ans, a+1);
	}

	return dp[l][r] = ans;
}

int main(void)
{
	FILE *fin = fopen("248.in", "r");
	FILE *fout = fopen("248.out", "w");

	fscanf(fin, "%d", &n);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &a[i]);

	memset(dp, -1, sizeof dp);

	int ans = 0;
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++)
			ans = max(ans, solve(l, r));
		
	fprintf(fout, "%d\n", ans);
}
