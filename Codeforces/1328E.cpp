// Codeforces 1328E - Tree Queries
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

vector<int> grafo[maxn];
int st[maxn], en[maxn], pai[maxn], nivel[maxn], tt;

void dfs(int u, int p)
{
    st[u] = ++tt;
    for (auto v: grafo[u])
    {
        if (v == p) continue;
        nivel[v] = nivel[u]+1, pai[v] = u;
        dfs(v, u);
    }
    en[u] = tt;
}

bool inside(int u, int v)
{
    return st[u] <= st[v] and st[v] <= en[u];
}

void solve()
{
    int n, m;
    cin >> n >> m;
    
    pai[1] = 1;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        grafo[u].pb(v); grafo[v].pb(u);
    }

    dfs(1, 0);

    while (m--)
    {
        int k;
        cin >> k;

        vector<int> vv(k+1);
        int mx = -1, u;
        for (int i = 1; i <= k; i++)
        {
            cin >> vv[i];
            if (nivel[vv[i]] > mx)
                u = vv[i], mx = nivel[vv[i]];
        }
        
        bool ok = 1;
        for (int i = 1; i <= k; i++)
        {
            if (!inside(vv[i], u) and !inside(pai[vv[i]], u))
                ok = 0;
        }

        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
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

