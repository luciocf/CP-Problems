// Seletiva IOI 2017 - Cabo de Guerra
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;
const int maxs = 2510;

int n;
int a[maxn];

bool dp[maxn][maxs];

int main(void)
{
	scanf("%d", &n);

	int soma = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		soma += a[i];
	}

	dp[0][0] = 1;

	for (int i = 1; i <= n; i++)
		for (int k = n; k >= 1; k--)
			for (int j = maxs-1; j >= a[i]; j--)
				dp[k][j] |= dp[k-1][j-a[i]];

	for (int i = soma/2; i >= 1; i--)
	{
		if (dp[n/2][i])
		{
			printf("%d\n", soma-2*i);
			return 0;
		}
	}
}
