// JOI Open Contest 2014 - Secret
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "secret.h"

using namespace std;

const int maxn = 1e3+10;

int n, num[maxn];
int suf[4*maxn][maxn], pref[4*maxn][maxn];

int get(int x, int y)
{
	return Secret(x, y);
}

void build(int node, int l, int r)
{
	if (l == r || r == l+1) return;

	int mid = (l+r)>>1;

	suf[node][mid-1] = get(num[mid-1], num[mid]);
	for (int i = mid-2; i >= l; i--)
		suf[node][i] = get(num[i], suf[node][i+1]);

	pref[node][mid+1] = num[mid+1];
	for (int i = mid+2; i <= r; i++)
		pref[node][i] = get(pref[node][i-1], num[i]);

	build(2*node, l, mid); build(2*node+1, mid+1, r);
}

int query(int node, int l, int r, int a, int b)
{
	if (r == l+1) return get(num[l], num[r]);

	int mid = (l+r)>>1;

	if (b < mid) return query(2*node, l, mid, a, b);
	else if (a > mid) return query(2*node+1, mid+1, r, a, b);
	else if (a == mid) return get(num[mid], pref[node][b]);
	else if (b == mid) return suf[node][a];
	return get(suf[node][a], pref[node][b]);
}

void Init(int N, int A[])
{
	n = N;
	for (int i = 1; i <= n; i++)
		num[i] = A[i-1];

	build(1, 1, n);
}

int Query(int L, int R)
{
	if (L == R) return num[L+1];

	return query(1, 1, n, L+1, R+1);
}
