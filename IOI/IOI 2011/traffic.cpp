
// IOI 2010 - Traffic Congestion
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6+10;

int s[MAXN], d[MAXN], p[MAXN], pai[MAXN];

ll soma[MAXN], num[MAXN];

vector<int> grafo[MAXN];

ll DFS(int u, int p)
{
    for (int i = 0; i < (int) grafo[u].size(); i++)
    {
        int v = grafo[u][i];
        if (v == p) continue;

        pai[v] = u;
        soma[u] += DFS(v, u);
    }
    soma[u]+=num[u];
    return soma[u];
}

int LocateCentre(int n, int p[], int s[], int d[])
{
    for (int i = 0; i < n-1; i++)
    {
        grafo[s[i]].push_back(d[i]);
        grafo[d[i]].push_back(s[i]);
    }
    for (int i = 0; i < n; i++) num[i] = p[i];

    DFS(0, -1);

    int ind;
    ll ans = 1e18;
    for (int i = 0; i < n; i++)
    {
        ll aux = soma[0]-soma[i];
        for (int j = 0; j < (int) grafo[i].size(); j++)
        {
            if (grafo[i][j] == pai[i]) continue;
            aux = max(aux, soma[grafo[i][j]]);
        }
        if (aux < ans)
            ans = aux, ind = i;
    }
    return ind;
}

int main(void)
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n-1; i++) cin >> s[i] >> d[i];

    cout << LocateCentre(n, p, s, d) << "\n";
}
