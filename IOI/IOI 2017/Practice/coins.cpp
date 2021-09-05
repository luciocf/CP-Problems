// IOI 2017 Practice Session - Coins
// Lúcio Figueiredo

#include <bits/stdc++.h>
#include "coins.h"

using namespace std;

vector<int> coin_flips(vector<int> b, int c)
{
    int x = 0;

    for (int i = 0; i < 64; i++)
        if (b[i])
            x ^= i;

    vector<int> ans;
    ans.push_back(x^c);
    return ans;
}

int find_coin(vector<int> b)
{
    int c = 0;

    for (int i = 0; i < 64; i++)
        if (b[i])
            c ^= i;

    return c;
}
