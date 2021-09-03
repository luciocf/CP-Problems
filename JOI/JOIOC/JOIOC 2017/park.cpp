// JOI Open Contest 2017 - Amusement Park
// Lúcio Figueiredo

// ------------- Joi.cpp -------------

#include <bits/stdc++.h>
#include "Joi.h"

using namespace std;

const int maxn_0 = 2e4+10;

int grau_0[maxn_0], bit_0[maxn_0];

vector<int> grafo_0[maxn_0], grupo_0[maxn_0];

set<int> adj_0[maxn_0];

int pai_0[maxn_0];
bool mark_0[maxn_0];

void get_sp_0(int u)
{
    mark_0[u] = 1;

    for (auto v: grafo_0[u])
    {
        if (!mark_0[v])
        {
            pai_0[v] = u;
            get_sp_0(v);
        }
    }
}

bool connect_0(int u, int v)
{
    return (adj_0[u].find(v) != adj_0[u].end());
}

void dfs_0_0(int u, int p)
{
    if (grupo_0[0].size() < 60)
    {
        bit_0[u] = grupo_0[0].size();
        grupo_0[0].push_back(u);
    }

    for (auto v: grafo_0[u])
        if (v != p)
            dfs_0_0(v, u);
}

void dfs_1(int u, int p)
{
    for (auto v: grafo_0[u])
    {
        if (v == p) continue;

        bool ok = 0;
        for (auto w: grupo_0[u])
            if (w == v)
                ok = 1;

        if (ok)
        {
            for (auto w: grupo_0[u])
                grupo_0[v].push_back(w);

            dfs_1(v, u);
            continue;
        }

        for (auto w1: grupo_0[u])
            for (auto w2: grupo_0[u])
                if (w1 != w2 && connect_0(w1, w2))
                    grau_0[w1]++;

        int out;
        for (auto w: grupo_0[u])
        {
            if (grau_0[w] == 1 && w != u)
            {
                out = w, bit_0[v] = bit_0[w];
                break;
            }
        }

        grupo_0[v].push_back(v);
        for (auto w: grupo_0[u])
            if (w != out)
                grupo_0[v].push_back(w);

        for (auto w1: grupo_0[u])
            for (auto w2: grupo_0[u])
                if (w1 != w2 && connect_0(w1, w2))
                    grau_0[w1]--;

        dfs_1(v, u);
    }  
}

void Joi(int N, int M, int A[], int B[], long long X, int T)
{
    for (int i = 0; i < M; i++)
    {
        grafo_0[A[i]].push_back(B[i]);
        grafo_0[B[i]].push_back(A[i]);
    }

    get_sp_0(0);

    for (int i = 0; i < N; i++)
        grafo_0[i].clear();

    for (int i = 1; i < N; i++)
    {
        grafo_0[i].push_back(pai_0[i]);
        grafo_0[pai_0[i]].push_back(i);

        adj_0[i].insert(pai_0[i]);
        adj_0[pai_0[i]].insert(i);
    }

    dfs_0_0(0, -1);
    dfs_1(0, -1);

    for (int i = 0; i < N; i++)
    {
        if (X & (1ll<<bit_0[i])) MessageBoard(i, 1);
        else MessageBoard(i, 0);
    }
}

// ------------- Ioi.cpp -------------

#include <bits/stdc++.h>
#include "Ioi.h"

using namespace std;

const int maxn = 2e4+10;

int grau[maxn], bit[maxn];

bool on[61];

vector<int> grafo[maxn], grupo[maxn];

set<int> adj[maxn];

int pai[maxn];
bool mark[maxn];

void get_sp(int u)
{
    mark[u] = 1;

    for (auto v: grafo[u])
    {
        if (!mark[v])
        {
            pai[v] = u;
            get_sp(v);
        }
    }
}

bool connect(int u, int v)
{
    return (adj[u].find(v) != adj[u].end());
}

void dfs_0(int u, int p)
{
    if (grupo[0].size() < 60)
    {
        bit[u] = (int)grupo[0].size();
        grupo[0].push_back(u);
    }

    for (auto v: grafo[u])
        if (v != p)
            dfs_0(v, u);
}

void dfs(int u, int p)
{
    for (auto v: grafo[u])
    {
        if (v == p) continue;

        bool ok = 0;
        for (auto w: grupo[u])
            if (w == v)
                ok = 1;

        if (ok)
        {
            for (auto w: grupo[u])
                grupo[v].push_back(w);

            dfs(v, u);
            continue;
        }

        for (auto w1: grupo[u])
            for (auto w2: grupo[u])
                if (w1 != w2 && connect(w1, w2))
                    grau[w1]++;

        int out;
        for (auto w: grupo[u])
        {
            if (grau[w] == 1 && w != u)
            {
                out = w, bit[v] = bit[w];
                break;
            }
        }

        grupo[v].push_back(v);
        for (auto w: grupo[u])
            if (w != out)
                grupo[v].push_back(w);

        for (auto w1: grupo[u])
            for (auto w2: grupo[u])
                if (w1 != w2 && connect(w1, w2))
                    grau[w1]--;

        dfs(v, u);
    }  
}

void get(int u, int p, int P)
{
    for (auto v: grafo[u])
    {
        if (v == p) continue;

        bool ok = 0;
        for (auto w: grupo[P])
            if (v == w)
                ok = 1;

        if (!ok) continue;

        on[bit[v]] = Move(v);
        get(v, u, P);
        Move(u);
    }
}

long long Ioi(int N, int M, int A[], int B[], int P, int V, int T)
{
    for (int i = 0; i < M; i++)
    {
        grafo[A[i]].push_back(B[i]);
        grafo[B[i]].push_back(A[i]);
    }

    get_sp(0);

    for (int i = 0; i < N; i++)
        grafo[i].clear();

    for (int i = 1; i < N; i++)
    {
        grafo[i].push_back(pai[i]);
        grafo[pai[i]].push_back(i);

        adj[i].insert(pai[i]);
        adj[pai[i]].insert(i);
    }

    dfs_0(0, -1);
    dfs(0, -1);

    on[bit[P]] = V;
    get(P, -1, P);

    long long ans = 0;
    for (int i = 0; i < 60; i++)
        if (on[i])
            ans += (1ll<<i);

    return ans;
}
