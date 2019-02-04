// BOI 2017 - Railway
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef pair<int, int> pii;

int chain[maxn], head[maxn], ind[maxn], back[maxn], cc, pp;

int sz[maxn], nivel[maxn], pai[maxn], n;

int freq[maxn], mark[maxn], aux;

vector<int> grafo[maxn], tree[4*maxn];

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, pai[v] = u;

		dfs(v, u);

		sz[u] += sz[v];
	}
}

void hld(int u)
{
	if (!head[cc]) head[cc] = u;
	chain[u] = cc, ind[u] = ++pp, back[pp] = u;

	int maior = -1, child = -1;
	for (auto v: grafo[u])
		if (v != pai[u] && sz[v] > maior)
			maior = sz[v], child = v;

	if (child != -1) hld(child);

	for (auto v: grafo[u])
		if (v != pai[u] && v != child)
			cc++, hld(v);
}

int lca(int u, int v)
{
	while (chain[u] != chain[v])
	{
		if (nivel[head[chain[u]]] > nivel[head[chain[v]]])
			u = pai[head[chain[u]]];
		else
			v = pai[head[chain[v]]];
	}

	return (nivel[u] > nivel[v] ? v : u);
}

void upd(int node, int l, int r, int a, int b, int v)
{
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		tree[node].push_back(v);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);
}

void upd_path(int u, int v, int it)
{
	while (true)
	{
		if (chain[u] == chain[v])
		{
			if (u != v) upd(1, 1, n, ind[v]+1, ind[u], it);
			return;
		}

		upd(1, 1, n, ind[head[chain[u]]], ind[u], it);
		u = pai[head[chain[u]]];
	}
}

void solve(int node, int l, int r)
{
	for (auto x: tree[node])
	{
		if (!mark[x]) aux++;
		mark[x]++;
	}

	if (l == r) freq[back[l]] = aux;

	if (l != r)
	{
		int mid = (l+r)>>1;

		solve(2*node, l, mid); solve(2*node+1, mid+1, r);
	}

	for (auto x: tree[node])
	{
		mark[x]--;
		if (!mark[x]) aux--;
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);
	
	int m, k;
	cin >> n >> m >> k;

	map<pii, int> mp;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v); grafo[v].push_back(u);
		mp[{u, v}] = mp[{v, u}] = i;
	}

	dfs(1, 0);
	hld(1);

	for (int i = 1; i <= m; i++)
	{
		int s, u;
		cin >> s >> u;

		for (int j = 2; j <= s; j++)
		{
			int v, low;
			cin >> v;

			low = lca(u, v);

			upd_path(u, low, i); upd_path(v, low, i);
		}
	}

	solve(1, 1, n);

	int qtd = 0;
	vector<int> ans;
	for (int i = 1; i <= n; i++)
	{
		if (freq[i] >= k)
		{
			qtd++;
			ans.push_back(mp[{i, pai[i]}]);
		}
	}

	sort(ans.begin(), ans.end());

	cout << qtd << "\n";
	if (qtd)
	{
		cout << ans[0];
		for (int i = 1; i < ans.size(); i++)
			cout << " " << ans[i];
		cout << "\n";
	}
}
