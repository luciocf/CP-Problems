// Balkan OI 2012 - Fan Groups
// Lúcio Cardoso

// Solution is the same as: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Fan%20Groups/main.cpp

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e4+10;
const int maxm = 2e5+10;
const int inf = 1e9+10;

int n, m;

int in[maxn], low[maxn], tt;
int scc[maxn], grau[maxn], cc;

int gg, group[maxn];

bool mark[maxn], ok;

vector<pii> grafo[maxn], edge;

vector<int> dag[maxn], last[maxn];
vector<int> inScc[maxn], inGroup[maxn], topsort;

stack<int> stk;

void dfs(int u)
{
    in[u] = low[u] = ++tt;
    stk.push(u);

    for (auto pp: grafo[u])
    {
        int v = pp.first;

        if (in[v])
        {
            low[u] = min(low[u], in[v]);
            continue; 
        }

        dfs(v);

        low[u] = min(low[u], low[v]);
    }

    if (low[u] != in[u]) return;

    ++cc;

    while (true)
    {
        int x = stk.top();
        stk.pop();

        scc[x] = cc, in[x] = inf;
        inScc[cc].push_back(x);

        if (x == u) break;
    }
}

void dfsCheck(int u)
{
    group[u] = gg;
    inGroup[gg].push_back(u);

    for (auto v: dag[u])
    {
        if (group[v])
        {
            if (group[v] != gg)
            {
                ok = 0;
                return;
            }
        }
        else
            dfsCheck(v);
    }
}

void dfsTopsort(int u)
{
    mark[u] = true;

    for (auto v: last[u])
        if (!mark[v])
            dfsTopsort(v);

    topsort.push_back(u); 
}

int main(void)
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        if (!w)
            grafo[u].push_back({v, i});
        else
            edge.push_back({u, v});
    }

    for (int i = 1; i <= n; i++)
        if (!in[i])
            dfs(i);

    for (int i = 1; i <= n; i++)
    {
        for (auto pp: grafo[i])
        {
            int v = pp.first, e = pp.second;

            if (scc[i] != scc[v])
            {
                dag[scc[i]].push_back(scc[v]);
                grau[scc[v]]++;
            }
        }
    }

    ok = 1;
    for (int i = 1; i <= cc; i++)
    {
        if (!grau[i])
        {
            ++gg;
            dfsCheck(i);

            if (!ok)
            {
                printf("-1\n");
                return 0;
            }
        }
    }

    for (auto E: edge)
    {
        int u = E.first, v = E.second;

        if (scc[u] == scc[v] || group[scc[u]] == group[scc[v]])
        {
            printf("-1\n");
            return 0;
        }

        last[group[scc[v]]].push_back(group[scc[u]]);
    }

    for (int i = 1; i <= gg; i++)
        if (!mark[i])
            dfsTopsort(i);

    if (topsort.size() != gg)
    {
        printf("-1\n");
        return 0;
    }

    reverse(topsort.begin(), topsort.end());

    for (int i = 0; i < topsort.size(); i++)
    {
        int G = topsort[i];

        for (int j = 0; j < inGroup[G].size(); j++)
        {
            int S = inGroup[G][j];

            for (int k = 0; k < inScc[S].size(); k++)
            {
                printf("%d", inScc[S][k]);

                if (k == inScc[S].size()-1 && j == inGroup[G].size()-1 && i == topsort.size()-1)
                    printf("\n");
                else
                    printf(" ");
            }
        }
    }
}

/*
    * bounds (maxn)
    * long long
    * all variables reset?
    * check if indexing is ok
    * off by one? (n-i+1) or (n-i)?
    * edge cases (n=0, n=1, n < 0, n=maxn)
*/
