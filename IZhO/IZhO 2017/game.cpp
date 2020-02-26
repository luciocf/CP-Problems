// IZhO 2017 - Simple Game
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int n, m;
int a[maxn];

int bit[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

void range_upd(int l, int r, int x)
{
	upd(l, x);
	upd(r+1, -x);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		if (a[i] <= a[i+1])
			range_upd(a[i], a[i+1]-1, 1);
		else
			range_upd(a[i+1]+1, a[i], 1);
	}

	for (int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int pos, v;
			scanf("%d %d", &pos, &v);

			if (pos != 1)
			{
				if (a[pos-1] <= a[pos])
					range_upd(a[pos-1], a[pos]-1, -1);
				else
					range_upd(a[pos]+1, a[pos-1], -1);

				if (a[pos-1] <= v)
					range_upd(a[pos-1], v-1, 1);
				else
					range_upd(v+1, a[pos-1], 1);
			}

			if (pos != n)
			{
				if (a[pos] <= a[pos+1])
					range_upd(a[pos], a[pos+1]-1, -1);
				else
					range_upd(a[pos+1]+1, a[pos], -1);

				if (v <= a[pos+1])
					range_upd(v, a[pos+1]-1, 1);
				else
					range_upd(a[pos+1]+1, v, 1);
			}

			a[pos] = v;
		}
		else
		{
			int H;
			scanf("%d", &H);

			printf("%d\n", (H == a[n] ? soma(H)+1 : soma(H)));
		}
	}
}
