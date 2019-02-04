// Seletiva IOI 2015 - Gude
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300010;

int num[MAXN];
long long dp[MAXN];

int main(void)
{
    int n, s;
    scanf("%d %d", &n, &s);

    for (int i = 1; i <= n; i++)
        scanf("%d", &num[i]);

    sort(num+1, num+n+1);

    dp[1] = 1LL*s;
    int menor = num[1];
    for (int i = 2; i <= n; i++)
    {
        if (dp[i-1]+s <= dp[i-1]-(num[i-1]-menor)+num[i]-menor)
        {
            menor = num[i];
            dp[i] = dp[i-1]+s;
        }
        else
            dp[i] = dp[i-1]-(num[i-1]-menor)+num[i]-menor;
    }
    
    printf("%lld\n", dp[n]);
}
