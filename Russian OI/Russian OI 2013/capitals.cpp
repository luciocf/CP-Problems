// Russian OI 2013 - Capitals
// Lúcio Cardoso

// Solution is the same as: https://github.com/SpeedOfMagic/CompetitiveProgramming/blob/master/RusOI-reg/13-capitals.cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int n, D;

int tot[maxn];
int val[maxn];

vector<int> grafo[maxn];
vector<int> sub[maxn];

struct Centroid
{
	int sz[maxn], qtd[maxn];
	bool mark[maxn];

	void dfs(int u, int p)
	{
		sz[u] = 1;

		for (auto v: grafo[u])
		{
			if (v == p || mark[v]) continue;

			dfs(v, u);

			sz[u] += sz[v];
		}
	}

	int centroid(int u, int p, int S)
	{
		for (auto v: grafo[u])
			if (v != p && !mark[v] && sz[v] > S/2)
				return centroid(v, u, S);

		return u;
	}

	void upd(int u, int p, int d, int add)
	{
		qtd[d] += add;

		for (auto v: grafo[u])
			if (v != p && !mark[v])
				upd(v, u, d+1, add);
	}

	void get(int u, int p, int d)
	{
		if (d <= D/2) tot[u] += qtd[D/2-d];

		for (auto v: grafo[u])
			if (v != p && !mark[v])
				get(v, u, d+1);
	}

	void decompose(int u)
	{
		dfs(u, 0);

		int c = centroid(u, 0, sz[u]);
		mark[c] = 1;

		upd(c, 0, 0, 1);

		for (auto v: grafo[c])
		{
			if (mark[v]) continue;

			upd(v, c, 1, -1);
			get(v, c, 1);
			upd(v, c, 1, 1);
		}

		tot[c] += qtd[D/2];

		upd(c, 0, 0, -1);

		for (auto v: grafo[c])
			if (!mark[v])
				decompose(v);
	}
} C;

struct BinaryLifting
{
	int nivel[maxn], tab[maxn][20];

	void dfs(int u, int p)
	{
		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u;
			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int j = 1; j < 20; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int kth(int u, int k)
	{
		for (int i = 19; i >= 0; i--)
			if (k >= (1<<i))
				u = tab[u][i], k -= (1<<i);

		return u;
	}
} LCA;

ll get_ans(int u)
{
	if (sub[u].size() < 3) return 0;

	int pref = sub[u][0];
	ll pref_2 = 0, ans = 0;

	for (int i = 1; i < sub[u].size(); i++)
	{
		int x = sub[u][i];

		ans += 1ll*x*pref_2;

		pref_2 += 1ll*x*pref;

		pref += x;
	}

	return ans;
}

int main(void)
{
	freopen("capitals.in", "r", stdin); freopen("capitals.out", "w", stdout);

	scanf("%d %d", &n, &D);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	if (D%2)
	{
		printf("0\n");
		return 0;
	}

	C.decompose(1);
	LCA.dfs(1, 0); LCA.build();
	
	for (int i = 1; i <= n; i++)
	{
		if (LCA.nivel[i] >= D/2)
		{
			int u = LCA.kth(i, D/2-1);
			val[u]++;
		}
	}

	for (int u = 1; u <= n; u++)
	{
		int soma = 0;

		for (auto v: grafo[u])
			if (v != LCA.tab[u][0])
				sub[u].push_back(val[v]), soma += val[v];

		sub[u].push_back(tot[u]-soma);
	}

	ll ans = 0;

	for (int i = 1; i <= n; i++)
		ans += get_ans(i);

	printf("%lld\n", ans);
}
