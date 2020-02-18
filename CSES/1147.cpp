// CSES 1147 - Maximum Building I
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+10;

int n, m;
char tab[maxn][maxn];

int up[maxn][maxn];
int l[maxn][maxn], r[maxn][maxn];

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	for (int i = 1; i <= m; i++)
	{
		if (tab[1][i] == '*') up[1][i] = n+1;
		else up[1][i] = 1;
	}

	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (tab[i][j] == '*') up[i][j] = n+1;
			else
			{
				if (tab[i-1][j] == '*') up[i][j] = i;
				else up[i][j] = up[i-1][j];
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		stack<pii> stk;

		for (int j = 1; j <= m; j++)
		{
			while (stk.size() && stk.top().ff <= up[i][j])
				stk.pop();

			if (stk.size() == 0) l[i][j] = 1;
			else l[i][j] = stk.top().ss+1;

			stk.push({up[i][j], j});
		}

		while (stk.size()) stk.pop();

		for (int j = m; j >= 1; j--)
		{
			while (stk.size() && stk.top().ff <= up[i][j])
				stk.pop();

			if (stk.size() == 0) r[i][j] = m;
			else r[i][j] = stk.top().ss-1;

			stk.push({up[i][j], j});
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans = max(ans, (r[i][j]-l[i][j]+1)*(i-up[i][j]+1));

	printf("%d\n", ans);
}
