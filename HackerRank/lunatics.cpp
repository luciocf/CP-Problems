// HackerRank - IOI 2014 Practice Contest - Guardians of the Lunatics
// Lúcio Cardoso

// Solution uses Divide and Conquer DP Optimization.
// Same as: https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 8e3+20;

const int maxm = 820;

const long long inf = 1111111111111111111LL;

int opt[maxm][maxn], num[maxn];

ll dp[maxm][maxn], soma[maxn];

void solve(int i, int l, int r)
{
	if (l > r) return;

	ll mid = (l+r)>>1;

	for (ll k = max(i, opt[i][l-1]); k <= mid && k <= opt[i][r+1]; k++)
	{
		ll cost = (mid-k+1LL)*(soma[mid]-soma[k-1]);

		if (dp[i][mid] > dp[i-1][k-1]+cost)
			dp[i][mid] = dp[i-1][k-1]+cost, opt[i][mid] = k;
	}

	solve(i, l, mid-1); solve(i, mid+1, r);
}

int main(void)
{
	int n, m;
	cin >> n >> m;
	m = min(n, m);

	for (int i = 1; i <= n; i++)
	{
		cin >> num[i];
		soma[i] = soma[i-1]+(ll)num[i];
	}

	for (int i = 2; i <= m; i++)
		for (int j = 1; j <= n; j++)
			dp[i][j] = inf;

	for (int i = 1; i <= n; i++)
		dp[1][i] = (ll)i*soma[i];

	for (int i = 2; i <= m; i++)
	{
		opt[i][0] = 1, opt[i][n+1] = n;
		solve(i, 1, n);
	}
	cout << dp[m][n] << "\n";
}
