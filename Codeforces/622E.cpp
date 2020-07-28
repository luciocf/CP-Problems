// Codeforces 622E - Ants in Leaves
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

vector<int> grafo[maxn], l;

int dfs(int u, int p, int d)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;
		dfs(v, u, d+1);
	}

	if (grafo[u].size() == 1)
		l.push_back(d);

	if (p == 1)
	{
		sort(l.begin(), l.end());

		int ans = 0;
		for (auto x: l)
			ans = max(x, ans+1);

		return ans;
	}

	return 0;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	int ans = 0;

	for (auto v: grafo[1])
	{
		l.clear();
		ans = max(ans, dfs(v, 1, 1));
	}

	printf("%d\n", ans);
}
