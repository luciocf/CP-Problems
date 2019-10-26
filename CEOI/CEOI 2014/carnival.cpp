// CEOI 2014 - Carnival
// Lúcio Cardoso

// The color of an index is the smallest color C such that query(ind[1], ind[2], ..., ind[C])
// is equal to C-1, where ind[i] is an index with color already found. So we can binary search on that.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 155;

int ans[maxn];
int ind[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	int c = 1;
	ans[1] = 1, ind[1] = 1;

	for (int i = 2; i <= n; i++)
	{
		int ini = 1, fim = c, cor = c+1;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			printf("%d", mid+1);
			for (int j = 1; j <= mid; j++)
				printf(" %d", ind[j]);
			printf(" %d\n", i);
			fflush(stdout);

			int res;
			scanf("%d", &res);

			if (res == mid) cor = mid, fim = mid-1;
			else ini = mid+1;
		}

		c = max(c, cor);
		ans[i] = cor, ind[cor] = i;
	}

	printf("0");
	for (int i = 1; i <= n; i++)
		printf(" %d", ans[i]);
	printf("\n");
	fflush(stdout);
}
