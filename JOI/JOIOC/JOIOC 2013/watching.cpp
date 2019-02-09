// JOI Open Contest 2013 - Watching
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2010;

typedef long long ll;

int n, p, q, num[MAXN];
int dp[MAXN][MAXN], next_[2][MAXN];

int busca2(int k)
{
    if (k > num[n]) return n;

    int ini = 1, fim = n, ans;
    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        if (num[mid] <= k) ans = mid, ini = mid+1;
        else fim = mid-1;
    }
    return ans;
}

bool ok(int w)
{
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= q; j++)
            dp[i][j] = 1;

    for (int i = 1; i <= n; i++)
        next_[0][i] = busca2(num[i]+w-1), next_[1][i] = busca2(num[i]+2*w-1);

    for (int i = 0; i <= p; i++)
    {
        for (int j = 0; j <= q; j++)
        {
            if (i)
                dp[i][j] = max(dp[i][j], next_[0][min(n, dp[i-1][j]+1)]);
            if (j)
                dp[i][j] = max(dp[i][j], next_[1][min(n, dp[i][j-1]+1)]);
        }
    }
    return (dp[p][q] >= n);
}

int busca(void)
{
    int ini = 1, fim = 1e9+10, ans;
    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        if (ok(mid)) ans = mid, fim = mid-1;
        else ini = mid+1;
    }
    return ans;
}

int main(void)
{
    scanf("%d %d %d", &n, &p, &q);

    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);

    if (p+q >= n)
    {
        cout << "1\n";
        return 0;
    }

    sort(num+1, num+n+1);
    printf("%d\n", busca());
}
