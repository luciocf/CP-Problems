// APIO 2018 - Duathlon
// Lúcio Cardoso

#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5+10;

int n;

pii edge[maxn];

int in[maxn], low[maxn], tt;
bool mark_edge[maxn], art[maxn];

int sz_bcc[maxn], sz_comp;

vector<vector<int>> bcc;
vector<int> tree[maxn];

vector<pii> grafo[maxn];

stack<int> stk;

void make_component(int last)
{
	bcc.push_back(vector<int>());

	while (!stk.empty())
	{
		int e = stk.top(); stk.pop();

		bcc.back().push_back(e);

		if (e == last) break;
	}
}

void lowlink(int u, bool isroot)
{
	in[u] = low[u] = ++tt;
	++sz_comp;

	bool fwd = 0;

	for (auto pp: grafo[u])
	{
		int v = pp.ff, e = pp.ss;
		if (mark_edge[e]) continue;

		mark_edge[e] = 1;
		stk.push(e);

		if (in[v])
		{
			low[u] = min(low[u], in[v]);
			continue;
		}

		lowlink(v, 0);

		low[u] = min(low[u], low[v]);

		if (isroot ? fwd : (low[v] >= in[u]))
		{
			art[u] = 1;
			make_component(e);
		}

		fwd = 1;
	}
}

int sub[maxn];
bool vis[maxn];

ll ans, dp[maxn];

ll choose2(int x)
{
	return 1ll*x*(x-1)/2ll;
}

ll choose3(int x)
{
	return 1ll*x*(x-1)*(x-2);
}

void dfs(int u, int p)
{
	vis[u] = 1;
	sub[u] = (u <= n ? 1 : sz_bcc[u]);

	for (auto v: tree[u])
	{
		if (v == p) continue;

		dfs(v, u);

		sub[u] += sub[v];
		dp[u] += dp[v];
	}

	if (u <= n) dp[u] = choose2(sub[u]);
}

void solve(int u, int p)
{
	for (auto v: tree[u])
		ans -= 2ll*(u <= n ? 1 : sz_bcc[u])*dp[v];

	for (auto v: tree[u])
	{
		if (v == p) continue;

		int old_sub_v = sub[v], old_sub_u = sub[u];
		ll old_dp_v = dp[v], old_dp_u = dp[u];

		if (u <= n)
		{
			int sz = sz_bcc[v];

			dp[u] = choose2(sub[u]-sub[v]);
			dp[v] += dp[u];
		}
		else
		{
			int sz = sz_bcc[u];

			dp[u] -= dp[v];
			dp[v] = choose2(sub[u]);
		}

		sub[v] = sub[u];
		sub[u] -= old_sub_v;

		solve(v, u);

		sub[v] = old_sub_v, sub[u] = old_sub_u;
		dp[v] = old_dp_v, dp[u] = old_dp_u; 
	}
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});

		edge[i] = {u, v};
	}

	for (int i = 1; i <= n; i++)
	{
		if (in[i]) continue;
		tt = 0;

		sz_comp = 0;

		int l = bcc.size();

		lowlink(i, 1);
		make_component(0);

		int r = bcc.size();

		ans += choose3(sz_comp);

		for (int j = l; j < r; j++)
		{
			vector<int> v;

			for (auto e: bcc[j])
			{
				v.push_back(edge[e].ff);
				v.push_back(edge[e].ss);
			}

			sort(all(v));
			v.erase(unique(all(v)), v.end());

			for (auto u: v)
			{
				if (art[u])
				{
					tree[n+j+1].push_back(u);
					tree[u].push_back(n+j+1);
				}
				else
				{
					sz_bcc[n+j+1]++;
				}
			}
		}
	}

	for (int i = 1; i <= 2*n; i++)
	{
		if (!vis[i] && tree[i].size())
		{
			dfs(i, 0);
			solve(i, 0);
		}
	}

	printf("%lld\n", ans);
}
