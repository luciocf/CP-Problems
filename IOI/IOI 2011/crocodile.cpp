// IOI 2011 - Crocodile's Underground City
// Lúcio Cardoso

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXN = 1e5+10;
const long long INF = 1e15+10;

typedef long long ll;
typedef pair<ll, int> pll;

int n, k, is[MAXN];

ll d1[MAXN], d2[MAXN];

bool mark[MAXN];

vector<pll> grafo[MAXN];

void Dijkstra(void)
{
    for (int i = 0; i < n; i++)
        d1[i] = d2[i] = INF;
    priority_queue<pll, vector<pll>, greater<pll> > fila;
    for (int i = 0; i < k; i++)
    {
        d1[is[i]] = d2[is[i]] = 0LL;
        fila.push(mp(0LL, is[i]));
    }

    while (true)
    {
        int davez = -1;
        while (!fila.empty())
        {
            int atual = fila.top().second;
            fila.pop();
            if (!mark[atual])
            {
                davez = atual;
                break;
            }
        }
        if (davez == -1) break;
        mark[davez] = true;

        for (int i = 0; i < grafo[davez].size(); i++)
        {
            int x = grafo[davez][i].second;
            ll d = grafo[davez][i].first;

            bool ok = 0;
            if (d1[x] > d2[davez]+d)
            {
                d2[x] = d1[x], d1[x] = d2[davez]+d;
                ok = 1;
            }
            else if (d2[davez]+d >= d1[x] && d2[davez]+d <= d2[x])
            {
                d2[x] = d2[davez]+d;
                ok = 1;
            }

            if (ok && d2[x] != INF)
                fila.push(mp(d2[x], x));
        }
    }
}

int main(void)
{
    int m;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        grafo[a].pb(mp(c, b));
        grafo[b].pb(mp(c, a));
    }
    
    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        is[i] = x;
    }

    Dijkstra();
    printf("%lld\n", d2[0]);
}
