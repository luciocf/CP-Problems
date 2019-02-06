// IOI 2013 - Cave
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "cave.h"

using namespace std;

const int maxn = 5e3+10;

int pos[maxn], n;
int s[maxn], d[maxn];

bool mark[maxn];

int get(void)
{
	return tryCombination(pos);
}

void reverse(int l, int r)
{
	for (int i = l; i <= r; i++)
		if (!mark[i])
			pos[i] = !pos[i];
}

void solve(int l, int r, int atual, int x)
{
	if (l == r)
	{	
		d[l] = x;
		if (atual == x) s[l] = !pos[l], pos[l] = !pos[l];
		else s[l] = pos[l];

		mark[l] = 1;

		return;
	}

	int mid = (l+r)>>1;

	reverse(l, mid);

	int g = get();

	if ( (atual == x && g != x) || (atual != x && g == x)) solve(l, mid, g, x);
	else solve(mid+1, r, g, x);
}

void exploreCave(int N)
{
	n = N;

	for (int i = 0; i < n; i++)
		pos[i] = mark[i] = 0;

	for (int i = 0; i < n; i++)
	{
		int atual = get();
		solve(0, n-1, atual, i);
	}

	answer(s, d);
}
