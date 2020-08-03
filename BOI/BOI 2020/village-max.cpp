// BOI 2020 - Village (Maximum)
// Lúcio Cardoso

// Solution is pretty much the same as in: http://www.boi2020.lv/data/spoilers/village.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;

int sz[maxn];
int h[maxn];

int back[maxn], tt;
int f[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v != p)
		{
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

int centroid(int u, int p)
{
	for (auto v: grafo[u])
		if (v != p && sz[v] > n/2)
			return centroid(v, u);

	return u;
}

void dfs2(int u, int p)
{
	h[u] = (p ? h[p]+1 : 0);
	back[++tt] = u;

	for (auto v: grafo[u])
		if (v != p)
			dfs2(v, u);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);
	int c = centroid(1, 0);
	dfs2(c, 0);

	for (int i = (n%2 ? 2 : 1); i <= n/2; i++)
	{
		f[back[i]] = back[i+n/2];
		f[back[i+n/2]] = back[i];
	}

	if (n%2)
	{
		f[c] = back[(n+1)/2];
		f[back[(n+1)/2]] = back[n];
		f[back[n]] = c;
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += 1ll*h[i];

	printf("%lld\n", 2ll*ans);
	for (int i = 1; i <= n; i++)
		printf("%d ", f[i]);
	printf("\n");
}
