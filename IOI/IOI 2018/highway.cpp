// IOI 2018 - Highway Tolls
// Lúcio Figueiredo

#include <bits/stdc++.h>
#include "highway.h"
using namespace std;

const int maxn = 2e5+10;

typedef pair<int, int> pii;
typedef long long ll;

int M;
ll D;

vector<pii> grafo[maxn], tree[2][maxn];

int pai[2][maxn], edge[2][maxn];
int dist[2][maxn];

bool is[maxn];

void bfs(int s, int k)
{
    queue<int> fila;
    dist[k][s] = 0, fila.push(s);

    while (!fila.empty())
    {
        int u = fila.front(); fila.pop();

        for (auto pp: grafo[u])
        {
            int v = pp.first, e = pp.second;

            if (dist[k][v] == -1)
            {
                dist[k][v] = dist[k][u]+1, pai[k][v] = u, edge[k][v] = e;
                fila.push(v);
            }
        }
    }
}

vector<int> lista[2];

void dfs(int u, int p, int k)
{
    for (auto pp: tree[k][u])
        if (pp.first != p)
            dfs(pp.first, u, k);

    lista[k].push_back(u);
}

int get(int k)
{
    int ini = 0, fim = (int)(lista[k].size())-2, ans = lista[k].back();

    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        vector<int> w(M, 1);

        for (int i = 0; i < M; i++)
            if (is[i])
                w[i] = 0;

        for (int i = 0; i <= mid; i++)
            w[edge[k][lista[k][i]]] = 1;

        ll d = ask(w);

        if (d > D) ans = lista[k][mid], fim = mid-1;
        else ini = mid+1;
    }

    return ans;
}

void find_pair(int N, vector<int> U, vector<int> V, int A, int B)
{
    M = U.size();
    vector<int> w(M);

    D = ask(w);

    int ini = 0, fim = M-1, ind = 0;
    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        for (int i = 0; i <= mid; i++)
            w[i] = 1;

        ll d = ask(w);

        if (d > D) ind = mid, fim = mid-1;
        else ini = mid+1;

        for (int i = 0; i <= mid; i++)
            w[i] = 0;
    }

    for (int i = 0; i < M; i++)
    {
        grafo[U[i]].push_back({V[i], i});
        grafo[V[i]].push_back({U[i], i});
    }

    memset(dist, -1, sizeof dist);
    bfs(U[ind], 0); bfs(V[ind], 1);

    is[ind] = 1;

    for (int i = 0; i < N; i++)
    {
        if (dist[0][i] == dist[1][i] || i == U[ind] || i == V[ind]) continue;

        if (dist[0][i] < dist[1][i])
        {
            is[edge[0][i]] = 1;

            tree[1][i].push_back({pai[0][i], edge[0][i]});
            tree[0][pai[0][i]].push_back({i, edge[0][i]});
        }
        else
        {
            is[edge[1][i]] = 1;

            tree[1][i].push_back({pai[1][i], edge[1][i]});
            tree[1][pai[1][i]].push_back({i, edge[1][i]});
        }
    }

    dfs(U[ind], -1, 0); dfs(V[ind], -1, 1);

    answer(get(0), get(1));
}
