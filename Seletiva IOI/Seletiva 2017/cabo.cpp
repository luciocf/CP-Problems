// Seletiva IOI 2017 - Cabo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;
const int maxv = 1300;

int num[maxn], s, n;

int dp[maxn][maxn][maxv];

int solve(int pos, int x, int v)
{
	if (v > s/2) return 0;
	if (pos == n+1 && x != n/2) return 0;
	if (pos == n+1 && x == n/2) return dp[n+1][x][v] = 1;
	if (dp[pos][x][v] != -1) return dp[pos][x][v];

	int caso1 = solve(pos+1, x, v);
	int caso2 = solve(pos+1, x+1, v+num[pos]);

	return dp[pos][x][v] = (caso1||caso2);
}

int main(void)
{
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> num[i], s += num[i];

	memset(dp, -1, sizeof dp);

	solve(1, 0, 0);

	for (int i = s/2; i >= 1; i--)
	{
		if (dp[n+1][n/2][i] == 1)
		{
			cout << s-2*i << "\n";
			break;
		}
	}
}