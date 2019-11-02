// Seletiva IOI 2018 - Empresa
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int val[maxn];

int in[maxn], out[maxn], tt;

vector<int> grafo[maxn], nivel[maxn];

int tree[4*maxn];

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node] = v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

void dfs(int u, int p, int d)
{	
	nivel[d].push_back(u);
	in[u] = ++tt;

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u, d+1);

	out[u] = tt;
}

bool comp(int a, int b) {return val[a] < val[b];}

int main(void)
{
	scanf("%d", &n);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		grafo[i].push_back(p);
		grafo[p].push_back(i);
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);

	dfs(1, 0, 1);

	for (int i = 1; i <= n; i++)
		sort(nivel[i].begin(), nivel[i].end(), comp);

	long long ans = 0;

	for (int i = n; i >= 1; i--)
	{
		int ant = 0;

		for (auto u: nivel[i])
		{
			int at = max(ant, query(1, 1, n, in[u], out[u]))+1;

			ans += 1ll*at, ant = at;
			upd(1, 1, n, in[u], at);
		}
	}

	printf("%lld\n", ans);
}
