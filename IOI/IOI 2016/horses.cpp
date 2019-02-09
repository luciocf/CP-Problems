// IOI 2015 - Horses
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "horses.h"

using namespace std;

const int maxn = 5e5+10;

const int mod = 1e9+7;

typedef long long ll;

ll x[maxn], y[maxn];

int n;

struct node
{
	double maior, soma;
	ll maiorp, prod;
} tree[4*maxn];

void join(int node)
{
	tree[node].maior = max(tree[2*node].maior, tree[2*node].soma+tree[2*node+1].maior);
	tree[node].soma = tree[2*node].soma+tree[2*node+1].soma;

	if (tree[2*node].maior > tree[2*node].soma+tree[2*node+1].maior)
		tree[node].maiorp = tree[2*node].maiorp;
	else 
		tree[node].maiorp = (tree[2*node].prod*tree[2*node+1].maiorp)%mod;

	tree[node].prod = (tree[2*node].prod*tree[2*node+1].prod)%mod;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].maior = log2(x[l])+log2(y[l]);
		tree[node].soma = log2(x[l]);

		tree[node].maiorp = (x[l]*y[l])%mod;
		tree[node].prod = x[l]%mod;

		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);
	join(node);
}

void upd(int node, int l, int r, int pos)
{
	if (l == r)
	{
		tree[node].maior = log2(x[l])+log2(y[l]);
		tree[node].soma = log2(x[l]);

		tree[node].maiorp = (x[l]*y[l])%mod;
		tree[node].prod = x[l]%mod;	

		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos);
	else upd(2*node+1, mid+1, r, pos);

	join(node);
}

int init(int N, int X[], int Y[])
{
	n = N;
	for (int i = 0; i < n; i++)
		x[i] = (ll)X[i], y[i] = (ll)Y[i];
	build(1, 0, n-1);

	return (int)tree[1].maiorp;
}

int updateX(int pos, int val)
{
	x[pos] = (ll)val;
	upd(1, 0, n-1, pos);

	return (int)tree[1].maiorp;
}

int updateY(int pos, int val)
{
	y[pos] = (ll)val;
	upd(1, 0, n-1, pos);

	return (int)tree[1].maiorp;
}
