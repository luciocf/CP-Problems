// COCI 2015/2016 - Nekameleoni
// Lúcio Cardoso

// Solution is the same as this one: http://hsin.hr/coci/archive/2015_2016/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxk = 55;

int n, k;

int a[maxn];
int tree[3*maxn];

int posPref[maxk][3*maxn], posSuf[maxk][3*maxn];
int prefSz[3*maxn], sufSz[3*maxn];
long long maskPref[maxk][3*maxn], maskSuf[maxk][3*maxn];

void updMin(int node, int l, int r)
{
	int ptr = 1;

	for (int i = sufSz[2*node]; i <= k; i++)
	{
		while (ptr <= prefSz[2*node+1] && (maskSuf[i][2*node] | maskPref[ptr][2*node+1]) != (1ll<<k)-1)
			ptr++;

		if (ptr <= prefSz[2*node+1] && (maskSuf[i][2*node] | maskPref[ptr][2*node+1]) == (1ll<<k)-1)
			tree[node] = min(tree[node], posPref[ptr][2*node+1]-posSuf[i][2*node]+1);
	}
}

void updMaskPref(int node, int l, int r)
{
	int j = 1;
	for (int i = 1; i <= prefSz[2*node]; i++)
	{
		maskPref[j][node] = maskPref[i][2*node];
		posPref[j][node] = posPref[i][2*node];

		++j;
	}

	for (int i = 1; i <= prefSz[2*node+1]; i++)
	{
		if ((maskPref[j-1][node] & maskPref[i][2*node+1]) != maskPref[i][2*node+1])
		{
			maskPref[j][node] = maskPref[j-1][node] | maskPref[i][2*node+1];
			posPref[j][node] = posPref[i][2*node+1];

			++j;
		}
	}

	prefSz[node] = j-1;
}

void updMaskSuf(int node, int l, int r)
{
	int j = k;
	for (int i = k; i >= sufSz[2*node+1]; i--)
	{
		maskSuf[j][node] = maskSuf[i][2*node+1];
		posSuf[j][node] = posSuf[i][2*node+1];

		--j;
	}

	for (int i = k; i >= sufSz[2*node]; i--)
	{
		if ((maskSuf[j+1][node] & maskSuf[i][2*node]) != maskSuf[i][2*node])
		{
			maskSuf[j][node] = maskSuf[j+1][node] | maskSuf[i][2*node];
			posSuf[j][node] = posSuf[i][2*node];

			--j;
		}
	}

	sufSz[node] = j+1;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		prefSz[node] = 1, sufSz[node] = k;

		maskPref[1][node] = maskSuf[k][node] = 1ll<<a[l];
		posPref[1][node] = posSuf[k][node] = l;

		if (k == 1) tree[node] = 1;
		else tree[node] = n+1;

		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = min(tree[2*node], tree[2*node+1]);
	updMin(node, l, r);

	updMaskPref(node, l, r); updMaskSuf(node, l, r);
}

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		maskPref[1][node] = maskSuf[k][node] = 1ll<<v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node] = min(tree[2*node], tree[2*node+1]);
	updMin(node, l, r);

	updMaskPref(node, l, r); updMaskSuf(node, l, r);
}

int main(void)
{
	int m;
	scanf("%d %d %d", &n, &k, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		--a[i];
	}

	build(1, 1, n);

	for (int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int pos, v;
			scanf("%d %d", &pos, &v);
			--v;

			upd(1, 1, n, pos, v);
		}
		else
		{
			if (tree[1] == n+1) printf("-1\n");
			else printf("%d\n", tree[1]);
		}
	}
}
