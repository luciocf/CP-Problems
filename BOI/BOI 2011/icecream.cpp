// BOI 2011 - Ice Cream
// Lúcio Cardoso

// wtf?

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;

bool bad[maxn][maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		bad[u][v] = bad[v][u] = 1;
	}

	int ans = 0;

	for (int a = 1; a <= n; a++)
		for (int b = a+1; b <= n; b++)
			for (int c = b+1; c <= n; c++)
				if (!bad[a][b] && !bad[b][c] && !bad[c][a])
					ans++;

	printf("%d\n", ans);
}
