// Codeforces 1361A - Johnny and Contribution
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int a[maxn];
int p[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

bool comp(int c, int d) {return a[c] < a[d];}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	vector<int> V;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		V.push_back(i);
	}

	for (int i = 1; i <= n; i++)
	{
		for (auto v: grafo[i])
		{
			if (a[i] == a[v])
			{
				printf("-1\n");
				return 0;
			}
		}
	}

	sort(V.begin(), V.end(), comp);

	for (auto u: V)
	{
		for (auto v: grafo[u])
			if (p[v])
				mark[p[v]] = 1;

		int c = 1;
		while (mark[c]) c++;

		p[u] = c;

		for (auto v: grafo[u])
			mark[p[v]] = 0;
	}	

	for (int i = 1; i <= n; i++)
	{
		if (p[i] != a[i])
		{
			printf("-1\n");
			return 0;
		}
	}

	for (int i = 0; i < n; i++)
		printf("%d ", V[i]);
	printf("\n");
}
