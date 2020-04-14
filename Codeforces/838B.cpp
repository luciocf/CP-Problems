// Codeforces 838B - Diverging Directions
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 4e5+10;
const ll inf = 1e18+10;

struct Edge
{
	int u, v, w;
	bool tipo;
} edge[maxn];

int n;
int back[maxn];

int st[maxn], en[maxn], tt;

ll tree[4*maxn], lazy[4*maxn];

vector<pii> grafo[maxn];

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node]; 
	}

	tree[node] += lazy[node];
	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] = 1ll*v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

void dfs(int u, int p, ll d)
{
	st[u] = ++tt;

	upd(1, 1, n, st[u], st[u], d+1ll*back[u]);

	for (auto e: grafo[u])
	{
		int v = e.first, w = e.second;
		if (v == p) continue;

		dfs(v, u, d+1ll*w);
	}

	en[u] = tt;
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});

		edge[i] = {u, v, w, 0};
	}

	for (int i = n; i <= 2*n-2; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		scanf("%d", &back[u]);

		edge[i] = {u, v, back[u], 1};
	}

	dfs(1, 0, 0);

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int i, w;
			scanf("%d %d", &i, &w);

			if (edge[i].tipo)
			{
				int u = edge[i].u;

				upd(1, 1, n, st[u], st[u], -back[u]);

				back[u] = w;

				upd(1, 1, n, st[u], st[u], back[u]);
			}
			else
			{
				int v = edge[i].v;

				upd(1, 1, n, st[v], en[v], -edge[i].w);

				edge[i].w = w;

				upd(1, 1, n, st[v], en[v], edge[i].w);
			}
		}
		else
		{
			int u, v;
			scanf("%d %d", &u, &v);

			if (st[v] >= st[u] && en[v] <= en[u])
			{
				ll nv = query(1, 1, n, st[v], st[v]) - 1ll*back[v];
				ll nu = query(1, 1, n, st[u], st[u]) - 1ll*back[u];

				printf("%lld\n", nv-nu);
			}
			else
			{
				ll mn = query(1, 1, n, st[u], en[u]) - (query(1, 1, n, st[u], st[u]) - 1ll*back[u]);
				printf("%lld\n", mn + query(1, 1, n, st[v], st[v]) - 1ll*back[v]);
			}
		}
	}
}
