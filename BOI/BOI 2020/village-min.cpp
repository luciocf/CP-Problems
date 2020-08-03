// BOI 2020 - Village (Minimum)
// Lúcio Cardoso

// Solution is the same as in: http://www.boi2020.lv/data/spoilers/village.pdf

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

ll ans;
int f[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	vector<int> child;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		if (!mark[v]) child.push_back(v);
	}

	if (child.size() != 0)
	{
		mark[u] = 1;
		ans += 2ll*child.size();

		for (int i = 1; i < child.size(); i++)
			f[child[i]] = child[i-1];

		f[child[0]] = u, f[u] = child.back();
	}
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

	int root;

	for (int i = 1; i <= n; i++)
		for (auto v: grafo[i])
			if (grafo[v].size() == 1)
				root = i;

	dfs(root, 0);

	printf("%lld\n", ans);
	for (int i = 1; i <= n; i++)
		printf("%d ", f[i]);
	printf("\n");
}
