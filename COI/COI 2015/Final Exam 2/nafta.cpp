// COI 2015 - Final Exam #2 - Nafta
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COI/official/2015/final-exam2/solutions.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

int n, m;
char tab[maxn][maxn];

int cc;
bool mark[maxn][maxn];

int comp[maxn][maxn], soma[maxn*maxn];
int ini[maxn*maxn], fim[maxn*maxn];

int dentro[maxn][maxn], qtd[maxn][maxn];

int dp[maxn][maxn], opt[maxn][maxn];

void dfs(int i, int j)
{
	mark[i][j] = 1;
	ini[cc] = min(ini[cc], j), fim[cc] = max(fim[cc], j);

	soma[cc] += (int)(tab[i][j]-'0');

	for (int k = 0; k < 4; k++)
	{
		int a = i+linha[k], b = j+coluna[k];

		if (a < 1 || a > n || b < 1 || b > m || mark[a][b] || tab[a][b] == '.') continue;

		dfs(a, b);
	}
}

void solve(int i, int l, int r)
{
	if (l > r) return;

	int mid = (l+r)>>1;

	for (int j = opt[l-1][i]; j < mid && j <= opt[r+1][i]; j++)
		if (dp[mid][i] < dp[j][i-1] + qtd[mid][j])
			dp[mid][i] = dp[j][i-1] + qtd[mid][j], opt[mid][i] = j;

	solve(i, l, mid-1); solve(i, mid+1, r);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (tab[i][j] != '.' && !mark[i][j])
			{
				++cc;
				ini[cc] = fim[cc] = j;
				dfs(i, j);
			}
		}
	}

	for (int i = 1; i <= cc; i++)
		for (int j = ini[i]; j <= fim[i]; j++)
			dentro[ini[i]][j] += soma[i];

	for (int i = 1; i <= m; i++)
		for (int j = i-1; j >= 0; j--)
			qtd[i][j] = dentro[j+1][i] + qtd[i][j+1];

	for (int i = 1; i <= m; i++)
	{
		opt[0][i] = 0, opt[m+1][i] = m;

		solve(i, 1, m);
	}

	for (int i = 1; i <= m; i++)
	{
		int ans = 0;
		for (int j = 1; j <= m; j++)
			ans = max(ans, dp[j][i]);

		printf("%d\n", ans);
	}
}
