#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;
const int bucket = 400;

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(int n)
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
} dsu[2];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	dsu[0].init(n);
	dsu[1].init(n);

	while (m--)
	{
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);

		for (int i = a, j = b; i < a+l; i += bucket, j += bucket)
		{
			if (i+bucket-1 < a+l)
			{
				if (dsu[1].Find(i) == dsu[1].Find(j)) continue;

				dsu[1].Join(i, j);
			}

			for (int k = 0; k < bucket && i+k < a+l; k++)
				dsu[0].Join(i+k, j+k);
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (dsu[0].Find(i) == i)
			ans++;

	printf("%d\n", ans);
}
