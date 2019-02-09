// IOI 2012 - Crayfish Scrivener
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6+10;
const int MAXL = 22;

int t, pai, nivel[MAXN], k[MAXN], tab[MAXN][MAXL];

char C[MAXN];

void Init(void)
{
    memset(tab, -1, sizeof tab);
}

void TypeLetter(char c)
{
    t++;
    k[t] = t, C[t] = c, nivel[t] = nivel[pai]+1;

    tab[t][0] = pai;
    for (int j = 1; j < MAXL; j++)
        if (tab[t][j-1] != -1)
            tab[t][j] = tab[tab[t][j-1]][j-1];
    pai = t;
}

void UndoCommands(int u)
{
    k[t+1] = k[t-u];
    t++;
    pai = k[t];
}

char GetLetter(int p)
{
    if (p+1 == nivel[k[t]]) return C[k[t]];

    int u = k[t];
    p = nivel[k[t]]-p-1;
    for (int i = MAXL-1; i >= 0; i--)
        if (p-(1<<i) >= 0)
            u = tab[u][i], p -= (1<<i);
    return C[u];
}
