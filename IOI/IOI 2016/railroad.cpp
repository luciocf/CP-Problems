// IOI 2016 - Roller Coaster Railroad
// Lúcio Figueiredo

#include <bits/stdc++.h>
#include "railroad.h"

using namespace std;

typedef long long ll;

const int maxn = 4e5+10;

struct DSU
{
    int pai[maxn], peso[maxn];

    void init(int n)
    {
        for (int i = 0; i < n; i++)
            pai[i] = i, peso[i] = 1;
    }

    int Find(int x)
    {
        if (pai[x] == x) return x;
        return pai[x] = Find(pai[x]);
    }

    void Join(int x, int y)
    {
        x = Find(x), y = Find(y);
        if (x == y) return;

        if (peso[x] < peso[y]) swap(x, y);

        pai[y] = x, peso[x] += peso[y];
    }
} dsu;

struct Edge
{
    int u, v, w;

    bool operator< (const Edge o)
    {
        return w < o.w;
    }
};

map<int, int> mp;
int back[maxn];

int soma[maxn];

long long plan_roller_coaster(vector<int> s, vector<int> t)
{
    s.push_back(1e9); s.push_back(1);
    int n = (int) s.size();

    for (int i = 0; i < n; i++)
        mp[s[i]] = mp[t[i]] = 0;
    
    int aux = 0;
    for (auto &x: mp)
    {
        x.second = aux++;
        back[aux-1] = x.first;
    }

    ll ans = 0;
    vector<int> v;
    vector<Edge> edge;

    dsu.init(aux);
    for (int i = 0; i < n; i++)
    {
        soma[mp[s[i]]]++;
        soma[mp[t[i]]]--;

        v.push_back(mp[s[i]]);
        v.push_back(mp[t[i]]);

        dsu.Join(mp[s[i]], mp[t[i]]);
    }

    for (int i = 0; i < aux; i++)
    {
        if (i) soma[i] += soma[i-1];

        if (soma[i] > 0)
        {
            dsu.Join(i, i+1);
            ans += 1ll*(back[i+1]-back[i])*soma[i];
        }
        else if (soma[i] < 0) dsu.Join(i, i+1);

        if (i < aux-1) edge.push_back({i, i+1, back[i+1]-back[i]});
    }

    sort(edge.begin(), edge.end());

    for (auto pp: edge)
    {
        int u = pp.u, v = pp.v, w = pp.w;

        if (dsu.Find(u) != dsu.Find(v))
        {
            dsu.Join(u, v);
            ans += 1ll*w;
        }
    }

    return ans;
}
