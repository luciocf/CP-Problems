// USACO 2012/2013 - Balanced Cow Breeds
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

string s;

int n;
int soma[maxn];

int dp[maxn][maxn];

int solve(int i, int s_a)
{
	if (i == n+1)
	{
		int s_b = soma[n]-s_a;

		if (s_a == 0 && s_b == 0) return 1;
		return 0;
	}
	if (dp[i][s_a] != -1) return dp[i][s_a];

	int s_b = soma[i-1]-s_a;
	int ans = 0;

	if (s[i-1] == '(')
	{
		ans = solve(i+1, s_a+1);
		ans = (ans + solve(i+1, s_a))%2012;
	}
	else
	{
		if (s_a > 0) ans = (ans + solve(i+1, s_a-1))%2012;
		if (s_b > 0) ans = (ans + solve(i+1, s_a))%2012;
	}

	return dp[i][s_a] = ans;
}

int main(void)
{
	freopen("bbreeds.in", "r", stdin); freopen("bbreeds.out", "w", stdout);

	cin >> s;

	n = s.size();

	for (int i = 0; i < n; i++)
	{
		if (s[i] == '(') soma[i+1] = soma[i]+1;
		else soma[i+1] = soma[i]-1;
	}

	memset(dp, -1, sizeof dp);
	printf("%d\n", solve(1, 0));
}
