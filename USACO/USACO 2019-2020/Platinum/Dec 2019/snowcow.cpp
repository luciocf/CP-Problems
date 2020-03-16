// USACO 2019/2020 - Bessie's Snow Cow
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int sub[maxn], st[maxn], en[maxn], tt;

ll bit[2][maxn];

set<pair<int, int>> primeiro[maxn];

vector<int> grafo[maxn];

int dfs(int u, int p)
{
	sub[u] = 1, st[u] = ++tt;

	for (auto v: grafo[u])
		if (v != p)
			sub[u] += dfs(v, u);

	en[u] = tt;
	return sub[u];
}

void upd(int x, int v, int q)
{
	for (; x < maxn; x += (x&-x))
		bit[q][x] += 1ll*v;
}

ll soma(int x, int q)
{
	ll ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[q][x];
	return ans;
}

int main(void)
{
	freopen("snowcow.in", "r", stdin);
	freopen("snowcow.out", "w", stdout);

	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(1, 0);

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int u, c;
			scanf("%d %d", &u, &c);

			auto it = primeiro[c].upper_bound({st[u], n+1});

			if (it != primeiro[c].begin() && en[prev(it)->second] >= en[u]) continue;

			for (; it != primeiro[c].end() && en[it->second] <= en[u]; )
			{
				int v = it->second;

				upd(st[v], -1, 0); upd(en[v]+1, 1, 0);
				upd(st[v], -sub[v], 1);

				it = primeiro[c].erase(it);
			}

			primeiro[c].insert({st[u], u});

			upd(st[u], 1, 0); upd(en[u]+1, -1, 0);
			upd(st[u], sub[u], 1);
		}
		else
		{
			int u;
			scanf("%d", &u);

			ll ans = 1ll*sub[u]*soma(st[u], 0);
			ans += (soma(en[u], 1)-soma(st[u], 1));

			printf("%lld\n", ans);
		}
	}
}
