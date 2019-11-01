// Seletiva IOI 2018 - Marcos Soluções Tecnológicas
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxm = 3e5+10;

typedef long long ll;

struct aresta
{
	int u, v, w;
} edge[maxm];

struct node
{
	ll soma;
	int qtd;
} tree[4*maxn];

int n;
int pai[maxn], peso[maxn];

int gadget[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

bool comp(aresta a, aresta b) {return a.w < b.w;}

void upd(int node, int l, int r, int pos, int x)
{
	if (l == r)
	{
		tree[node].qtd += x;
		tree[node].soma += 1ll*x*pos;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, x);
	else upd(2*node+1, mid+1, r, pos, x);

	tree[node].soma = tree[2*node].soma+tree[2*node+1].soma;
	tree[node].qtd = tree[2*node].qtd+tree[2*node+1].qtd;
}

ll query(int node, int l, int r, int k)
{
	if (k == 0) return 0;
	if (l == r) return 1ll*k*l;

	int mid = (l+r)>>1;

	if (tree[2*node].qtd >= k) return query(2*node, l, mid, k);

	return (tree[2*node].soma + query(2*node+1, mid+1, r, k-tree[2*node].qtd));
}

int main(void)
{
	int m, k, q;
	scanf("%d %d %d %d", &n, &m, &k, &q);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		edge[i] = {u, v, w}; 
	}

	for (int i = 1; i <= k; i++)
	{
		scanf("%d", &gadget[i]);
		upd(1, 1, maxn-1, gadget[i], 1);
	}


	init();
	sort(edge+1, edge+m+1, comp);

	for (int i = 1; i <= m; i++)
	{
		if (Find(edge[i].u) != Find(edge[i].v))
		{
			upd(1, 1, maxn-1, edge[i].w, 1);
			Join(edge[i].u, edge[i].v);
		}
	}

	printf("%lld\n", query(1, 1, maxn-1, n-1));

	for (int i = 1; i <= q; i++)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int x;
			scanf("%d", &x);

			upd(1, 1, maxn-1, x, 1);
			printf("%lld\n", query(1, 1, maxn-1, n-1));
		}
		else
		{
			int x;
			scanf("%d", &x);

			upd(1, 1, maxn-1, x, -1);
			printf("%lld\n", query(1, 1, maxn-1, n-1));
		}
	}
}
