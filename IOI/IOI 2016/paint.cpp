// IOI 2016 - Paint By Numbers
// Lúcio Figueiredo

#include <bits/stdc++.h>
#include "paint.h"

using namespace std;

const int maxn = 2e5+10;

int soma[2][maxn], pref[110];
bool can[2][maxn][110];

int black[maxn], white[maxn];

int get(int l, int r, int q)
{
    return soma[q][r] - soma[q][l-1];
}

string solve_puzzle(string s, vector<int> c)
{
    int n = (int) s.size(), k = (int) c.size();

    for (int i = 1; i <= n; i++)
    {
        soma[0][i] = soma[0][i-1] + (s[i-1] == '_');
        soma[1][i] = soma[1][i-1] + (s[i-1] == 'X');
    }

    for (int i = 1; i <= k; i++)
        pref[i] = pref[i-1] + c[i-1];

    can[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        can[0][i][0] = (get(1, i, 1) == 0);

    for (int j = 1; j <= k; j++)
    {
        for (int i = c[j-1]; i <= n; i++)
        {
            if (s[i-1] == '_') can[0][i][j] = can[0][i-1][j];
            else if (s[i-1] == 'X' && get(i-c[j-1]+1, i, 0) == 0)
            {
                if (i-c[j-1] == 0 && j == 1) can[0][i][j] = 1;
                else if (i-c[j-1] > 0 && s[i-c[j-1]-1] != 'X') can[0][i][j] |= can[0][i-c[j-1]-1][j-1]; 
            }
            else if (s[i-1] == '.')
            {
                can[0][i][j] = can[0][i-1][j];

                if (get(i-c[j-1]+1, i, 0) == 0)
                {
                    if (i-c[j-1] == 0 && j == 1) can[0][i][j] = 1;
                    else if (i-c[j-1] > 0 && s[i-c[j-1]-1] != 'X') can[0][i][j] |= can[0][i-c[j-1]-1][j-1]; 
                }
            }
        }
    }

    can[1][n+1][k+1] = 1;
    for (int i = 1; i <= n; i++)
        can[1][i][k+1] = (get(i, n, 1) == 0);

    for (int j = k; j >= 1; j--)
    {
        for (int i = n-c[j-1]+1; i >= 1; i--)
        {
            if (s[i-1] == '_') can[1][i][j] = can[1][i+1][j];
            else if (s[i-1] == 'X' && get(i, i+c[j-1]-1, 0) == 0)
            {
                if (i+c[j-1] == n+1 && j == k) can[1][i][j] = 1;
                else if (i+c[j-1] < n+1 && s[i+c[j-1]-1] != 'X') can[1][i][j] |= can[1][i+c[j-1]+1][j+1]; 
            }
            else if (s[i-1] == '.')
            {
                can[1][i][j] = can[1][i+1][j];

                if (get(i, i+c[j-1]-1, 0) == 0)
                {
                    if (i+c[j-1] == n+1 && j == k) can[1][i][j] = 1;
                    else if (i+c[j-1] < n+1 && s[i+c[j-1]-1] != 'X') can[1][i][j] |= can[1][i+c[j-1]+1][j+1]; 
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++)
            if (s[i-1] != 'X' && can[0][i-1][j] && can[1][i+1][j+1])
                white[i] = 1;

    for (int j = 1; j <= k; j++)
    {
        for (int i = c[j-1]; i <= n; i++)
        {
            if (s[i-1] == '_') continue;

            bool ok1 = 0, ok2 = 0, ok3 = 0;

            if (get(i-c[j-1]+1, i, 0) == 0)
            {
                if (i-c[j-1] == 0 && j == 1) ok1 = 1;
                else if (i-c[j-1] > 0 && s[i-c[j-1]-1] != 'X') ok1 = 1;
            }

            if (i-c[j-1] == 0 && j == 1) ok2 = 1;
            else if (i-c[j-1] > 0 && can[0][i-c[j-1]-1][j-1]) ok2 = 1;

            if (i+1 == n+1 && j == k) ok3 = 1;
            else if (i+1 < n+1 && s[i] != 'X' && can[1][i+2][j+1]) ok3 = 1;

            if (ok1 && ok2 && ok3) black[i-c[j-1]+1]++, black[i+1]--;
        }
    }

    for (int i = 1; i <= n; i++)
        black[i] += black[i-1];

    string ans;

    for (int i = 1; i <= n; i++)
    {
        if (black[i] && white[i]) ans += '?';
        else if (white[i]) ans += '_';
        else ans += 'X';
    }

    return ans;
}
