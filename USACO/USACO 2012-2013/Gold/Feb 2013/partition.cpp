// USACO 2012/2013 - Partitioning the Farm
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 30;

int n, k;

int a[maxn][maxn];

int qtd[maxn];

bool ok(int mask, int x, int p)
{
	int tot = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			qtd[j] = 0;

		int j;

		for (j = i; j <= n; j++)
		{
			int ind = 1;

			for (int l = 1; l <= n; l++)
			{
				qtd[ind] += a[j][l];

				if (mask&(1<<(l-1))) ind++;
			}

			bool fim = 0;
			for (int l = 1; l <= ind; l++)
				if (qtd[l] > x)
					fim = 1;

			if (fim) break;
		}

		if (j == i) return false;

		i = j-1;
		if (j != n+1) tot++;
	}

	return (tot <= p);
}

int main(void)
{
	freopen("partition.in", "r", stdin); freopen("partition.out", "w", stdout);

	scanf("%d %d", &n, &k);
		
	int soma = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]), soma += a[i][j];

	int ans = soma;

	for (int mask = 0; mask < (1<<(n-1)); mask++)
	{
		int p = k-__builtin_popcount(mask);
		if (p < 0) continue;

		int ini = 0, fim = soma, mn = soma;

		while (ini <= fim)
		{
			int mid = (ini+fim)/2;

			if (ok(mask, mid, p)) mn = mid, fim = mid-1;
			else ini = mid+1;
		}

		ans = min(ans, mn);
	}

	printf("%d\n", ans);
}
