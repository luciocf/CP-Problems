// Codeforces 1311E - Construct the Binary Tree
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;

int l[maxn], r[maxn], p[maxn];
int nivel[maxn];

bool mark[maxn];

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n, d;
		scanf("%d %d", &n, &d);

		for (int i = 1; i <= n; i++)
			mark[i] = 0;

		if (d > n*(n-1)/2)
		{
			printf("NO\n");
			continue;
		}

		int mn = 0;

		int j = 1;

		for (int i = 1; i <= 14; i++)
		{
			mn += i*min(n-j, (1<<i));

			if (n-j <= (1<<i)) break;
			
			j += (1<<i);
		}

		if (d < mn)
		{
			printf("NO\n");
			continue;
		}

		p[1] = 0;

		for (int i = 1; i < n; i++)
		{
			l[i] = i+1, r[i] = -1;
			p[i+1] = i, nivel[i] = i-1;
		}

		l[n] = r[n] = -1;
		nivel[n] = n-1;

		int soma = n*(n-1)/2;

		while (soma > d)
		{
			int mn = n+1;
			int u = -1, v = -1;

			for (int i = 1; i <= n; i++)
				if (l[i] == -1 && r[i] == -1 && !mark[i] && nivel[i] < mn)
					u = i, mn = nivel[i];

			if (u == -1) break;

			for (int i = 1; i <= n; i++)
				if (nivel[i] == nivel[u]-2 && (l[i] == -1 || r[i] == -1))
					v = i;

			if (v == -1)
			{
				mark[u] = 1;
				continue;
			}

			soma--;

			if (l[p[u]] == u) l[p[u]] = -1;
			else r[p[u]] = -1;

			nivel[u]--;

			if (l[v] == -1) l[v] = u;
			else r[v] = u;

			p[u] = v;
		}

		printf("YES\n");

		for (int i = 2; i <= n; i++)
			printf("%d ", p[i]);
		printf("\n");
	}
}
