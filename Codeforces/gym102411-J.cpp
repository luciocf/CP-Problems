// ICPC 2019-2020 North-Western Russia Regional Contest - J - Just the Last Digit
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;

int qtd[maxn][maxn], aux[maxn][maxn], ans[maxn][maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			char c;
			scanf(" %c", &c);

			qtd[i][j] = (int)(c-'0');
		}
	}

	for (int i = n; i >= 1; i--)
	{
		for (int j = i+1; j <= n; j++)
		{
			if (aux[i][j] != qtd[i][j])
			{
				ans[i][j] = 1;

				for (int l = j+1; l <= n; l++)
					aux[i][l] = (aux[i][l] + qtd[j][l])%10;
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%d", ans[i][j]);
		printf("\n");
	}
}
