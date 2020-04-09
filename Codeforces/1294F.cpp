// Codeforces 1294F - Three Paths on a Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 2e5+10;

typedef pair<int, int> pii;

int n, ans;
int A, B, C;

int st[maxn], en[maxn], back[maxn], tt;
int m1[maxn], m2[maxn], m3[maxn];
int c1[maxn], c2[maxn], c3[maxn];

pii tree[4*maxn];
int lazy[4*maxn];

vector<int> grafo[maxn];

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node].ff += lazy[node];
	lazy[node] = 0;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = {0, l};
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = tree[2*node];
}

void upd(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void dfs(int u, int p, int d)
{
	st[u] = ++tt, back[tt] = u;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u, d+1);

		if (1+m1[v] > m1[u])
		{
			m3[u] = m2[u];
			m2[u] = m1[u];
			m1[u] = 1+m1[v];
		}
		else if (1+m1[v] > m2[u])
		{
			m3[u] = m2[u];
			m2[u] = 1+m1[v];
		}
		else if (1+m1[v] > m3[u])
		{
			m3[u] = 1+m1[v];
		}
	}

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		if (1+m1[v] == m1[u] && !c1[u]) c1[u] = c1[v];
		else if (1+m1[v] == m2[u] && !c2[u]) c2[u] = c1[v];
		else if (1+m1[v] == m3[u] && !c3[u]) c3[u] = c1[v];
	}

	if (!c1[u]) c1[u] = u;

	upd(1, 1, n, st[u], st[u], m1[u]+m2[u]+d);

	en[u] = tt;
}

void solve(int u, int p)
{
	flush(1, 1, n);
	
	if (tree[1].ff > ans)
		A = u, B = c1[back[tree[1].ss]], C = c2[back[tree[1].ss]], ans = tree[1].ff;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		int old_m_u[3], old_m_v[3], old_c_u[3], old_c_v[3];

		old_m_u[0] = m1[u], old_m_u[1] = m2[u], old_m_u[2] = m3[u];
		old_m_v[0] = m1[v], old_m_v[1] = m2[v], old_m_v[2] = m3[v];
		old_c_u[0] = c1[u], old_c_u[1] = c2[u], old_c_u[2] = c3[u];
		old_c_v[0] = c1[v], old_c_v[1] = c2[v], old_c_v[2] = c3[v];

		upd(1, 1, n, st[u], st[u], -m1[u]-m2[u]);
		upd(1, 1, n, st[v], st[v], -m1[v]-m2[v]-1);

		if (1+m1[v] == m1[u])
		{
			m1[u] = m2[u], c1[u] = c2[u];
			m2[u] = m3[u], c2[u] = c3[u];
		}
		else if (1+m1[v] == m2[u])
		{
			m2[u] = m3[u], c2[u] = c3[u];
		}

		upd(1, 1, n, st[u], st[u], m1[u]+m2[u]);

		if (m1[u]+1 > m1[v])
		{
			m3[v] = m2[v], c3[v] = c2[v];
			m2[v] = m1[v], c2[v] = c1[v];
			m1[v] = m1[u]+1, c1[v] = c1[u];
		}
		else if (m1[u]+1 > m2[v])
		{
			m3[v] = m2[v], c3[v] = c2[v];
			m2[v] = m1[u]+1, c2[v] = c1[u];
		}
		else if (m1[u]+1 > m3[v])
		{
			m3[v] = m1[u]+1, c3[v] = c1[u];
		}

		upd(1, 1, n, st[v], st[v], m1[v]+m2[v]+1);

		upd(1, 1, n, 1, n, 1);
		upd(1, 1, n, st[v], en[v], -2);

		solve(v, u);

		upd(1, 1, n, 1, n, -1);
		upd(1, 1, n, st[v], en[v], 2);

		upd(1, 1, n, st[u], st[u], -(m1[u]+m2[u]));
		upd(1, 1, n, st[v], st[v], -(m1[v]+m2[v]+1));

		m1[u] = old_m_u[0], m2[u] = old_m_u[1], m3[u] = old_m_u[2];
		c1[u] = old_c_u[0], c2[u] = old_c_u[1], c3[u] = old_c_u[2];
		m1[v] = old_m_v[0], m2[v] = old_m_v[1], m3[v] = old_m_v[2];
		c1[v] = old_c_v[0], c2[v] = old_c_v[1], c3[v] = old_c_v[2];

		upd(1, 1, n, st[u], st[u], m1[u]+m2[u]);
		upd(1, 1, n, st[v], st[v], m1[v]+m2[v]+1);
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	build(1, 1, n);

	dfs(1, 0, 0); solve(1, 0);

	if (A == B)
	{
		for (int i = 1; i <= n; i++)
			if (i != A && i != C)
				B = i;
	}

	if (B == C || !C)
	{
		for (int i = 1; i <= n; i++)
			if (i != A && i != B)
				C = i;
	}

	printf("%d\n%d %d %d\n", ans, A, B, C);
}
