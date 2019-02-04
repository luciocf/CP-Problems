// APIO 2015 - Skyscrapers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e4+10;
const int INF = 1e9+10;

typedef pair<int, int> pii;

int pos[MAXN], dist[MAXN], n;

bool mark[MAXN];

vector<pii> grafo[MAXN];

set<int> S[MAXN];

void dijkstra(int u)
{
    for (int i = 0; i < n; i++)
        dist[i] = INF;

    dist[u] = 0;

    priority_queue<pii, vector<pii>, greater<pii> > fila;
    fila.push({0, u});

    while (!fila.empty())
    {
        int u = fila.top().second;
        fila.pop();

        if (mark[u]) continue;

        for (auto P: grafo[u])
        {
            int v = P.second, d = P.first;

            if (dist[v] > dist[u]+d)
            {
                dist[v] = dist[u]+d;
                fila.push({dist[v], v});
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    int m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> pos[i] >> x;

        S[pos[i]].insert(x);
    }

    for (int i = 0; i < n; i++)
    {
        for (set<int>::iterator it = S[i].begin(); it != S[i].end(); it++)
        {
            int k = *it;

            for (int j = i+k; j < n; j+=k)
            {
                if (S[j].size() == 0) continue;

                int d = (j-i)/k;
                grafo[i].push_back({d, j});

                if (S[j].find(k) != S[j].end()) break;
            }

            for (int j = i-k; j >= 0; j-=k)
            {
                if (S[j].size() == 0) continue;

                int d = (i-j)/k;
                grafo[i].push_back({d, j});

                if (S[j].find(k) != S[j].end()) break;
            }
        }
    }

    dijkstra(pos[0]);

    if (dist[pos[1]] == INF) cout << "-1\n";
    else cout << dist[pos[1]] << "\n";
}
