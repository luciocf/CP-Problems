// APIO 2009 - ATM
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5+10;
const int INF = 2e9+10;

int num[MAXN], in[MAXN], low[MAXN], comp[MAXN], sum[MAXN], dp[MAXN], t, c, n;

bool pub[MAXN];

vector<int> grafo[MAXN], dag[MAXN];

stack<int> stk;

void DFS(int u)
{
    in[u] = low[u] = ++t;
    stk.push(u);

    for (auto v: grafo[u])
    {
        if (in[v])
        {
            low[u] = min(low[u], in[v]);
            continue;
        }

        DFS(v);

        low[u] = min(low[u], low[v]);
    }

    if (low[u] == in[u])
    {
        c++;
        sum[c] += num[u], comp[u] = c;

        while (stk.top() != u)
        {
            sum[c] += num[stk.top()], comp[stk.top()] = c;

            in[stk.top()] = INF, stk.pop();
        }

        in[u] = INF, stk.pop();
    }
}

int solve(int u)
{
    if (dp[u] != -1) return dp[u];

    int aux = -INF;
    for (auto v: dag[u])
        aux = max(aux, sum[u]+solve(v));

    if (pub[u]) return dp[u] = max(aux, sum[u]);
    return dp[u] = aux;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    
    int m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;

        grafo[u].push_back(v);
    }

    for (int i = 1; i <= n; i++)
        cin >> num[i];

    int s, p;
    cin >> s >> p;

    DFS(s);

    for (int i = 1; i <= p; i++)
    {
        int u;
        cin >> u;

        pub[comp[u]] = 1;
    }

    for (int i = 1; i <= n; i++)
        for (auto v: grafo[i])
            if (comp[i] != comp[v])
                dag[comp[i]].push_back(comp[v]);

    memset(dp, -1, sizeof dp);
    cout << solve(comp[s]) << "\n";
}
