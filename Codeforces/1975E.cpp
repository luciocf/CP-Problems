// Codeforces 1975E - Chain Queries
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;
const int maxl = 20;

int n;
int qtd[maxn], a[maxn];
vector<int> grafo[maxn];

struct BinaryLifting
{
	int tab[maxn][20], nivel[maxn];

	void dfs(int u, int p)
	{
		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1;
			tab[v][0] = u;
			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int i = 1; i <= n; i++)
		{
			nivel[i] = 0;
			for (int j = 0; j < maxl; j++)
				tab[i][j] = -1;
		}

		dfs(1, 0);

		for (int j = 1; j < maxl; j++)
			for (int i = 1; i <= n; i++)
				if (tab[i][j-1] != -1)
					tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int lca(int u, int v)
	{
		if (nivel[u] < nivel[v]) swap(u, v);

		for (int i = maxl-1; i >= 0; i--)
			if (nivel[u]-(1<<i) >= nivel[v])
				u = tab[u][i];

		if (u == v) return u;

		for (int i = maxl-1; i >= 0; i--)
			if (tab[u][i] != -1 and tab[v][i] != -1 and tab[u][i] != tab[v][i])
				u = tab[u][i], v = tab[v][i];

		return tab[u][0];
	}
} LCA;

void solve(void)
{
	int q;
	cin >> n >> q;

	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		grafo[i].clear(), qtd[i] = 0;
	}

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].pb(v); grafo[v].pb(u);
	}

	LCA.build();

	for (int u = 1; u <= n; u++)
		for (auto v: grafo[u])
			if (LCA.nivel[u] < LCA.nivel[v] and a[v] == 1)
				qtd[u]++;

	set<pii> st, stLevel;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 1)
		{
			st.insert({qtd[i], i});
			stLevel.insert({LCA.nivel[i], i});
		}
	}

	while (q--)
	{
		int u;
		cin >> u;

		if (a[u] == 0)
		{
			a[u] = 1;
			if (u != 1)
			{
				int p = LCA.tab[u][0];

				if (a[p] == 1) st.erase({qtd[p], p});
				qtd[p]++;
				if (a[p] == 1) st.insert({qtd[p], p});
			}

			st.insert({qtd[u], u});
			stLevel.insert({LCA.nivel[u], u});
		}
		else
		{
			a[u] = 0;
			if (u != 1)
			{
				int p = LCA.tab[u][0];

				if (a[p] == 1) st.erase({qtd[p], p});
				qtd[p]--;
				if (a[p] == 1) st.insert({qtd[p], p});
			}

			st.erase({qtd[u], u});
			stLevel.erase({LCA.nivel[u], u});
		}

		if (st.size() == 0)
		{
			cout << "No\n";
			continue;
		}

		auto it = st.begin();
		int x = it->ss;

		if (st.size() == 1)
		{
			cout << "Yes\n";
			continue;
		}

		it = next(it);

		int y = it->ss;
		int l = LCA.lca(x, y);

		if (it->ff > 0)
		{
			cout << "Yes\n";
			continue;
		}

		if (LCA.nivel[x]+LCA.nivel[y]-2*LCA.nivel[l]+1 != st.size())
		{
			cout << "No\n";
			continue;
		}

		if (LCA.nivel[l] > stLevel.begin()->ff)
		{
			cout << "No\n";
			continue;
		}

		if (st.size() == 2)
		{
			cout << "Yes\n";
			continue;
		}

		it = next(it);
		if (it->ff == 0) cout << "No\n";
		else cout << "Yes\n";
	}
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		solve();
	}
}
