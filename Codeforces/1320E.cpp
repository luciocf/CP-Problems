// Codeforces 1320E - Treeland and Viruses
// Lúcio Cardoso

// Solution is the same as in editorial (using Dijkstra's)

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int in[maxn], tt;

bool mark[maxn], process[maxn];

int virus[maxn], s[maxn];

vector<int> grafo[maxn];

struct BinaryLifting
{
	int nivel[maxn], tab[maxn][20];

	void dfs(int u, int p)
	{
		in[u] = ++tt;

		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u;

			dfs(v, u);
		}
	}

	void build(int n)
	{
		for (int j = 1; j < 20; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int lca(int u, int v)
	{
		if (nivel[u] < nivel[v]) swap(u, v);

		for (int i = 19; i >= 0; i--)
			if (nivel[u]-(1<<i) >= nivel[v])
				u = tab[u][i];

		if (u == v) return u;

		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
				u = tab[u][i], v = tab[v][i];

		return tab[u][0];
	}

	int dist(int u, int v) {return nivel[u] + nivel[v] - 2*nivel[lca(u, v)];}
} LCA;

struct VirtualTree
{
	vector<pii> tree[maxn];

	void init(vector<int> &S)
	{
		for (auto v: S)
		{
			tree[v].clear();
			mark[v] = virus[v] = process[v] = 0;
		}
	}

	void build(vector<int> &S)
	{
		auto comp = [&](int a, int b) {return in[a] < in[b];};

		sort(S.begin(), S.end(), comp);

		int m = S.size();

		for (int i = 1; i < m; i++)
			S.push_back(LCA.lca(S[i-1], S[i]));

		sort(S.begin(), S.end(), comp);
		S.erase(unique(S.begin(), S.end()), S.end());

		for (int i = 1; i < S.size(); i++)
		{
			int l = LCA.lca(S[i-1], S[i]);

			tree[S[i]].push_back({l, LCA.dist(l, S[i])});
			tree[l].push_back({S[i], LCA.dist(l, S[i])});
		}
	}
} T;

void solve(vector<int> &V)
{
	priority_queue<pair<pii, pii>, vector<pair<pii, pii>>, greater<pair<pii, pii>>> fila;

	for (int i = 0; i < V.size(); i++)
	{
		int v = V[i];

		virus[v] = i+1;
		fila.push({{0, i+1}, {0, v}});
	}

	while (!fila.empty())
	{
		auto pp = fila.top(); fila.pop();

		int turno = pp.ff.ff, ind_virus = pp.ff.ss, d = pp.ss.ff, u = pp.ss.ss;
		if (process[u]) continue;

		virus[u] = ind_virus, process[u] = 1;

		for (auto pp: T.tree[u])
		{
			int v = pp.ff, w = pp.ss;

			int d2 = d+w;
			int t2 = (d2 + s[ind_virus] - 1)/s[ind_virus];

			fila.push({{t2, ind_virus}, {d2, v}});
		}
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

	LCA.dfs(1, 0); LCA.build(n);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int k, m;
		scanf("%d %d", &k, &m);

		vector<int> S, V, I;

		for (int i = 1; i <= k; i++)
		{
			int u;
			scanf("%d %d", &u, &s[i]);

			S.push_back(u);
			V.push_back(u);
		}

		while (m--)
		{
			int u;
			scanf("%d", &u);

			S.push_back(u);
			I.push_back(u);
		}

		T.build(S);

		solve(V);

		for (auto v: I)
			printf("%d ", virus[v]);
		printf("\n");

		T.init(S);
	}
}
