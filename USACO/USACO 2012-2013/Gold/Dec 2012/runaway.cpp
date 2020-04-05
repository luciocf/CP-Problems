// USACO 2012/2013 - Running Away From the Barn
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, ll> pii;

const int maxn = 2e5+10;

ll dist[maxn];

int st[maxn], en[maxn], back[maxn], tt;

vector<pii> grafo[maxn];

vector<ll> tree[4*maxn];

void dfs(int u, int p)
{
	st[u] = ++tt, back[tt] = u;

	for (auto v: grafo[u])
	{
		if (v.first != p)
		{
			dist[v.first] = dist[u]+v.second;
			dfs(v.first, u);
		}
	}

	en[u] = tt;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].push_back(dist[back[l]]);
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), back_inserter(tree[node]));
}

int query(int node, int l, int r, int a, int b, ll v)
{
	if (l > b || r < a) return 0;

	if (l >= a && r <= b)
	{
		auto it = upper_bound(tree[node].begin(), tree[node].end(), v);
		return (int)(it-tree[node].begin());
	}

	int mid = (l+r)>>1;

	return (query(2*node, l, mid, a, b, v)+query(2*node+1, mid+1, r, a, b, v));
}

int main(void)
{
	freopen("runaway.in", "r", stdin); freopen("runaway.out", "w", stdout);

	int n;
	ll L;
	scanf("%d %lld", &n, &L);

	for (int i = 2; i <= n; i++)
	{
		int p;
		ll d;
		scanf("%d %lld", &p, &d);

		grafo[p].push_back({i, d}); grafo[i].push_back({p, d});
	}

	dfs(1, 0);
	build(1, 1, n);

	for (int i = 1; i <= n; i++)
		printf("%d\n", query(1, 1, n, st[i], en[i], dist[i]+L));
}
