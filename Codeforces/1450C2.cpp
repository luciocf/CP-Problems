// Codeforces 1450C2 - Errich-Tac-Toe (Hard Version)
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;

int n;
char a[maxn][maxn];

int q[2][3];

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		scanf("%d", &n);

		memset(q, 0, sizeof q);

		int tot = 0;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				scanf(" %c", &a[i][j]);
				
				if (a[i][j] == 'X') q[0][(i+j-2)%3]++, tot++;
				if (a[i][j] == 'O') q[1][(i+j-2)%3]++, tot++;
			}
		}

		int id_0, id_1;

		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				if (i == j) continue;

				if ((q[0][i]+q[1][j]) <= tot/3)
					id_0 = i, id_1 = j;
			}
		}

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if ((i+j-2)%3 == id_0 && a[i][j] == 'X')
					a[i][j] = 'O';

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if ((i+j-2)%3 == id_1 && a[i][j] == 'O')
					a[i][j] = 'X';

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				printf("%c", a[i][j]);
			printf("\n");
		}
	}
}
