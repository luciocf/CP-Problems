// Codeforces 1988D - The Omnipotent Monster Killer
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

const int maxn = 3e5+10;
const ll inf = 1e18+10;

vector<int> grafo[maxn];

ll a[maxn];

ll dp[maxn][65];
ll best[maxn][65];

void dfs(int u, int p)
{
    for (auto v: grafo[u])
    {
        if (v == p) continue;
        dfs(v, u);
    }
    
    for (int i = 1; i <= 63; i++)
    {
        dp[u][i] = 1ll*i*a[u];
        for (auto v: grafo[u])
            if (v != p)
                dp[u][i] += best[v][i];
    }

    for (int i = 1; i <= 63; i++)
    {
        best[u][i] = inf;
        for (int j = 1; j <= 63; j++)
            if (j != i)
                best[u][i] = min(best[u][i], dp[u][j]);
    }
}
void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        grafo[i].clear();

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        grafo[u].pb(v);
        grafo[v].pb(u);
    }
    
    dfs(1, 0);
    ll ans = inf;
    for (int i = 1; i <= 63; i++)
        ans = min(ans, dp[1][i]);

    cout << ans << nl;
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
 
