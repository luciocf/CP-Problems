// IOI 2009 - POI
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e3+10;
const int MAXM = 2e3+10;

int task[MAXM];
int num[MAXN][MAXM];

struct C {
    int v, q, id;
} comp[MAXN];

bool check(C a, C b)
{
    if (a.v == b.v && a.q == b.q)
        return a.id < b.id;
    if (a.v == b.v)
        return a.q > b.q;
    return a.v > b.v;
}

int main(void)
{
    int n, m, p;
    cin >> n >> m >> p;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> num[i][j];
            if (!num[i][j])
                task[j]++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int q = 0, v = 0;
        comp[i].id = i;
        for (int j = 1; j <= m; j++)
            if (num[i][j])
                q++, v += task[j];
        comp[i].q = q, comp[i].v = v;
    }
    sort(comp+1, comp+n+1, check);

    for (int i = 1; i <= n; i++)
    {
        if (comp[i].id == p)
        {
            cout << comp[i].v << " " << i << "\n";
            return 0;
        }
    }
}
