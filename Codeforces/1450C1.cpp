// Codeforces 1450C1 - Errich-Tac-Toe (Easy Version)
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;

int n;
char a[maxn][maxn];

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		scanf("%d", &n);

		int q[] = {0, 0, 0};

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				scanf(" %c", &a[i][j]);
				
				if (a[i][j] == 'X') q[(i+j-2)%3]++;
			}
		}

		if (min({q[0], q[1], q[2]}) == q[0])
		{
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if ((i+j-2)%3 == 0 && a[i][j] == 'X')
						a[i][j] = 'O';
		}
		else if (min({q[0], q[1], q[2]}) == q[1])
		{
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if ((i+j-2)%3 == 1 && a[i][j] == 'X')
						a[i][j] = 'O';
		}
		else
		{
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if ((i+j-2)%3 == 2 && a[i][j] == 'X')
						a[i][j] = 'O';
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				printf("%c", a[i][j]);
			printf("\n");
		}
	}
}
