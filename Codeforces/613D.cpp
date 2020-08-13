// Codeforces 613D - Kingdom and its Cities
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int in[maxn], tt;

bool mark[maxn];

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

			nivel[v] = nivel[u]+1;
			tab[v][0] = u;

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

	void init(vector<int> &V)
	{
		for (auto v: V)
		{
			tree[v].clear();
			mark[v] = 0;
		}
	}

	vector<int> build(vector<int> S)
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

			tree[S[i]].push_back({l, LCA.dist(S[i], l)});
			tree[l].push_back({S[i], LCA.dist(S[i], l)});
		}

		return S;
	}
} T;

int ans, ruim;
int tem[maxn];

void solve(int u, int p)
{
	int soma = 0;

	for (auto pp: T.tree[u])
	{
		int v = pp.ff, w = pp.ss;
		if (v == p) continue;

		solve(v, u);

		if (mark[u] && mark[v] && w == 1) ruim = 1;

		soma += tem[v];
	}

	if (mark[u])
	{
		tem[u] = 1;
		ans += soma; 
	}
	else
	{
		if (soma == 1) tem[u] = 1;
		else
		{
			tem[u] = 0;
			if (soma) ans++;
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
		int k;
		scanf("%d", &k);

		vector<int> V;

		while (k--)
		{
			int v;
			scanf("%d", &v);

			V.push_back(v);
		}

		for (auto v: V)
			mark[v] = 1;

		vector<int> S = T.build(V);

		ans = ruim = 0;
		solve(S[0], 0);

		if (ruim) printf("-1\n");
		else printf("%d\n", ans);

		T.init(S);
	}
}
