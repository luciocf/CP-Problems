// Codeforces 1385E - Directing Edges
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

const int maxn = 2e5+10;

int tin[maxn], tt;
int mark[maxn];
vector<int> grafo[maxn];

bool dfs(int u)
{
    mark[u] = 1;
    bool ok = 1;
    for (auto v: grafo[u])
    {
        if (mark[v] == 1) return 0;
        if (!mark[v]) ok &= dfs(v);
    }

    tin[u] = tt--;
    mark[u] = 2;
    return ok;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    tt = n;
    for (int i = 1; i <= n; i++)
    {
        grafo[i].clear(); mark[i] = 0;
    }

    vector<pii> edges, todo;
    for (int i = 1; i <= m; i++)
    {
        int t, u, v;
        cin >> t >> u >> v;

        if (t == 1)
        {
            edges.pb({u, v});
            grafo[u].pb(v);
        }
        else todo.pb({u, v});
    }

    bool ok = 1;
    for (int i = 1; i <= n; i++)
        if (!mark[i])
            ok &= dfs(i);

    if (!ok)
    {
        cout << "NO\n";
        return;
    }
    
    cout << "YES\n";
    for (auto [u, v]: edges)
        cout << u << " " << v << nl;
    for (auto [u, v]: todo)
    {
        if (tin[u] < tin[v]) cout << u << " " << v << nl;
        else cout << v << " " << u << nl;
    }
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		solve();
	}
}

