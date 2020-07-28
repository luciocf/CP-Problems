// Codeforces 1249F - Maximum Weight Subset
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;

int n, k;
int a[maxn];

int dp[maxn][maxn];
int dp_pref[maxn][maxn];

vector<int> grafo[maxn];

void solve(int u, int p)
{
	dp[u][0] = a[u];

	vector<int> child;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		child.push_back(v);

		solve(v, u);

		int mx = 0;
		for (int i = k; i <= n; i++)
			mx = max(mx, dp[v][i]);

		dp[u][0] += mx;
	}

	memset(dp_pref, 0, sizeof dp_pref);

	for (int i = 0; i < child.size(); i++)
	{
		int v = child[i];

		for (int j = 1; j <= n; j++)
			for (int l = 1; l <= n; l++)
				if (l+j > k)
					dp_pref[i+1][min(j, l)] = max(dp_pref[i+1][min(j, l)], dp_pref[i][j] + dp[v][l-1]);
	}

	for (int i = 1; i <= n; i++)
		dp[u][i] = dp_pref[child.size()][i];
}

int main(void)
{
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	solve(1, 0);

	int mx = 0;
	for (int i = 0; i <= n; i++)
		mx = max(mx, dp[1][i]);

	cout << mx << "\n";
}
