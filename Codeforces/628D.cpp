// Codeforces 628D - Magic Numbers
// Lúcio Cardoso

// Solution is the same as in editorial (with digit dp), except I coded in a messier way

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;
const int M = 1e9+7;

int m, d;
string a, b;

int pot[maxn];

int dp[maxn][maxn][2][2][2][2];

int solve(int i, int mod, int f1, int f2, int par, int prim)
{
	if (i == 0 && mod == 0) return 1;
	if (i == 0) return 0;
	if (dp[i][mod][f1][f2][par][prim] != -1) return dp[i][mod][f1][f2][par][prim];

	int ans = 0;

	for (int j = 0; j <= 9; j++)
	{
		if (j == 0 && prim) continue;
		if (j == d && par == i%2) continue;
		if (par != i%2 && j != d) continue;

		if (b.size() >= i && f1 == 0 && (char)(j+'0') > b[i-1]) continue;
		if (f2 == 0 && (char)(j+'0') < a[i-1]) continue;

		int g1 = f1, g2 = f2;

		if (g1 || (char)(j+'0') < b[i-1]) g1 = 1;
		if (g2 || (char)(j+'0') > a[i-1]) g2 = 1;

		ans = (ans + solve(i-1, (mod + pot[i-1]*j)%m, g1, g2, par, 0))%M;
	}

	return dp[i][mod][f1][f2][par][prim] = ans;
}

int main(void)
{
	scanf("%d %d", &m, &d);

	pot[0] = 1;
	for (int i = 1; i <= 2000; i++)
		pot[i] = (10*pot[i-1])%m;

	cin >> a >> b;

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	memset(dp, -1, sizeof dp);

	int ans = 0;

	for (int i = b.size(); i >= a.size(); i--)
	{
		int f1 = 0, f2 = 0;

		if (i < b.size()) f1 = 1;
		if (i > a.size()) f2 = 1;

		ans = (ans + solve(i, 0, f1, f2, i%2, 1))%M;
	}

	printf("%d\n", ans);
}
