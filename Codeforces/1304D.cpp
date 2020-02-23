// Codeforces 1304D - Shortest and Longest LIS
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

char a[maxn];

int ans1[maxn], ans2[maxn];

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i < n; i++)
			scanf(" %c", &a[i]);

		int at = n;

		a[n] = '>';
		for (int i = 1; i <= n; i++)
		{
			if (a[i] == '>')
			{
				ans1[i] = at--;

				for (int j = i-1; j >= 1 && a[j] != '>'; j--)
					ans1[j] = at--;
			}
		}

		at = 1;

		a[n] = '<';
		for (int i = 1; i <= n; i++)
		{
			if (a[i] == '<')
			{
				ans2[i] = at++;

				for (int j = i-1; j >= 1 && a[j] != '<'; j--)
					ans2[j] = at++;
			}
		}

		for (int i = 1; i <= n; i++)
			printf("%d ", ans1[i]);
		printf("\n");

		for (int i = 1; i <= n; i++)
			printf("%d ", ans2[i]);
		printf("\n");
	}
}
