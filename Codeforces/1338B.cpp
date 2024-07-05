// Codeforces 1338B - Edge Weight Assignment
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e5+10;

int nivel[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
    for (auto v: grafo[u])
    {
        if (v == p) continue;
        nivel[v] = nivel[u]+1;
        dfs(v, u);
    }
}

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        grafo[u].pb(v); grafo[v].pb(u);
    }

    if (n == 2)
    {
        cout << "1 1\n";
        return;
    }
    
    int root = 0;
    for (int i = 1; i <= n; i++)
        if (grafo[i].size() > 1)
            root = i;

    dfs(root, 0);

    int mn = 1, mx = n-1;
    bool par = 0, imp = 0;

    for (int u = 1; u <= n; u++)
    {
        int qtd = 0;
        for (auto v: grafo[u])
            if (nivel[v] > nivel[u] and grafo[v].size() == 1)
                qtd++;

        mx -= (qtd > 0 ? (qtd-1) : 0);

        if (grafo[u].size() == 1)
            par |= (nivel[u]%2 == 0), imp |= (nivel[u]%2);
    }

    if (par and imp) mn = 3;

    cout << mn << " " << mx << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
//	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
 
