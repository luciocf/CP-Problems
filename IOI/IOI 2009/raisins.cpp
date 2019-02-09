// IOI 2009 - Raisins
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 54;
const int INF = 1e9+10;

int num[MAXN][MAXN], soma[MAXN][MAXN], n, m;
int dp[MAXN][MAXN][MAXN][MAXN];

void pre(void)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            soma[i][j] = soma[i][j-1]+soma[i-1][j]+num[i][j]-soma[i-1][j-1];
}

int main(void)
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &num[i][j]);
    pre();

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = 1; k <= m; k++)
                for (int l = k; l <= m; l++)
                    if (!(i == j && k == l))
                        dp[i][j][k][l] = INF;

    for (int i = n; i >= 1; i--)
    {
        for (int j = i; j <= n; j++)
        {
            for (int k = m; k >= 1; k--)
            {
                for (int l = k; l <= m; l++)
                {
                    if (i == j && k == l) continue;
                    for (int a = i; a < j; a++)
                        dp[i][j][k][l] = min(dp[i][j][k][l], dp[i][a][k][l]+dp[a+1][j][k][l]);
                    for (int a = k; a < l; a++)
                        dp[i][j][k][l] = min(dp[i][j][k][l], dp[i][j][k][a]+dp[i][j][a+1][l]);
                    dp[i][j][k][l] += (soma[j][l]-soma[i-1][l]-soma[j][k-1]+soma[i-1][k-1]);
                }
            }
        }
    }
    printf("%d\n", dp[1][n][1][m]);
}
