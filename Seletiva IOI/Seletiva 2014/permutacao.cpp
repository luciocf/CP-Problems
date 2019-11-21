// Seletiva IOI 2014 - Permutação
// Lúcio Cardoso

#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+1;

int n;

int a[maxn], b[maxn];

int ord[maxn], ans[maxn];

int pos[maxn];

int bit[maxn][2];

void upd(int x, int q, int v)
{
	for (; x <= n; x += (x&-x))
		bit[x][q] += v;
}

int busca_pref(int q)
{
	int s = 0, pos = 0;

	for (int i = 19; i >= 0; i--)
		if (pos + (1<<i) <= n && s + bit[pos+(1<<i)][q] == pos+(1<<i))
			s += bit[pos+(1<<i)][q], pos += (1<<i);

	return pos;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pos[a[i]] = i;
	}

	if (n == 1)
	{
		printf("1\n");
		return 0;
	}

	for (int i = 1; i < n; i++)
		scanf("%d", &b[i]);

	for (int i = 1; i < n; i++)
		if (a[i] == b[i])
			upd(i, 0, 1);

	for (int i = n; i > 1; i--)
		if (a[i] == b[i-1])
			upd(n-i+1, 1, 1);

	for (int i = n; i >= 1; i--)
		ord[n-i+1] = pos[i];

	int tot = 0;

	for (int i = 1; i <= n; i++)
	{
		int p = ord[i];

		int v = a[p];

		if (p != pos[n])
		{
			if (a[pos[v+1]] == b[pos[v+1]])
				upd(pos[v+1], 0, -1);
			else if (a[pos[v+1]]-1 == b[pos[v+1]])
				upd(pos[v+1], 0, 1);

			if (pos[v+1] != 1)
			{
				if (a[pos[v+1]] == b[pos[v+1]-1])
					upd(n-pos[v+1]+1, 1, -1);
				else if (a[pos[v+1]]-1 == b[pos[v+1]-1])
					upd(n-pos[v+1]+1, 1, 1);
			}
		}

		int ate_pref = busca_pref(0);

		if (ate_pref < p-1) continue;

		int ate_suf = busca_pref(1);

		if (n-ate_suf+1 <= p+1)
			ans[++tot] = a[p];
	}


	if (tot > 0)
	{
		printf("%d", ans[tot]);
		for (int i = tot-1; i >= 1; i--)
			printf(" %d", ans[i]);
		printf("\n");
	}
}
