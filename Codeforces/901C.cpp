// Codeforces 901C - Bipartite Segments
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;

int n, m;

int nivel[maxn], pai[maxn];
bool mark[maxn];

int mx[maxn];
ll pref[maxn];

vector<int> grafo[maxn];

void get_ciclo(int u, int v)
{
	int menor = n+1, maior = 0;

	while (u && nivel[u] >= nivel[v])
	{
		menor = min(menor, u);
		maior = max(maior, u);

		u = pai[u];
	}

	mx[menor] = min(mx[menor], maior);
}

void dfs(int u, int p)
{
	mark[u] = 1;

	for (auto v: grafo[u])
	{
		if (mark[v])
		{
			if (v == p || nivel[v] > nivel[u]) continue;

			get_ciclo(u, v);

			continue;
		}

		nivel[v] = nivel[u]+1;
		pai[v] = u;

		dfs(v, u);
	}
}

ll soma(int x)
{
	return 1ll*x*(x+1)/2ll;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n+1; i++)
		mx[i] = n+1;

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i, 0);

	for (int i = n; i >= 1; i--)
		mx[i] = min(mx[i], mx[i+1]);

	for (int i = 1; i <= n; i++)
		pref[i] = pref[i-1] + 1ll*(mx[i]-i);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		int ini = l, fim = r, ind = r+1;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (mx[mid] > r) ind = mid, fim = mid-1;
			else ini = mid+1;
		}

		ll ans = 0;

		if (ind != r+1)
		{
			ans += 1ll*(r+1)*(r-ind+1);
			ans -= (1ll*soma(r)-soma(ind-1));
		}

		if (ind > l) ans += pref[ind-1]-pref[l-1];

		printf("%lld\n", ans);
	}
}
