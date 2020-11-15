// Codeforces 1198D - Rectangle Painting 1
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int n;
char a[maxn][maxn];

int dp[maxn][maxn][maxn][maxn];

int solve(int l_lin, int r_lin, int l_col, int r_col)
{
	if (r_lin == l_lin && r_col == l_col) return (a[l_lin][l_col] == '#' ? 1 : 0);
	if (dp[l_lin][r_lin][l_col][r_col] != -1) return dp[l_lin][r_lin][l_col][r_col];

	int ans = max(r_lin-l_lin+1, r_col-l_col+1);

	for (int i = l_lin; i < r_lin; i++)
		ans = min(ans, solve(l_lin, i, l_col, r_col) + solve(i+1, r_lin, l_col, r_col));

	for (int i = l_col; i < r_col; i++)
		ans = min(ans, solve(l_lin, r_lin, l_col, i) + solve(l_lin, r_lin, i+1, r_col));

	return dp[l_lin][r_lin][l_col][r_col] = ans;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf(" %c", &a[i][j]);

	memset(dp, -1, sizeof dp);
	printf("%d\n", solve(1, n, 1, n));
}
