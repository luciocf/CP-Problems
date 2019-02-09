
// IOI 2011 - Race
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5+10;
const int MAXD = 1e6+10;
const int MAXL = 20;

typedef pair<int, int> pii;

int n, k, size[MAXN], ans;
set<int> S[MAXD];
bool mark[MAXN];
vector<pii> grafo[MAXN];

int DFS(int u, int p)
{
    size[u] = 1;
    for (int i = 0; i < (int) grafo[u].size(); i++)
    {
        int v = grafo[u][i].first;
        if (v == p || mark[v]) continue;

        size[u] += DFS(v, u);
    }
    return size[u];
}

int centroid(int u, int x, int p)
{
    for (int i = 0; i < (int) grafo[u].size(); i++)
    {
        int v = grafo[u][i].first;
        if (v == p || mark[v]) continue;

        if (size[v] > x/2) return centroid(v, x, u);
    }
    return u;
}

void upd(int u, int p, int d, int deep, int ok)
{
    if (d > k) return;

    if (ok) S[d].insert(deep);
    else S[d].erase(deep);

    for (int i = 0; i < (int) grafo[u].size(); i++)
    {
        int v = grafo[u][i].first;
        if (v == p || mark[v]) continue;

        upd(v, u, d+grafo[u][i].second, deep+1, ok);
    }
}

int get(int u, int p, int d, int deep)
{
    if (d > k) return 1e9;

    int aux = 1e9;
    if (S[k-d].size() > 0)
    {
        set<int>::iterator it = S[k-d].begin();
        aux = deep+*it;
    }

    for (int i = 0; i < (int) grafo[u].size(); i++)
    {
        int v = grafo[u][i].first;
        if (v == p || mark[v]) continue;

        aux = min(aux, get(v, u, d+grafo[u][i].second, deep+1));
    }
    return aux;
}

void decompose(int u)
{
    DFS(u, 0);

    int c = centroid(u, size[u], 0);
    mark[c] = 1;

    upd(c, 0, 0, 0, 1);

    int aux = 1e9;

    for (int i = 0; i < (int) grafo[c].size(); i++)
    {
        int v = grafo[c][i].first;
        if (mark[v]) continue;

        upd(v, c, grafo[c][i].second, 1, 0);
        aux = min(aux, get(v, c, grafo[c][i].second, 1));
        upd(v, c, grafo[c][i].second, 1, 1);
    }

    ans = min(ans, aux);

    upd(c, 0, 0, 0, 0);

    for (int i = 0; i < (int) grafo[c].size(); i++)
    {
        int v = grafo[c][i].first;
        if (!mark[v]) decompose(v);
    }
}

int best_path(int N, int K, int H[][2], int L[])
{
    n = N, k = K;
    for (int i = 0; i < n-1; i++)
    {
        int a = H[i][0]+1, b = H[i][1]+1, c = L[i];
        grafo[a].push_back(make_pair(b, c));
        grafo[b].push_back(make_pair(a, c));
    }

    ans = 1e9;
    decompose(1);
    return (ans==1e9)?(-1):ans;
}
