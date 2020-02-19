// IZhO 2019 - Red-Blue Table
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+10;

pii linha[maxn];

char tab[maxn][maxn];

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);

		int mx = n, opt = 0;

		for (int B = 0; B <= m; B++)
		{
			int need = (m+2)/2 - (m-B);
			int qtd = B;

			if (need == 0) qtd += n;
			else
			{
				int x = (n - ((n+2)/2))*B;
				qtd += min(n, x/need);
			}

			if (qtd > mx)
				mx = qtd, opt = B;
		}

		for (int i = 1; i <= n; i++)
			linha[i] = {0, i};

		printf("%d\n", mx);

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				tab[i][j] = '-';

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m-opt; j++)
				tab[i][j] = '+';

		for (int j = m-opt+1; j <= m; j++)
		{
			sort(linha+1, linha+mx-opt+1);

			for (int k = 1; k <= n - ((n+2)/2); k++)
			{
				tab[linha[k].second][j] = '+';
				linha[k].first++;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				printf("%c", tab[i][j]);

			printf("\n");
		}
	}
}
