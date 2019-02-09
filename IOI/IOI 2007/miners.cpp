// IOI 2007 - Miners
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
const int INF = 1e9;

int num[MAXN], dp[2][4][4][4][4], n;

int get(int a, int b, int c)
{
    if ((a == 0 && b == 0) || (a == 0 && b == c) || (a == c && b == 0) || (a == b && a == c))
        return 1;
    if (a != 0 && b != 0 && a != b && a != c && b != c)
        return 3;
    return 2;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> n >> s;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'M') num[i+1] = 1;
        else if (s[i] == 'B') num[i+1] = 2;
        else num[i+1] = 3;
    }

    for (int i = 1; i <= n; i++)
        for (int a1 = 0; a1 <= 3; a1++)
            for (int a2 = 0; a2 <= 3; a2++)
                for (int b1 = 0; b1 <= 3; b1++)
                    for (int b2 = 0; b2 <= 3; b2++)
                        dp[i%2][a1][a2][b1][b2] = -INF;

    dp[1][0][num[1]][0][0] = 1;
    dp[1][0][0][0][num[1]] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int a1 = 0; a1 <= 3; a1++)
        {
            for (int a2 = 0; a2 <= 3; a2++)
            {
                for (int b1 = 0; b1 <= 3; b1++)
                {
                    for (int b2 = 0; b2 <= 3; b2++)
                    {
                        int d = get(a1, a2, num[i]);
                        dp[i%2][a1][num[i]][b2][b1] = max(dp[i%2][a1][num[i]][b2][b1], dp[(i-1)%2][a2][a1][b2][b1]+d);
                        d = get(b1, b2, num[i]);
                        dp[i%2][a2][a1][b1][num[i]] = max(dp[i%2][a2][a1][b1][num[i]], dp[(i-1)%2][a2][a1][b2][b1]+d);
                    }
                }
            }
        }
    }
    int ans = -INF;
    for (int a1 = 0; a1 <= 3; a1++)
        for (int a2 = 0; a2 <= 3; a2++)
            for (int b1 = 0; b1 <= 3; b1++)
                for (int b2 = 0; b2 <= 3; b2++)
                    ans = max(ans, max(dp[n%2][a1][num[n]][b2][b1], dp[n%2][a2][a1][b1][num[n]]));
    cout << ans << "\n";
}
