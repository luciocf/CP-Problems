// Codeforces 1205D - Almost All
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+10;

int n;

int sz[maxn];

vector<int> filho[maxn];

vector<int> grafo[maxn];

map<pii, int> ans;

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

int solve(int u, int p, int val, int soma, int add)
{
	ans[{u, p}] = val-soma, soma = val;
	val += add;

	for (auto v: grafo[u])
		if (v != p)
			val = solve(v, u, val, soma, add) + add;

	return val-add;
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

	if (n == 1) return 0;
	if (n == 2)
	{
		printf("1 2 1\n");
		return 0;
	}

	dfs(1, 0);

	int c = centroid(1, 0);
	dfs(c, 0);

	priority_queue<pii, vector<pii>, greater<pii>> pq;

	for (auto i: grafo[c])
	{
		filho[i].push_back(i);
		pq.push({sz[i], i});
	}

	while (pq.size() > 2)
	{
		int su = pq.top().first, u = pq.top().second; pq.pop();
		int sv = pq.top().first, v = pq.top().second; pq.pop();

		for (auto f: filho[u])
			filho[v].push_back(f);

		pq.push({su+sv, v});
	}

	int a = pq.top().second; pq.pop();
	int b = pq.top().second; pq.pop();

	int at = 1;
	for (auto f: filho[a])
		at = solve(f, c, at, 0, 1)+1;

	int add = at;
	for (auto f: filho[b])
		at = solve(f, c, at, 0, add)+add;

	for (auto e: ans)
		printf("%d %d %d\n", e.first.first, e.first.second, e.second);
}
