// CEOI 2014 - Cake
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int n;
int a[maxn];

pair<int, int> aux[maxn];

int tree[4*maxn];

vector<pair<int, int>> mx;

void faz(void)
{
	sort(aux+1, aux+n+1);

	for (int i = max(1, n-12); i <= n; i++)
		mx.push_back({a[aux[i].second], aux[i].second});
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = a[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

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
	if (l > b || r < a) return -1;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

int findL(int node, int l, int r, int pos, int v)
{
	if (l > pos || tree[node] <= v) return -1;
	if (l == r) return l;

	int mid = (l+r)>>1;

	int p1 = findL(2*node+1, mid+1, r, pos, v);
	return (p1 == -1 ? findL(2*node, l, mid, pos, v) : p1);
}

int findR(int node, int l, int r, int pos, int v)
{
	if (r < pos || tree[node] <= v) return -1;
	if (l == r) return l;

	int mid = (l+r)>>1;

	int p1 = findR(2*node, l, mid, pos, v);
	return (p1 == -1 ? findR(2*node+1, mid+1, r, pos, v) : p1);
}

int main(void)
{
	int A;
	scanf("%d %d", &n, &A);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		aux[i] = {a[i], i};
	}

	faz();

	build(1, 1, n);

	int q;
	scanf("%d", &q);

	for (int t = 1; t <= q; t++)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'E')
		{
			int ind, e;
			scanf("%d %d", &ind, &e);

			vector<pair<int, int>> aux;

			int qtd = 0;

			for (int i = mx.size()-1; i > mx.size()-e; i--, qtd++)
				aux.push_back(mx[i]);

			aux.push_back({a[ind], ind}), ++qtd;

			for (int i = mx.size()-e; i >= 0 && qtd < 13; i--, qtd++)
				if (mx[i].second != ind)
					aux.push_back(mx[i]);

			mx.clear();

			for (int i = aux.size()-1; i >= 0; i--)
				mx.push_back(aux[i]);

			for (int i = 1; i < mx.size(); i++)
			{
				if (mx[i].first <= mx[i-1].first)
				{
					a[mx[i].second] = mx[i-1].first+1;
					mx[i].first = mx[i-1].first+1;
				}
			}

			for (int i = 0; i < mx.size(); i++)
			{
				a[mx[i].second] = mx[i].first;
				upd(1, 1, n, mx[i].second, mx[i].first);
			}
		}
		else
		{
			int ind;
			scanf("%d", &ind);

			if (ind == A) printf("0\n");
			else if (ind < A)
			{
				int M = query(1, 1, n, ind, A-1);
				int last = findR(1, 1, n, A+1, M);

				if (last == -1)
					printf("%d\n", n-ind);
				else
					printf("%d\n", last-ind-1);
			}
			else
			{
				int M = query(1, 1, n, A+1, ind);
				int last = findL(1, 1, n, A-1, M);

				if (last == -1)
					printf("%d\n", ind-1);
				else
					printf("%d\n", ind-last-1);
			}
		}
	}
}
