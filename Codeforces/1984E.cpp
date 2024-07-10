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

int dp[maxn][2], ans;
vector<int> grafo[maxn];

void dfs(int u, int p)
{
    dp[u][0] = 0, dp[u][1] = 1;
    for (auto v: grafo[u])
    {
        if (v == p) continue;
        
        dfs(v, u);
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][1], dp[v][0]);
    }
}

void solve(int u, int p)
{
    if (grafo[u].size() == 1)
        ans = max({ans, dp[u][1], 1+dp[u][0]});

    for (auto v: grafo[u])
    {
        if (v == p) continue;
        int ant_u[2] = {dp[u][0], dp[u][1]};
        int ant_v[2] = {dp[v][0], dp[v][1]};

        dp[u][0] -= max(dp[v][0], dp[v][1]);
        dp[u][1] -= dp[v][0];

        dp[v][1] += dp[u][0];
        dp[v][0] += max(dp[u][0], dp[u][1]);
        solve(v, u);

        dp[u][0] = ant_u[0], dp[u][1] = ant_u[1];
        dp[v][0] = ant_v[0], dp[v][1] = ant_v[1];
    }
}

void solve()
{
    int n;
    cin >> n;
    
    ans = 0;
    for (int i = 1; i <= n; i++)
        grafo[i].clear();

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        grafo[u].pb(v); grafo[v].pb(u);
    }
    
    dfs(1, 0);
    solve(1, 0);
    
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
 
