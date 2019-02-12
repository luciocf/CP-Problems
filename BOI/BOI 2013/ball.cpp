// BOI 2013 - Ball Machine
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxl = 20;

int n, cont;
int menor[maxn], order[maxn], pos[maxn];
int tree[4*maxn], lazy[4*maxn];
int tab[maxn][maxl], nivel[maxn];

vector<int> grafo[maxn];

bool comp(int a, int b) {return menor[a] < menor[b];}

int dfs(int u, int p)
{
	menor[u] = u;
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		tab[v][0] = u, nivel[v] = nivel[u]+1;
		menor[u] = min(menor[u], dfs(v, u));
	}

	return menor[u];
}

void dfs2(int u, int p)
{
	vector<int> child;

	for (auto v: grafo[u])
		if (v != p) child.push_back(v);

	sort(child.begin(), child.end(), comp);

	for (auto v: child)
		dfs2(v, u);

	pos[u] = ++cont;
	order[cont] = u;
}

void flush(int node, int l, int r)
{
	if (lazy[node] == -1) return;

	if (l != r) lazy[2*node] = lazy[2*node+1] = lazy[node];

	tree[node] = (r-l+1)*lazy[node], lazy[node] = -1;
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

	tree[node] = tree[2*node]+tree[2*node+1];
}

int query(int node, int l, int r, int pos)
{
	flush(node, l, r);

	if (l == r) return tree[node];

	int mid = (l+r)>>1;

	if (pos <= mid) return query(2*node, l, mid, pos);
	else return query(2*node+1, mid+1, r, pos);
}

int kth(int node, int l, int r, int k)
{
	flush(node, l, r);

	if (l == r) return l;

	int mid = (l+r)>>1;

	if (mid-l+1-tree[2*node] >= k) return kth(2*node, l, mid, k);
	return kth(2*node+1, mid+1, r, k-(mid-l+1-tree[2*node]));
}

void build(void)
{
	for (int j = 1; j < maxl; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	memset(lazy, -1, sizeof lazy);

	int q;
	cin >> n >> q;

	int root;
	for (int i = 1; i <= n; i++)
	{
		int p;
		cin >> p;

		if (!p) root = i;
		else grafo[i].push_back(p), grafo[p].push_back(i);
	}

	dfs(root, 0); dfs2(root, 0);

	build();

	while (q--)
	{
		int op;
		cin >> op;

		if (op == 1)
		{
			int k;
			cin >> k;

			int x = kth(1, 1, n, k);
			upd(1, 1, n, 1, x, 1);

			cout << order[x] << "\n";
		}
		else
		{
			int u;
			cin >> u;

			int x = u;
			for (int i = maxl-1; i >= 0; i--)
				if (tab[u][i] && query(1, 1, n, pos[tab[u][i]]) == 1)
					u = tab[u][i];

			upd(1, 1, n, pos[u], pos[u], 0);

			cout << nivel[x]-nivel[u] << "\n";
		}
	}
}
