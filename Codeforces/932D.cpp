// Codeforces 932D - Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 4e5+10;

int a[maxn];

int prox[maxn];

int tab[maxn][20], mx[maxn][20];

int tab_prox[maxn][20];
ll soma[maxn][20];

void build(int u, int p)
{
	tab[u][0] = p, mx[u][0] = a[p];

	for (int i = 1; i < 20; i++)
	{
		tab[u][i] = tab[tab[u][i-1]][i-1];
		mx[u][i] = max(mx[u][i-1], mx[tab[u][i-1]][i-1]);
	}
}

void build2(int u)
{
	tab_prox[u][0] = prox[u], soma[u][0] = a[prox[u]];

	for (int i = 1; i < 20; i++)
	{
		tab_prox[u][i] = tab_prox[tab_prox[u][i-1]][i-1];
		soma[u][i] = soma[u][i-1] + soma[tab_prox[u][i-1]][i-1];
	}
}

int find_maior(int u)
{
	int w = a[u];

	for (int i = 19; i >= 0; i--)
		if (mx[u][i] < w)
			u = tab[u][i];

	return tab[u][0];
}

int get_ans(int u, ll x)
{
	if (a[u] > x) return 0;

	int ans = 1;
	ll s = a[u];

	for (int i = 19; i >= 0; i--)
		if (tab_prox[u][i] && s + 1ll*soma[u][i] <= x)
			ans += (1<<i), s += soma[u][i], u = tab_prox[u][i];

	return ans;
}

int main(void)
{
	int q;
	scanf("%d", &q);

	int last = 0;
	int n = 1;

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			ll p, q;
			scanf("%lld %lld", &p, &q);

			int pai = p^last, w = q^last;
			int u = ++n;

			a[u] = w;

			build(u, pai);
			prox[u] = find_maior(u);

			build2(u);
		}
		else
		{
			ll p, q;
			scanf("%lld %lld", &p, &q);

			int u = p^last;
			ll x = q^last;

			last = get_ans(u, x);
			printf("%d\n", last);
		}
	}
}
